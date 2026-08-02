import Foundation

/// Type-safe access to user-facing strings.
///
/// Every string the user can see is routed through here so that:
///  - translations live in `Localizable.strings` (ru + en), and
///  - the codebase never hard-codes user-facing text (or technical jargon).
enum L10n {

    static func string(_ key: String, _ args: CVarArg...) -> String {
        let format = NSLocalizedString(key, comment: "")
        return args.isEmpty ? format : String(format: format, arguments: args)
    }
}

/// Convenience so SwiftUI can write `Text(L.key)` while keeping key names checked in one place.
extension String {
    /// Localized value of `self` treated as a key.
    var localized: String { L10n.string(self) }
}
