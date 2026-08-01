import Foundation

/// Fetches the resident's digital keys from the SmartAirKey backend (req. 1).
///
/// Returns the raw server JSON. Decoding into SDK models happens strictly inside
/// the Access layer, keeping the SDK out of the rest of the app.
protocol KeyProviding {
    func fetchDigitalKeys() async throws -> Data
}

enum BackendError: LocalizedError {
    case notAuthenticated
    case badResponse(status: Int)
    case emptyData
    case transport(Error)

    var errorDescription: String? {
        L10n.string("error.keys_failed.message")
    }
}

/// Network implementation. Uses the resident's session token to authorize the
/// request, per the SmartAirKey mobile API (SAS-TOKEN + Timestamp headers).
struct SmartAirKeyBackendClient: KeyProviding {

    let baseURL: URL
    let session: URLSession
    let tokenProvider: () -> String?
    /// Endpoint returning the resident's keys ("route": keys + cryptoKeys).
    var path: String = "/api/mobile"
    var query: [URLQueryItem] = [URLQueryItem(name: "Action", value: "GetUserProfile")]

    init(baseURL: URL,
         session: URLSession = .shared,
         tokenProvider: @escaping () -> String?) {
        self.baseURL = baseURL
        self.session = session
        self.tokenProvider = tokenProvider
    }

    func fetchDigitalKeys() async throws -> Data {
        guard let token = tokenProvider() else { throw BackendError.notAuthenticated }

        var components = URLComponents(url: baseURL.appendingPathComponent(path),
                                       resolvingAgainstBaseURL: false)
        components?.queryItems = query
        guard let url = components?.url else { throw BackendError.badResponse(status: -1) }

        var request = URLRequest(url: url)
        request.httpMethod = "GET"
        request.setValue("SAS-TOKEN \(token)", forHTTPHeaderField: "Authorization")
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        request.setValue("*/*", forHTTPHeaderField: "Accept")
        request.setValue(Self.timestamp(), forHTTPHeaderField: "Timestamp")

        do {
            let (data, response) = try await session.data(for: request)
            guard let http = response as? HTTPURLResponse else {
                throw BackendError.badResponse(status: -1)
            }
            guard (200..<300).contains(http.statusCode) else {
                throw BackendError.badResponse(status: http.statusCode)
            }
            guard !data.isEmpty else { throw BackendError.emptyData }
            return data
        } catch let error as BackendError {
            throw error
        } catch {
            throw BackendError.transport(error)
        }
    }

    private static func timestamp() -> String {
        let formatter = DateFormatter()
        formatter.locale = Locale(identifier: "en_US_POSIX")
        formatter.timeZone = TimeZone(secondsFromGMT: 0)
        formatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss.SSS"
        return formatter.string(from: Date())
    }
}

/// Offline/demo provider that serves a bundled `route.sample.json`, so the app
/// is fully explorable without a live backend or granted keys.
struct BundledKeyProvider: KeyProviding {

    var resource = "route.sample"

    func fetchDigitalKeys() async throws -> Data {
        guard let url = Bundle.main.url(forResource: resource, withExtension: "json") else {
            throw BackendError.emptyData
        }
        return try Data(contentsOf: url)
    }
}
