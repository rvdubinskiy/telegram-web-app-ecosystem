import Foundation

/// Builds a `JSONDecoder` that tolerates the several date shapes the SmartAirKey
/// backend and sample payloads use, so key parsing doesn't break on format drift.
enum ServerDecoding {

    private static let formats = [
        "yyyy-MM-dd'T'HH:mm:ss.SZZZZZ",   // documented server format
        "yyyy-MM-dd'T'HH:mm:ss.SSSZZZZZ",
        "yyyy-MM-dd'T'HH:mm:ss.SSS",
        "yyyy-MM-dd'T'HH:mm:ssZ",
        "dd.MM.yyyy, HH:mm:ss zzzz",      // sample bundle format
        "dd.MM.yyyy, HH:mm:ss zzz",
    ]

    static func makeDecoder() -> JSONDecoder {
        let formatters: [DateFormatter] = formats.map { format in
            let f = DateFormatter()
            f.locale = Locale(identifier: "en_US_POSIX")
            f.timeZone = TimeZone.current
            f.dateFormat = format
            return f
        }

        let decoder = JSONDecoder()
        decoder.dateDecodingStrategy = .custom { decoder in
            let container = try decoder.singleValueContainer()
            let raw = try container.decode(String.self)
            for formatter in formatters {
                if let date = formatter.date(from: raw) {
                    return date
                }
            }
            // Last resort: ISO8601 (handles offsets/Z without fractional seconds).
            if let date = ISO8601DateFormatter().date(from: raw) {
                return date
            }
            throw DecodingError.dataCorrupted(
                .init(codingPath: decoder.codingPath,
                      debugDescription: "Unrecognized date format: \(raw)")
            )
        }
        return decoder
    }
}
