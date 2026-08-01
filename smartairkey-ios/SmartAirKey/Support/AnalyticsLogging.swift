import Foundation
import os

/// Product analytics.
///
/// Requirement 12: the app records when seamless access is enabled/disabled,
/// successful door opens, and errors. This protocol keeps the call sites clean
/// and lets us swap in Firebase/Amplitude/etc. later without touching features.
protocol AnalyticsLogging {
    func log(_ event: AnalyticsEvent)
}

enum AnalyticsEvent {
    case seamlessAccessEnabled
    case seamlessAccessDisabled
    case doorOpenRequested(doorID: String)
    case doorOpenSucceeded(doorID: String)
    case doorOpenFailed(doorID: String, reason: String)
    case keysRefreshed(active: Int, dropped: Int)
    case error(domain: String, reason: String)
    case signedIn
    case signedOut

    var name: String {
        switch self {
        case .seamlessAccessEnabled: return "seamless_access_enabled"
        case .seamlessAccessDisabled: return "seamless_access_disabled"
        case .doorOpenRequested: return "door_open_requested"
        case .doorOpenSucceeded: return "door_open_succeeded"
        case .doorOpenFailed: return "door_open_failed"
        case .keysRefreshed: return "keys_refreshed"
        case .error: return "error"
        case .signedIn: return "signed_in"
        case .signedOut: return "signed_out"
        }
    }

    /// Structured parameters. Door identifiers are opaque ids, never BLE names.
    var parameters: [String: String] {
        switch self {
        case .seamlessAccessEnabled, .seamlessAccessDisabled, .signedIn, .signedOut:
            return [:]
        case let .doorOpenRequested(id), let .doorOpenSucceeded(id):
            return ["door_id": id]
        case let .doorOpenFailed(id, reason):
            return ["door_id": id, "reason": reason]
        case let .keysRefreshed(active, dropped):
            return ["active": String(active), "dropped": String(dropped)]
        case let .error(domain, reason):
            return ["domain": domain, "reason": reason]
        }
    }
}

/// Default implementation backed by the unified logging system.
/// Events are emitted at `.info`/`.error` so they can be collected off-device.
struct OSLogAnalytics: AnalyticsLogging {

    private let logger = Logger(
        subsystem: Bundle.main.bundleIdentifier ?? "com.smartairkey.seamless",
        category: "analytics"
    )

    func log(_ event: AnalyticsEvent) {
        let params = event.parameters
            .map { "\($0.key)=\($0.value)" }
            .sorted()
            .joined(separator: " ")
        switch event {
        case .doorOpenFailed, .error:
            logger.error("event=\(event.name, privacy: .public) \(params, privacy: .public)")
        default:
            logger.info("event=\(event.name, privacy: .public) \(params, privacy: .public)")
        }
    }
}
