import XCTest
@testable import SmartAirKey

/// Verifies expired keys are treated as invalid (req. 10).
final class KeyValidityTests: XCTestCase {

    func testFutureExpiryIsValid() {
        let future = Date().addingTimeInterval(3600)
        XCTAssertTrue(KeyValidity.isValid(till: future))
    }

    func testPastExpiryIsInvalid() {
        let past = Date().addingTimeInterval(-3600)
        XCTAssertFalse(KeyValidity.isValid(till: past))
    }

    func testBoundaryIsInvalid() {
        let now = Date()
        XCTAssertFalse(KeyValidity.isValid(till: now, now: now))
    }
}
