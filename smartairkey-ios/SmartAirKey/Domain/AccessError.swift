import Foundation

/// User-facing errors, each written in plain language with exactly one primary
/// action (UI req. 4): enable Bluetooth / open Settings / retry / contact support.
enum AccessError: Identifiable, Equatable {

    case bluetoothOff
    case bluetoothDenied
    case bluetoothUnsupported
    case openFailed(doorID: String)
    case noAccess(doorID: String)
    case keysRefreshFailed
    case generic

    var id: String {
        switch self {
        case .bluetoothOff: return "bluetoothOff"
        case .bluetoothDenied: return "bluetoothDenied"
        case .bluetoothUnsupported: return "bluetoothUnsupported"
        case let .openFailed(id): return "openFailed-\(id)"
        case let .noAccess(id): return "noAccess-\(id)"
        case .keysRefreshFailed: return "keysRefreshFailed"
        case .generic: return "generic"
        }
    }

    var title: String {
        switch self {
        case .bluetoothOff: return L10n.string("error.bluetooth_off.title")
        case .bluetoothDenied: return L10n.string("error.bluetooth_denied.title")
        case .bluetoothUnsupported: return L10n.string("error.bluetooth_unsupported.title")
        case .openFailed: return L10n.string("error.open_failed.title")
        case .noAccess: return L10n.string("error.no_access.title")
        case .keysRefreshFailed: return L10n.string("error.keys_failed.title")
        case .generic: return L10n.string("error.generic.title")
        }
    }

    var message: String {
        switch self {
        case .bluetoothOff: return L10n.string("error.bluetooth_off.message")
        case .bluetoothDenied: return L10n.string("error.bluetooth_denied.message")
        case .bluetoothUnsupported: return L10n.string("error.bluetooth_unsupported.message")
        case .openFailed: return L10n.string("error.open_failed.message")
        case .noAccess: return L10n.string("error.no_access.message")
        case .keysRefreshFailed: return L10n.string("error.keys_failed.message")
        case .generic: return L10n.string("error.generic.message")
        }
    }

    /// The single primary action offered for this error.
    var primaryAction: ErrorAction {
        switch self {
        case .bluetoothOff, .bluetoothDenied: return .openSettings
        case .bluetoothUnsupported: return .contactSupport
        case .openFailed, .keysRefreshFailed, .generic: return .retry
        case .noAccess: return .contactSupport
        }
    }

    /// Short analytics reason string.
    var analyticsReason: String { id }
}

/// The one action a user can take to resolve an error.
enum ErrorAction: Equatable {
    case openSettings
    case retry
    case contactSupport

    var title: String {
        switch self {
        case .openSettings: return L10n.string("common.open_settings")
        case .retry: return L10n.string("common.retry")
        case .contactSupport: return L10n.string("common.contact_support")
        }
    }
}
