import XCTest
import Combine
@testable import SmartAirKey

/// Exercises the manual-open flow and sign-out cleanup through the mock service
/// (reqs. 9 & 11) without needing the BLE SDK.
final class MockAccessServiceTests: XCTestCase {

    private var cancellables: Set<AnyCancellable> = []

    override func tearDown() {
        cancellables.removeAll()
        super.tearDown()
    }

    func testOpeningReadyDoorEmitsDoorOpened() {
        let door = Door(id: "d1", name: "Test", status: .ready)
        let service = MockAccessService(preferences: InMemoryPreferences(),
                                        analytics: SpyAnalytics(),
                                        doors: [door])

        let opened = expectation(description: "door opened")
        service.events
            .sink { event in
                if case .doorOpened(let id) = event, id == "d1" { opened.fulfill() }
            }
            .store(in: &cancellables)

        service.open(doorID: "d1")
        wait(for: [opened], timeout: 2.0)
    }

    func testOpeningUnavailableDoorFails() {
        let door = Door(id: "d2", name: "Test", status: .unavailable)
        let service = MockAccessService(preferences: InMemoryPreferences(),
                                        analytics: SpyAnalytics(),
                                        doors: [door])

        let failed = expectation(description: "open failed")
        service.events
            .sink { event in
                if case .openFailed(let id) = event, id == "d2" { failed.fulfill() }
            }
            .store(in: &cancellables)

        service.open(doorID: "d2")
        wait(for: [failed], timeout: 2.0)
    }

    func testClearEmptiesDoors() {
        let service = MockAccessService(preferences: InMemoryPreferences(),
                                        analytics: SpyAnalytics())
        let emptied = expectation(description: "doors emptied")
        service.doors
            .dropFirst()
            .sink { doors in if doors.isEmpty { emptied.fulfill() } }
            .store(in: &cancellables)

        service.clear()
        wait(for: [emptied], timeout: 2.0)
    }

    func testSeamlessPreferencePersists() {
        let prefs = InMemoryPreferences()
        let service = MockAccessService(preferences: prefs, analytics: SpyAnalytics())
        XCTAssertFalse(service.isSeamlessAccessEnabled)
        service.setSeamlessAccess(enabled: true)
        XCTAssertTrue(service.isSeamlessAccessEnabled)
        XCTAssertTrue(prefs.isSeamlessAccessEnabled)
    }
}

// MARK: - Test doubles

final class InMemoryPreferences: SeamlessPreferenceStoring {
    var isSeamlessAccessEnabled: Bool = false
    func reset() { isSeamlessAccessEnabled = false }
}

final class SpyAnalytics: AnalyticsLogging {
    private(set) var events: [String] = []
    func log(_ event: AnalyticsEvent) { events.append(event.name) }
}
