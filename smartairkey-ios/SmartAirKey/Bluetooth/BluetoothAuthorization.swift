import Foundation
import Combine
import CoreBluetooth

/// User-facing Bluetooth availability. No CoreBluetooth types leak past here.
enum BluetoothAvailability: Equatable {
    /// Not yet determined / powering up.
    case unknown
    /// Everything is fine — doors can be reached.
    case ready
    /// Bluetooth is switched off.
    case off
    /// The user denied Bluetooth permission for this app.
    case denied
    /// This device can't use Bluetooth for access.
    case unsupported

    /// The actionable error to show, if any (UI req. 4).
    var error: AccessError? {
        switch self {
        case .ready, .unknown: return nil
        case .off: return .bluetoothOff
        case .denied: return .bluetoothDenied
        case .unsupported: return .bluetoothUnsupported
        }
    }
}

/// Wraps `CBCentralManager` to (a) prompt for Bluetooth permission and (b)
/// publish a plain-language availability state (req. 6).
final class BluetoothAuthorization: NSObject, ObservableObject {

    @Published private(set) var availability: BluetoothAvailability = .unknown

    private var manager: CBCentralManager?

    /// Creates the central manager, which triggers the system permission prompt
    /// on first use. We suppress the default "turn on Bluetooth" system alert
    /// (`ShowPowerAlert = false`) and present our own friendly message instead.
    func requestAuthorization() {
        guard manager == nil else {
            // Re-evaluate current state.
            centralManagerDidUpdateState(manager!)
            return
        }
        manager = CBCentralManager(
            delegate: self,
            queue: nil,
            options: [CBCentralManagerOptionShowPowerAlertKey: false]
        )
    }
}

extension BluetoothAuthorization: CBCentralManagerDelegate {

    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        let newValue: BluetoothAvailability
        switch central.state {
        case .poweredOn:
            newValue = .ready
        case .poweredOff:
            newValue = .off
        case .unauthorized:
            newValue = .denied
        case .unsupported:
            newValue = .unsupported
        case .resetting, .unknown:
            newValue = .unknown
        @unknown default:
            newValue = .unknown
        }

        DispatchQueue.main.async { [weak self] in
            self?.availability = newValue
        }
        AppLog.bluetooth.info("Bluetooth availability=\(String(describing: newValue), privacy: .public)")
    }
}
