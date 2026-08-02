import Foundation

/// Exchanges resident credentials for a backend access token.
///
/// The concrete network endpoint depends on the SmartAirKey deployment; the
/// protocol keeps sign-in swappable. `DemoAuthService` lets the app run without
/// a live server; `SmartAirKeyAuthService` is the network implementation.
protocol Authenticating {
    func signIn(email: String, password: String) async throws -> String
}

enum AuthError: LocalizedError {
    case invalidCredentials
    case network(underlying: Error)

    var errorDescription: String? {
        switch self {
        case .invalidCredentials: return L10n.string("auth.error.invalid")
        case .network: return L10n.string("error.generic.message")
        }
    }
}

/// Offline/demo sign-in: accepts any well-formed credentials and mints a local
/// token. Handy for Simulator and reviewers without backend access.
struct DemoAuthService: Authenticating {
    func signIn(email: String, password: String) async throws -> String {
        let email = email.trimmingCharacters(in: .whitespacesAndNewlines)
        guard email.contains("@"), password.count >= 4 else {
            throw AuthError.invalidCredentials
        }
        // A token the demo backend accepts. Real deployments return a SAS token.
        return "demo." + Data(email.utf8).base64EncodedString()
    }
}

/// Network sign-in against a SmartAirKey backend. Configure `baseURL` for your
/// environment. The exact auth route is deployment-specific; adjust `path`.
struct SmartAirKeyAuthService: Authenticating {

    let baseURL: URL
    let session: URLSession
    var path: String = "/api/mobile/auth"

    init(baseURL: URL, session: URLSession = .shared) {
        self.baseURL = baseURL
        self.session = session
    }

    func signIn(email: String, password: String) async throws -> String {
        var request = URLRequest(url: baseURL.appendingPathComponent(path))
        request.httpMethod = "POST"
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        request.httpBody = try JSONSerialization.data(
            withJSONObject: ["login": email, "password": password]
        )

        do {
            let (data, response) = try await session.data(for: request)
            guard let http = response as? HTTPURLResponse else {
                throw AuthError.network(underlying: URLError(.badServerResponse))
            }
            guard http.statusCode == 200 else {
                throw AuthError.invalidCredentials
            }
            let payload = try JSONDecoder().decode(TokenResponse.self, from: data)
            return payload.token
        } catch let error as AuthError {
            throw error
        } catch {
            throw AuthError.network(underlying: error)
        }
    }

    private struct TokenResponse: Decodable {
        let token: String
    }
}
