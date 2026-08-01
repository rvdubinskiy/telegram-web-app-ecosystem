import Foundation

/// SDK-free mirror of `AirKeySmartDeviceCore.LockStatus.Bluetooth`.
///
/// Declared with the *same raw Int values* as the SDK enum so the real service
/// can convert with `LockBluetoothState(rawValue: sdkStatus.rawValue)`. Keeping
/// this here (with no SDK import) lets the status→UI mapping be unit-tested
/// without linking the binary framework.
enum LockBluetoothState: Int, CaseIterable {
    case undefined = 0
    case inactive = 1
    case channelDiscovered = 2
    case channelConnecting = 3
    case channelConnected = 4
    case discovered = 5
    case connecting = 6
    case connected = 7
    case opening = 8
    case opened = 9
    case closed = 10
    case unauthorized = 11
    case error = 12
    case smartDoor = 13
}

enum LockStateMapping {

    /// Translates a raw controller state into the user-facing `DoorStatus`.
    ///
    /// The user never sees BLE terminology — only "ready", "connecting",
    /// "opening", "opened", "unavailable", "no access" (UI reqs. 3 & 5).
    static func doorStatus(for state: LockBluetoothState) -> DoorStatus {
        switch state {
        case .undefined, .inactive, .error:
            return .unavailable
        case .channelDiscovered, .channelConnecting, .channelConnected,
             .discovered, .connecting:
            return .connecting
        case .connected, .closed, .smartDoor:
            return .ready
        case .opening:
            return .opening
        case .opened:
            return .opened
        case .unauthorized:
            return .noAccess
        }
    }
}
