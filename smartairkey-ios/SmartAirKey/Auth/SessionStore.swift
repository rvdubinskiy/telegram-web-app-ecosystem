import Foundation
import Combine

/// Holds the signed-in resident's credentials/token, backed by the Keychain.
///
/// The token is the app's proof to the SmartAirKey backend that it may fetch
/// this resident's digital keys. Cleared on sign-out (req. 11).
final class SessionStore: ObservableObject {

    private enum Account {
        static let token = "session.accessToken"
    }

    @Published private(set) var isSignedIn: Bool

    private let keychain: KeychainStore

    init(keychain: KeychainStore = KeychainStore()) {
        self.keychain = keychain
        self.isSignedIn = keychain.string(for: Account.token) != nil
    }

    var accessToken: String? {
        keychain.string(for: Account.token)
    }

    func save(accessToken: String) {
        try? keychain.setString(accessToken, for: Account.token)
        isSignedIn = true
    }

    /// Removes all tokens and secrets from the device.
    func clear() {
        keychain.removeAll()
        isSignedIn = false
    }
}
