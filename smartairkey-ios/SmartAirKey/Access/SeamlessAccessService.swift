import Foundation
import Combine

/// The app-facing contract for reaching SmartAirKey doors.
///
/// This is the seam that isolates the rest of the app from the SmartAirKey SDK
/// (BLE, CryptoKey, controllers, RSSI …). Everything above this protocol speaks
/// only in `Door` / `DoorStatus` / `AccessError` terms.
///
///  - `AirKeyAccessService` is the real implementation (wraps AirKeySmartDeviceCore).
///  - `MockAccessService` drives the UI on Simulator / in previews / in tests.
protocol SeamlessAccessService: AnyObject {

    /// The current set of doors and their statuses. Emits on every change.
    var doors: AnyPublisher<[Door], Never> { get }

    /// One-off events worth reacting to in the UI (success animation, error banner).
    var events: AnyPublisher<AccessEvent, Never> { get }

    /// Whether seamless (automatic) access is currently enabled.
    var isSeamlessAccessEnabled: Bool { get }

    /// Begins bluetooth/connection lifecycle. Call once the user is signed in.
    func start()

    /// Hands the SDK the latest digital keys received from the backend (req. 2).
    ///
    /// Expired and revoked keys are filtered out here and never used (req. 10).
    /// - Parameter serverJSON: raw JSON from the SmartAirKey backend.
    /// - Returns: a summary of how many keys were kept vs dropped.
    @discardableResult
    func loadKeys(serverJSON: Data) throws -> KeyLoadSummary

    /// Turns seamless access on/off (req. 3). Sets `autoOpen` on every active
    /// key to `enabled` (req. 4). Never deletes a key (req. 5).
    func setSeamlessAccess(enabled: Bool)

    /// Manually opens a door the user tapped "Open" on (req. 9).
    func open(doorID: String)

    /// Asks the SDK to refresh door statuses.
    func refreshStatuses()

    /// Removes all keys from the device (used on sign-out, req. 11).
    func clear()
}

/// Result of loading a key bundle, for analytics (req. 12) and UI feedback.
struct KeyLoadSummary: Equatable {
    /// Keys that are valid and were handed to the SDK.
    let active: Int
    /// Keys that were expired/revoked and deliberately dropped.
    let dropped: Int
}

/// Transient things the access layer reports up to the UI.
enum AccessEvent: Equatable {
    /// A door finished opening — trigger success animation + haptics (UI req. 7).
    case doorOpened(doorID: String)
    /// A manual open attempt failed.
    case openFailed(doorID: String)
    /// Something went wrong that the user should see.
    case failure(AccessError)
}
