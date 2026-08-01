import XCTest
@testable import SmartAirKey

/// Verifies the controller-state → user-facing status mapping (UI req. 3),
/// including that raw values stay aligned with the SDK enum's ordering.
final class LockStateMappingTests: XCTestCase {

    func testReadyStates() {
        XCTAssertEqual(LockStateMapping.doorStatus(for: .closed), .ready)
        XCTAssertEqual(LockStateMapping.doorStatus(for: .connected), .ready)
        XCTAssertEqual(LockStateMapping.doorStatus(for: .smartDoor), .ready)
    }

    func testConnectingStates() {
        for state: LockBluetoothState in [.channelDiscovered, .channelConnecting,
                                          .channelConnected, .discovered, .connecting] {
            XCTAssertEqual(LockStateMapping.doorStatus(for: state), .connecting,
                           "\(state) should map to connecting")
        }
    }

    func testOpeningAndOpened() {
        XCTAssertEqual(LockStateMapping.doorStatus(for: .opening), .opening)
        XCTAssertEqual(LockStateMapping.doorStatus(for: .opened), .opened)
    }

    func testUnavailableStates() {
        for state: LockBluetoothState in [.undefined, .inactive, .error] {
            XCTAssertEqual(LockStateMapping.doorStatus(for: state), .unavailable)
        }
    }

    func testNoAccess() {
        XCTAssertEqual(LockStateMapping.doorStatus(for: .unauthorized), .noAccess)
    }

    /// Raw values must match the SDK's `LockStatus.Bluetooth` order so
    /// `LockBluetoothState(rawValue: sdk.rawValue)` is correct.
    func testRawValueContract() {
        XCTAssertEqual(LockBluetoothState.undefined.rawValue, 0)
        XCTAssertEqual(LockBluetoothState.opened.rawValue, 9)
        XCTAssertEqual(LockBluetoothState.closed.rawValue, 10)
        XCTAssertEqual(LockBluetoothState.unauthorized.rawValue, 11)
        XCTAssertEqual(LockBluetoothState.smartDoor.rawValue, 13)
        XCTAssertEqual(LockBluetoothState.allCases.count, 14)
    }

    func testCanOpenOnlyWhenReadyOrOpened() {
        XCTAssertTrue(DoorStatus.ready.canOpen)
        XCTAssertTrue(DoorStatus.opened.canOpen)
        for status: DoorStatus in [.connecting, .opening, .unavailable, .noAccess, .expired] {
            XCTAssertFalse(status.canOpen, "\(status) should not be openable")
        }
    }
}
