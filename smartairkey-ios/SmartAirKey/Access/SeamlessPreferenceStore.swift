import Foundation

/// Persists the user's seamless-access toggle (req. 3) so it survives launches
/// and can be re-asserted on the SDK after every key refresh.
protocol SeamlessPreferenceStoring: AnyObject {
    var isSeamlessAccessEnabled: Bool { get set }
    /// Wipes the preference (used on sign-out, req. 11).
    func reset()
}

final class SeamlessPreferenceStore: SeamlessPreferenceStoring {

    private let defaults: UserDefaults
    private let key = "seamlessAccessEnabled"

    init(defaults: UserDefaults = .standard) {
        self.defaults = defaults
    }

    var isSeamlessAccessEnabled: Bool {
        get { defaults.bool(forKey: key) }
        set { defaults.set(newValue, forKey: key) }
    }

    func reset() {
        defaults.removeObject(forKey: key)
    }
}
