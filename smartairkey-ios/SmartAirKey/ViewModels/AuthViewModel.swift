import Foundation

/// Drives the sign-in screen (req. 1: authorized resident obtains keys).
@MainActor
final class AuthViewModel: ObservableObject {

    @Published var email = ""
    @Published var password = ""
    @Published private(set) var isSubmitting = false
    @Published var errorMessage: String?

    private let auth: Authenticating
    private let session: SessionStore
    private let analytics: AnalyticsLogging

    init(auth: Authenticating, session: SessionStore, analytics: AnalyticsLogging) {
        self.auth = auth
        self.session = session
        self.analytics = analytics
    }

    convenience init(environment: AppEnvironment) {
        self.init(auth: environment.auth,
                  session: environment.session,
                  analytics: environment.analytics)
    }

    var canSubmit: Bool {
        !email.trimmingCharacters(in: .whitespaces).isEmpty
            && !password.isEmpty
            && !isSubmitting
    }

    func signIn() async {
        errorMessage = nil
        isSubmitting = true
        defer { isSubmitting = false }
        do {
            let token = try await auth.signIn(email: email, password: password)
            session.save(accessToken: token)
            analytics.log(.signedIn)
        } catch {
            let message = (error as? LocalizedError)?.errorDescription
                ?? L10n.string("auth.error.invalid")
            errorMessage = message
            analytics.log(.error(domain: "auth", reason: "\(error)"))
        }
    }
}
