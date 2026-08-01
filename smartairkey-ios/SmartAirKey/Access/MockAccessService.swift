import Foundation
import Combine

/// In-memory `SeamlessAccessService` used on Simulator, in SwiftUI previews and
/// in tests, where the BLE SDK cannot run. It simulates a small building with a
/// few doors and realistic status transitions so the whole UI is exercisable.
final class MockAccessService: SeamlessAccessService {

    private let doorsSubject: CurrentValueSubject<[Door], Never>
    private let eventsSubject = PassthroughSubject<AccessEvent, Never>()
    private let preferences: SeamlessPreferenceStoring
    private let analytics: AnalyticsLogging

    var doors: AnyPublisher<[Door], Never> { doorsSubject.eraseToAnyPublisher() }
    var events: AnyPublisher<AccessEvent, Never> { eventsSubject.eraseToAnyPublisher() }

    init(preferences: SeamlessPreferenceStoring = SeamlessPreferenceStore(),
         analytics: AnalyticsLogging = OSLogAnalytics(),
         doors: [Door] = MockAccessService.sampleDoors) {
        self.preferences = preferences
        self.analytics = analytics
        self.doorsSubject = CurrentValueSubject(doors)
    }

    var isSeamlessAccessEnabled: Bool { preferences.isSeamlessAccessEnabled }

    func start() {
        // Simulate doors coming online shortly after launch.
        transition(doorAt: 0, to: .connecting)
        DispatchQueue.main.asyncAfter(deadline: .now() + 0.8) { [weak self] in
            self?.transition(doorAt: 0, to: .ready)
            self?.transition(doorAt: 1, to: .ready)
        }
    }

    @discardableResult
    func loadKeys(serverJSON: Data) throws -> KeyLoadSummary {
        // The mock ignores the payload but reports a plausible summary.
        analytics.log(.keysRefreshed(active: doorsSubject.value.count, dropped: 0))
        return KeyLoadSummary(active: doorsSubject.value.count, dropped: 0)
    }

    func setSeamlessAccess(enabled: Bool) {
        preferences.isSeamlessAccessEnabled = enabled
        analytics.log(enabled ? .seamlessAccessEnabled : .seamlessAccessDisabled)
    }

    func open(doorID: String) {
        guard let index = doorsSubject.value.firstIndex(where: { $0.id == doorID }),
              doorsSubject.value[index].status.canOpen else {
            eventsSubject.send(.openFailed(doorID: doorID))
            return
        }
        transition(doorAt: index, to: .opening)
        DispatchQueue.main.asyncAfter(deadline: .now() + 0.9) { [weak self] in
            guard let self else { return }
            self.transition(doorAt: index, to: .opened)
            self.eventsSubject.send(.doorOpened(doorID: doorID))
            DispatchQueue.main.asyncAfter(deadline: .now() + 3) {
                self.transition(doorAt: index, to: .ready)
            }
        }
    }

    func refreshStatuses() {}

    func clear() {
        doorsSubject.send([])
    }

    // MARK: Helpers

    private func transition(doorAt index: Int, to status: DoorStatus) {
        var current = doorsSubject.value
        guard current.indices.contains(index) else { return }
        current[index].status = status
        doorsSubject.send(current)
    }

    static let sampleDoors: [Door] = [
        Door(id: "front-door", name: "Входная дверь", status: .connecting),
        Door(id: "lobby", name: "Подъезд", status: .unavailable),
        Door(id: "garage", name: "Гараж", status: .noAccess),
    ]
}
