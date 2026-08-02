import Foundation
import Combine

#if canImport(AirKeySmartDeviceCore)
import AirKeySmartDeviceCore

/// Real implementation of `SeamlessAccessService` on top of the SmartAirKey SDK
/// (`AirKeySmartDeviceCore`). This is the ONE place in the app that knows about
/// CryptoKey / LockStatus / BLE device names; it exposes only `Door` values.
final class AirKeyAccessService: NSObject, SeamlessAccessService {

    // MARK: Publishers

    private let doorsSubject = CurrentValueSubject<[Door], Never>([])
    private let eventsSubject = PassthroughSubject<AccessEvent, Never>()

    var doors: AnyPublisher<[Door], Never> { doorsSubject.eraseToAnyPublisher() }
    var events: AnyPublisher<AccessEvent, Never> { eventsSubject.eraseToAnyPublisher() }

    // MARK: State

    /// Active keys keyed by their door id (the CryptoKey id).
    private var keysByDoorID: [String: CryptoKey] = [:]
    /// Reverse lookup: BLE device name -> door id.
    private var doorIDByDeviceName: [String: String] = [:]
    /// Stable display order of doors.
    private var doorOrder: [String] = []
    /// Latest known status per door id.
    private var statuses: [String: DoorStatus] = [:]

    private let device: AirKeySmartDeviceCoreProtocol
    private let analytics: AnalyticsLogging
    private let preferences: SeamlessPreferenceStoring

    init(device: AirKeySmartDeviceCoreProtocol = AirKeySmartDevice.shared,
         analytics: AnalyticsLogging,
         preferences: SeamlessPreferenceStoring) {
        self.device = device
        self.analytics = analytics
        self.preferences = preferences
        super.init()
        self.device.set(delegate: self)
    }

    // MARK: SeamlessAccessService

    var isSeamlessAccessEnabled: Bool { preferences.isSeamlessAccessEnabled }

    func start() {
        // Kicks off the connection lifecycle; safe to call repeatedly.
        (device as? AirKeySmartDevice)?.setupBluetooth()
        (device as? AirKeySmartDevice)?.updateBluetoothLocksStatuses()
    }

    @discardableResult
    func loadKeys(serverJSON: Data) throws -> KeyLoadSummary {
        let route = try ServerDecoding.makeDecoder().decode(Route.self, from: serverJSON)

        // Requirement 10: use only keys that are still valid. The SDK's
        // `CryptoKey.status` is computed from the key's validity period, so an
        // expired key reports `.expired` and is dropped here. (Revoked keys are
        // simply absent from the new bundle and removed by `removeAllKeys()`.)
        let activeKeys = route.cryptoKeys.filter { $0.status == .active }
        let dropped = route.cryptoKeys.count - activeKeys.count

        rebuildIndex(with: activeKeys)

        // Refresh the SDK's key set. Removing first ensures revoked keys (absent
        // from the new bundle) stop being used entirely (req. 10).
        device.removeAllKeys()
        device.add(compositeKeys: route.keys, crypto: activeKeys, sent: [])

        // Re-assert the seamless preference on the fresh key set (req. 3/4).
        applySeamlessSetting(enabled: preferences.isSeamlessAccessEnabled)

        publishDoors()

        let summary = KeyLoadSummary(active: activeKeys.count, dropped: dropped)
        analytics.log(.keysRefreshed(active: summary.active, dropped: summary.dropped))
        AppLog.access.info("Loaded keys active=\(summary.active) dropped=\(summary.dropped)")
        return summary
    }

    func setSeamlessAccess(enabled: Bool) {
        preferences.isSeamlessAccessEnabled = enabled
        applySeamlessSetting(enabled: enabled)
        analytics.log(enabled ? .seamlessAccessEnabled : .seamlessAccessDisabled)
        AppLog.access.info("Seamless access set to \(enabled)")
    }

    func open(doorID: String) {
        guard let key = keysByDoorID[doorID],
              let deviceName = bleDeviceName(for: key) else {
            eventsSubject.send(.openFailed(doorID: doorID))
            return
        }
        // Only meaningful when the door is reachable.
        guard statuses[doorID]?.canOpen == true else {
            eventsSubject.send(.openFailed(doorID: doorID))
            return
        }
        setStatus(.opening, for: doorID)
        device.openLock(for: deviceName, key: key)
        AppLog.access.info("Manual open requested door=\(doorID, privacy: .public)")
    }

    func refreshStatuses() {
        (device as? AirKeySmartDevice)?.updateBluetoothLocksStatuses()
    }

    func clear() {
        device.removeAllKeys()
        keysByDoorID.removeAll()
        doorIDByDeviceName.removeAll()
        doorOrder.removeAll()
        statuses.removeAll()
        publishDoors()
        AppLog.access.info("Cleared all keys from device")
    }

    // MARK: - Internals

    /// Applies `autoOpen = enabled` to every active key without deleting them (req. 5).
    private func applySeamlessSetting(enabled: Bool) {
        for (doorID, key) in keysByDoorID {
            var settings = key.settings
            settings.autoOpen = enabled
            // Notify the user's phone when the door opens by itself.
            settings.notifyWhenOpened = enabled
            device.updateLock(keyId: key.id, settings: settings)
            _ = doorID
        }
    }

    private func rebuildIndex(with keys: [CryptoKey]) {
        keysByDoorID.removeAll()
        doorIDByDeviceName.removeAll()
        var order: [String] = []
        for key in keys {
            keysByDoorID[key.id] = key
            if let name = bleDeviceName(for: key) {
                doorIDByDeviceName[name] = key.id
            }
            order.append(key.id)
        }
        doorOrder = order
        // Drop statuses for doors that no longer exist.
        statuses = statuses.filter { keysByDoorID[$0.key] != nil }
    }

    private func bleDeviceName(for key: CryptoKey) -> String? {
        let transport: Transport.BluetoothLE? = key.lock.transport(.blueToothLe)
        return transport?.deviceName
    }

    private func setStatus(_ status: DoorStatus, for doorID: String) {
        statuses[doorID] = status
        publishDoors()
    }

    private func publishDoors() {
        let doors: [Door] = doorOrder.compactMap { id in
            guard let key = keysByDoorID[id] else { return nil }
            let status = statuses[id] ?? .connecting
            return Door(id: id, name: displayName(for: key), status: status)
        }
        let snapshot = doors
        if Thread.isMainThread {
            doorsSubject.send(snapshot)
        } else {
            DispatchQueue.main.async { [weak self] in self?.doorsSubject.send(snapshot) }
        }
    }

    /// User-facing name for a door. Falls back gracefully; never shows a BLE name.
    private func displayName(for key: CryptoKey) -> String {
        let trimmed = key.title.trimmingCharacters(in: .whitespacesAndNewlines)
        return trimmed.isEmpty ? L10n.string("app.name") : trimmed
    }
}

// MARK: - AirKeyDeviceDelegate

extension AirKeyAccessService: AirKeyDeviceDelegate {

    func lockStatusDidChanged(device name: String, status: LockStatus) {
        guard let doorID = doorIDByDeviceName[name] else { return }
        guard let bluetooth = status.bluetooth,
              let raw = LockBluetoothState(rawValue: bluetooth.rawValue) else { return }

        let newStatus = LockStateMapping.doorStatus(for: raw)
        let previous = statuses[doorID]
        statuses[doorID] = newStatus

        // Surface a successful open exactly once on the rising edge.
        if newStatus == .opened && previous != .opened {
            eventsSubject.send(.doorOpened(doorID: doorID))
        }
        if newStatus == .noAccess && previous != .noAccess {
            eventsSubject.send(.failure(.noAccess(doorID: doorID)))
        }

        publishDoors()
    }

    func didChange(configuration: Configuration, for deviceName: String) {
        // Controller configuration is not surfaced to the resident in this app.
    }

    func device(configuration: Configuration) {
        // Not surfaced to the resident.
    }
}

// MARK: - Server payload

/// The backend "route" payload: composite keys + their crypto keys.
private struct Route: Decodable {
    let keys: [CompositeKey]
    let cryptoKeys: [CryptoKey]
}

#endif
