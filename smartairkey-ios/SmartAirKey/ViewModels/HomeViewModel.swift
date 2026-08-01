import Foundation
import Combine
import UIKit

/// Drives the main screen: the seamless-access toggle, the door list, manual
/// opens, success feedback and actionable errors. Speaks only in domain terms.
@MainActor
final class HomeViewModel: ObservableObject {

    // Seamless access (reqs. 1–5, UI 1/3)
    @Published var isSeamlessOn: Bool
    @Published private(set) var isSeamlessBusy = false

    // Doors (reqs. 8/9, UI 2/3)
    @Published private(set) var doors: [Door] = []
    @Published private(set) var isLoadingKeys = false

    // Feedback
    @Published var activeError: AccessError?
    @Published var successDoorName: String?

    // Bluetooth (req. 6)
    @Published private(set) var bluetooth: BluetoothAvailability = .unknown

    private let access: SeamlessAccessService
    private let bluetoothAuth: BluetoothAuthorization
    private let analytics: AnalyticsLogging
    private let keyProvider: KeyProviding
    private let config: AppConfig

    private var cancellables = Set<AnyCancellable>()
    private var lastOpenRequestedDoorID: String?

    init(access: SeamlessAccessService,
         bluetoothAuth: BluetoothAuthorization,
         analytics: AnalyticsLogging,
         keyProvider: KeyProviding,
         config: AppConfig) {
        self.access = access
        self.bluetoothAuth = bluetoothAuth
        self.analytics = analytics
        self.keyProvider = keyProvider
        self.config = config
        self.isSeamlessOn = access.isSeamlessAccessEnabled
        bind()
    }

    convenience init(environment: AppEnvironment) {
        self.init(access: environment.access,
                  bluetoothAuth: environment.bluetooth,
                  analytics: environment.analytics,
                  keyProvider: environment.keyProvider,
                  config: environment.config)
    }

    // MARK: Lifecycle

    /// Called when the home screen appears. Idempotent.
    func onAppear() {
        bluetoothAuth.requestAuthorization()
        access.start()
        Task { await refreshKeys() }
    }

    private func bind() {
        access.doors
            .receive(on: DispatchQueue.main)
            .sink { [weak self] doors in self?.doors = doors }
            .store(in: &cancellables)

        access.events
            .receive(on: DispatchQueue.main)
            .sink { [weak self] event in self?.handle(event) }
            .store(in: &cancellables)

        bluetoothAuth.$availability
            .receive(on: DispatchQueue.main)
            .sink { [weak self] availability in self?.handleBluetooth(availability) }
            .store(in: &cancellables)
    }

    // MARK: Keys (reqs. 1, 2, 10)

    func refreshKeys() async {
        isLoadingKeys = true
        defer { isLoadingKeys = false }
        do {
            let data = try await keyProvider.fetchDigitalKeys()
            try access.loadKeys(serverJSON: data)
        } catch {
            AppLog.backend.error("Key refresh failed: \(String(describing: error), privacy: .public)")
            analytics.log(.error(domain: "keys", reason: "\(error)"))
            activeError = .keysRefreshFailed
        }
    }

    // MARK: Seamless toggle (reqs. 3, 4, 5)

    func setSeamless(_ enabled: Bool) {
        isSeamlessOn = enabled
        isSeamlessBusy = true
        access.setSeamlessAccess(enabled: enabled)

        // Enabling requires Bluetooth; surface a friendly error if it isn't ready.
        if enabled {
            bluetoothAuth.requestAuthorization()
            if let error = bluetooth.error {
                activeError = error
            }
        }

        DispatchQueue.main.asyncAfter(deadline: .now() + 0.35) { [weak self] in
            self?.isSeamlessBusy = false
        }
    }

    var seamlessStatusText: String {
        if isSeamlessBusy {
            return isSeamlessOn
                ? L10n.string("seamless.state.turning_on")
                : L10n.string("seamless.state.turning_off")
        }
        return isSeamlessOn
            ? L10n.string("seamless.state.on")
            : L10n.string("seamless.state.off")
    }

    var seamlessSubtitle: String {
        isSeamlessOn
            ? L10n.string("seamless.subtitle.on")
            : L10n.string("seamless.subtitle.off")
    }

    // MARK: Manual open (req. 9)

    func open(_ door: Door) {
        guard door.status.canOpen else { return }
        lastOpenRequestedDoorID = door.id
        analytics.log(.doorOpenRequested(doorID: door.id))
        Haptics.tap()
        access.open(doorID: door.id)
    }

    // MARK: Events

    private func handle(_ event: AccessEvent) {
        switch event {
        case let .doorOpened(doorID):
            analytics.log(.doorOpenSucceeded(doorID: doorID))
            Haptics.success()
            successDoorName = doors.first(where: { $0.id == doorID })?.name ?? L10n.string("open.success")
            DispatchQueue.main.asyncAfter(deadline: .now() + 1.8) { [weak self] in
                self?.successDoorName = nil
            }
        case let .openFailed(doorID):
            analytics.log(.doorOpenFailed(doorID: doorID, reason: "open_failed"))
            Haptics.error()
            activeError = .openFailed(doorID: doorID)
        case let .failure(error):
            analytics.log(.error(domain: "access", reason: error.analyticsReason))
            activeError = error
        }
    }

    private func handleBluetooth(_ availability: BluetoothAvailability) {
        bluetooth = availability
        // Only nag about Bluetooth when the user is relying on seamless access.
        if isSeamlessOn, let error = availability.error {
            activeError = error
        }
    }

    // MARK: Error actions (UI req. 4)

    func perform(_ action: ErrorAction) {
        switch action {
        case .openSettings:
            if let url = URL(string: UIApplication.openSettingsURLString) {
                UIApplication.shared.open(url)
            }
        case .retry:
            let doorID = lastOpenRequestedDoorID
            activeError = nil
            if let doorID, let door = doors.first(where: { $0.id == doorID }) {
                open(door)
            } else {
                Task { await refreshKeys() }
            }
        case .contactSupport:
            if let url = config.supportURL {
                UIApplication.shared.open(url)
            }
        }
        if action != .retry { activeError = nil }
    }
}
