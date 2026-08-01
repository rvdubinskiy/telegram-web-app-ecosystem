import Foundation

/// Pure rules for deciding whether a digital key may still be used (req. 10).
///
/// Kept free of SDK types so the expiry rule can be unit-tested directly. The
/// real service combines this with the SDK's own `CryptoKey.status`.
enum KeyValidity {

    /// A key is usable while its validity period has not ended.
    /// - Parameters:
    ///   - till: end of the key's validity period.
    ///   - now: reference time (injectable for tests).
    static func isValid(till: Date, now: Date = Date()) -> Bool {
        till > now
    }
}
