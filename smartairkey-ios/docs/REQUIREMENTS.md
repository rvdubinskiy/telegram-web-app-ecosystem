# Requirements traceability

Every MVP and UI requirement, mapped to where it's implemented.

## MVP — seamless BLE access

| # | Requirement | Where |
|---|-------------|-------|
| 1 | Authorized resident receives digital keys from the backend | `Auth/Authenticating.swift`, `Backend/KeyProviding.swift` (`SmartAirKeyBackendClient`), `ViewModels/HomeViewModel.refreshKeys()` |
| 2 | App passes valid keys to the SmartAirKey iOS SDK | `Access/AirKeyAccessService.loadKeys(serverJSON:)` → `AirKeySmartDevice.shared.add(compositeKeys:crypto:sent:)` |
| 3 | User can turn seamless access on/off with a switch | `Views/SeamlessToggleCard.swift`, `HomeViewModel.setSeamless(_:)` |
| 4 | On → `autoOpen = true`; off → `false` | `AirKeyAccessService.applySeamlessSetting(enabled:)` → `updateLock(keyId:settings:)` |
| 5 | Turning it off does **not** delete the key | `applySeamlessSetting` only edits `Settings.autoOpen`; keys are never removed on toggle |
| 6 | Requests Bluetooth permission; clear error if off/denied | `Bluetooth/BluetoothAuthorization.swift`, surfaced via `HomeViewModel.handleBluetooth`, `AccessError.bluetooth*` |
| 7 | Works minimised / screen locked, within iOS limits | `Info.plist` `UIBackgroundModes`; `AppDelegate` calls `AirKeySmartDevice.shared.launch`; Keychain `AfterFirstUnlock` |
| 8 | User sees the list of available doors and their status | `Views/HomeView.doorsSection`, `DoorRowView`, `DoorStatusBadge` |
| 9 | User can manually open an available door | `DoorRowView` "Open" button → `HomeViewModel.open(_:)` → `AirKeyAccessService.open(doorID:)` → `openLock(for:key:)` |
| 10 | Expired/revoked keys stop being used automatically | `CryptoKey.status == .active` filter in `loadKeys` (the SDK computes status from the key's validity period); `removeAllKeys()` before re-adding drops revoked keys |
| 11 | Sign-out removes keys and tokens from the device | `AppEnvironment.signOutCleanup()` → `access.clear()` (`removeAllKeys`), `SeamlessPreferenceStore.reset()`, `SessionStore.clear()` (`KeychainStore.removeAll`) |
| 12 | Records feature enable, successful opens, and errors | `Support/AnalyticsLogging.swift`; logged in `HomeViewModel` and `AirKeyAccessService` |

## UI requirements

| # | Requirement | Where |
|---|-------------|-------|
| 1 | Big "Seamless Access" switch + current status on the main screen | `Views/SeamlessToggleCard.swift` (large card, status text) |
| 2 | List of doors, each with an "Open" button | `HomeView.doorsSection` + `DoorRowView` |
| 3 | States: on / off / connecting / opened / unavailable / no-access | `Domain/DoorStatus`, `HomeViewModel.seamlessStatusText`, `Access/LockStateMapping` |
| 4 | Errors in plain language, one primary action (BT / settings / retry / support) | `Domain/AccessError.swift` (`primaryAction`), alert in `HomeView`, banner for Bluetooth |
| 5 | No technical terms (BLE, SDK, controller, RSSI, CryptoKey) shown | All user text via `Localizable.strings`; SDK confined to `Access/`; enforced by `AccessErrorTests.testCopyHasNoTechnicalJargon` |
| 6 | Modern, native, light+dark, Dynamic Type, VoiceOver | SwiftUI + semantic colors (`Theme`), system fonts, `accessibilityLabel/Value/Hint` throughout |
| 7 | Short animation + haptics on successful open | `Views/OpenSuccessOverlay.swift` + `Support/Haptics.success()` in `HomeViewModel.handle(.doorOpened)` |

## Notes & limitations

- **Background execution** relies on iOS BLE background modes and the SDK's own
  connection lifecycle; iOS may still suspend the app under memory pressure.
- **Live backend**: the auth route and key endpoint are deployment-specific
  (`SmartAirKeyAuthService.path`, `SmartAirKeyBackendClient.path`). Demo mode
  (bundled keys) is the default so the app is runnable out of the box.
- The SmartAirKey binary SDK is bundled in `Vendor/SDK/` (device + simulator
  slices), so the project builds out of the box after `xcodegen generate` +
  `pod install`.
