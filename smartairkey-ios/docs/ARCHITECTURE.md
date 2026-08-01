# Architecture

## Goals

1. **Keep the SDK at arm's length.** BLE, `CryptoKey`, `LockStatus`, RSSI and
   controller concepts must never reach the UI (UI req. 5). They live behind one
   protocol: `SeamlessAccessService`.
2. **Be runnable without hardware.** Simulator, previews and tests use a mock,
   so the whole experience is exercisable without a phone or a real controller.
3. **Testable core.** The tricky rules (status mapping, error contracts, the
   open/clear flows) are pure and SDK-free, so they're unit-tested directly.
   (Key expiry is delegated to the SDK's own `CryptoKey.status`.)

## Layers

```
┌─────────────────────────────────────────────────────────────┐
│ Views (SwiftUI)   HomeView · SeamlessToggleCard · DoorRowView │
│                   OpenSuccessOverlay · LoginView · RootView    │
├─────────────────────────────────────────────────────────────┤
│ ViewModels        HomeViewModel · AuthViewModel  (@MainActor)  │
├─────────────────────────────────────────────────────────────┤
│ Services                                                       │
│   SeamlessAccessService  ◄── the SDK seam                      │
│     • AirKeyAccessService  (real: AirKeySmartDeviceCore)       │
│     • MockAccessService    (simulator / previews / tests)      │
│   KeyProviding · Authenticating · BluetoothAuthorization       │
│   AnalyticsLogging · SessionStore/Keychain · Preferences       │
├─────────────────────────────────────────────────────────────┤
│ Domain (SDK-free)   Door · DoorStatus · AccessError            │
└─────────────────────────────────────────────────────────────┘
```

## The SDK seam

`SeamlessAccessService` is the only contract the app depends on. It publishes
`[Door]` and `AccessEvent`s and accepts commands (`loadKeys`, `setSeamlessAccess`,
`open`, `clear`).

- **`AirKeyAccessService`** is the real implementation. It is the *only* file that
  imports `AirKeySmartDeviceCore`. It:
  - decodes the backend "route" JSON into SDK `CryptoKey`/`CompositeKey` models,
  - filters expired/revoked keys (req. 10),
  - hands keys to `AirKeySmartDevice.shared`,
  - conforms to `AirKeyDeviceDelegate` and translates `LockStatus.Bluetooth` into
    `DoorStatus` via `LockStateMapping`,
  - maps BLE device names back to opaque door ids so the UI never sees a device
    name.
  - It's wrapped in `#if canImport(AirKeySmartDeviceCore) && !targetEnvironment(simulator)`.

- **`MockAccessService`** provides the same behaviour in-memory with scripted
  status transitions.

`AppEnvironment` (composition root) picks the implementation at build time and
injects it everywhere.

## Data flow: opening a door

```
tap "Open"
  → HomeViewModel.open(door)                 // analytics + haptic tap
    → SeamlessAccessService.open(doorID)
      → AirKeySmartDevice.openLock(for:key:)  // BLE
        … delegate: lockStatusDidChanged(.opened)
      → AccessEvent.doorOpened(doorID)
  → HomeViewModel.handle(.doorOpened)         // success haptic + overlay + analytics
  → OpenSuccessOverlay animates
```

## Seamless toggle

The toggle writes the preference (persisted), then sets `autoOpen` on every
active key through `updateLock(keyId:settings:)`. The preference is re-asserted
after every key refresh so a fresh key set inherits the user's choice. Keys are
never deleted by the toggle (req. 5).

## Security / lifecycle

- Tokens live in the **Keychain** (`AfterFirstUnlock`, so background BLE works
  while locked). Sign-out calls `KeychainStore.removeAll()` and
  `AirKeySmartDevice.removeAllKeys()`.
- The app boots the SDK in `AppDelegate.didFinishLaunching` so iOS can relaunch
  it for background BLE events.

## Concurrency

View models are `@MainActor`. Services publish via Combine and marshal to the
main queue before the UI observes them.
