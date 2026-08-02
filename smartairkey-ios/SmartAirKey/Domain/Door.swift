import Foundation

/// A door the resident can reach, in plain product terms.
///
/// This is the *only* vocabulary the UI ever sees. It deliberately contains no
/// BLE / SDK / controller / RSSI / key concepts (UI req. 5) — the Access layer
/// translates the SmartAirKey SDK into these values.
struct Door: Identifiable, Equatable, Hashable {

    /// Stable, opaque identifier (derived from the digital key). Never a BLE name.
    let id: String

    /// Friendly, human name shown to the user (e.g. "Front door").
    let name: String

    /// Current status of the door.
    var status: DoorStatus

    init(id: String, name: String, status: DoorStatus) {
        self.id = id
        self.name = name
        self.status = status
    }
}

/// The states a single door can be in, as the user understands them.
///
/// Maps the UI-required states (UI req. 3): connecting, opened, unavailable,
/// no-access — plus the everyday "ready" and transient "opening".
enum DoorStatus: Equatable, Hashable {

    /// Establishing a connection to the door.
    case connecting

    /// In range and ready — the user can open it.
    case ready

    /// Open command in flight.
    case opening

    /// The door is open right now.
    case opened

    /// Not reachable (out of range / no connection). User should move closer.
    case unavailable

    /// The resident's access to this door is not authorized.
    case noAccess

    /// The digital access has expired or been revoked.
    case expired

    /// Whether a manual "Open" action is currently possible (req. 9).
    var canOpen: Bool {
        switch self {
        case .ready, .opened: return true
        case .connecting, .opening, .unavailable, .noAccess, .expired: return false
        }
    }

    /// Localized, jargon-free label for the status.
    var localizedTitle: String {
        switch self {
        case .connecting: return L10n.string("door.status.connecting")
        case .ready: return L10n.string("door.status.ready")
        case .opening: return L10n.string("door.status.opening")
        case .opened: return L10n.string("door.status.opened")
        case .unavailable: return L10n.string("door.status.unavailable")
        case .noAccess: return L10n.string("door.status.no_access")
        case .expired: return L10n.string("door.status.expired")
        }
    }

    /// SF Symbol used in the status badge.
    var systemImage: String {
        switch self {
        case .connecting: return "dot.radiowaves.left.and.right"
        case .ready: return "lock.fill"
        case .opening: return "arrow.triangle.2.circlepath"
        case .opened: return "lock.open.fill"
        case .unavailable: return "wifi.slash"
        case .noAccess: return "hand.raised.fill"
        case .expired: return "clock.badge.exclamationmark.fill"
        }
    }

    /// Semantic tint category for the status (resolved to a color in the view).
    var tint: DoorStatusTint {
        switch self {
        case .opened, .ready: return .positive
        case .connecting, .opening: return .neutral
        case .unavailable: return .muted
        case .noAccess, .expired: return .negative
        }
    }
}

enum DoorStatusTint {
    case positive
    case neutral
    case muted
    case negative
}
