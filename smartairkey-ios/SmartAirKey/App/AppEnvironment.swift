import Foundation

/// Runtime configuration. With no `backendBaseURL` the app runs in demo mode
/// (bundled keys + demo sign-in), so it is fully explorable without a server.
struct AppConfig {
    /// Base URL of the SmartAirKey mobile backend, e.g. https://apidev.smartairkey.com
    var backendBaseURL: URL?
    /// Support contact surfaced by the "Contact support" error action.
    var supportURL: URL? = URL(string: "mailto:support@smartairkey.com")

    static let demo = AppConfig(backendBaseURL: nil)
}

/// Composition root: builds and owns the app's services and wires the SDK seam.
///
/// The real SmartAirKey SDK service is used on device; Simulator/previews use the
/// in-memory mock so the whole UI is exercisable without hardware.
final class AppEnvironment: ObservableObject {

    let config: AppConfig
    let session: SessionStore
    let bluetooth: BluetoothAuthorization
    let analytics: AnalyticsLogging
    let preferences: SeamlessPreferenceStoring
    let access: SeamlessAccessService
    let auth: Authenticating
    let keyProvider: KeyProviding

    init(config: AppConfig = .demo,
         session: SessionStore = SessionStore(),
         bluetooth: BluetoothAuthorization = BluetoothAuthorization(),
         analytics: AnalyticsLogging = OSLogAnalytics(),
         preferences: SeamlessPreferenceStoring = SeamlessPreferenceStore(),
         access: SeamlessAccessService? = nil,
         auth: Authenticating? = nil,
         keyProvider: KeyProviding? = nil) {

        self.config = config
        self.session = session
        self.bluetooth = bluetooth
        self.analytics = analytics
        self.preferences = preferences
        self.access = access ?? AppEnvironment.makeAccessService(analytics: analytics,
                                                                 preferences: preferences)
        self.auth = auth ?? AppEnvironment.makeAuth(config: config)
        self.keyProvider = keyProvider ?? AppEnvironment.makeKeyProvider(config: config,
                                                                        session: session)
    }

    private static func makeAccessService(analytics: AnalyticsLogging,
                                          preferences: SeamlessPreferenceStoring) -> SeamlessAccessService {
        #if canImport(AirKeySmartDeviceCore) && !targetEnvironment(simulator)
        return AirKeyAccessService(analytics: analytics, preferences: preferences)
        #else
        return MockAccessService(preferences: preferences, analytics: analytics)
        #endif
    }

    private static func makeAuth(config: AppConfig) -> Authenticating {
        if let base = config.backendBaseURL {
            return SmartAirKeyAuthService(baseURL: base)
        }
        return DemoAuthService()
    }

    private static func makeKeyProvider(config: AppConfig, session: SessionStore) -> KeyProviding {
        if let base = config.backendBaseURL {
            return SmartAirKeyBackendClient(baseURL: base, tokenProvider: { session.accessToken })
        }
        return BundledKeyProvider()
    }

    /// Removes all on-device secrets and keys (req. 11).
    func signOutCleanup() {
        access.clear()
        preferences.reset()
        session.clear()
        analytics.log(.signedOut)
    }
}
