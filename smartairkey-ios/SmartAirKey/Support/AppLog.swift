import Foundation
import os

/// Lightweight structured logging built on `os.Logger`.
///
/// Used for diagnostics only. Product analytics events (feature enabled,
/// successful opens, errors — req. 12) go through `AnalyticsLogging`.
enum AppLog {

    private static let subsystem = Bundle.main.bundleIdentifier ?? "com.smartairkey.seamless"

    static let access = Logger(subsystem: subsystem, category: "access")
    static let backend = Logger(subsystem: subsystem, category: "backend")
    static let auth = Logger(subsystem: subsystem, category: "auth")
    static let bluetooth = Logger(subsystem: subsystem, category: "bluetooth")
    static let ui = Logger(subsystem: subsystem, category: "ui")
}
