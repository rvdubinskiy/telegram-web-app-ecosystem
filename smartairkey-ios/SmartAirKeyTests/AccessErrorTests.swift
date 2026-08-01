import XCTest
@testable import SmartAirKey

/// Confirms every error offers exactly one clear primary action (UI req. 4)
/// and never leaks technical jargon.
final class AccessErrorTests: XCTestCase {

    private let all: [AccessError] = [
        .bluetoothOff, .bluetoothDenied, .bluetoothUnsupported,
        .openFailed(doorID: "x"), .noAccess(doorID: "x"),
        .keysRefreshFailed, .generic,
    ]

    func testEveryErrorHasTitleMessageAndAction() {
        for error in all {
            XCTAssertFalse(error.title.isEmpty, "\(error.id) missing title")
            XCTAssertFalse(error.message.isEmpty, "\(error.id) missing message")
            XCTAssertFalse(error.primaryAction.title.isEmpty, "\(error.id) missing action")
        }
    }

    func testActionsMatchExpectations() {
        XCTAssertEqual(AccessError.bluetoothOff.primaryAction, .openSettings)
        XCTAssertEqual(AccessError.bluetoothDenied.primaryAction, .openSettings)
        XCTAssertEqual(AccessError.openFailed(doorID: "x").primaryAction, .retry)
        XCTAssertEqual(AccessError.keysRefreshFailed.primaryAction, .retry)
        XCTAssertEqual(AccessError.noAccess(doorID: "x").primaryAction, .contactSupport)
    }

    func testCopyHasNoTechnicalJargon() {
        let banned = ["BLE", "RSSI", "SDK", "CryptoKey", "controller", "контроллер", "Bluetooth Low Energy"]
        for error in all {
            let text = (error.title + " " + error.message)
            for term in banned {
                XCTAssertFalse(text.localizedCaseInsensitiveContains(term),
                               "\(error.id) copy contains banned term \(term)")
            }
        }
    }
}
