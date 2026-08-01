# SmartAirKey — Seamless BLE Access (iOS)

A native iOS app that gives an authorized resident **seamless, hands-free access**
to their doors using the SmartAirKey BLE SDK (`AirKeySmartDeviceCore`).

The resident flips one big switch — **Seamless Access** — and doors open by
themselves as they walk up. They can also open any door manually, see each
door's status in plain language, and never encounter a single technical term
(no BLE / SDK / RSSI / controller / key jargon anywhere in the UI).

> Built as an MVP against the SmartAirKey SDK **v1.2** and the official `TestApp`
> integration sample.

---

## What it does

| Area | Behaviour |
|------|-----------|
| **Seamless access** | One prominent toggle turns automatic opening on/off. On → `autoOpen = true` on every valid key; Off → `false`. Turning it off never deletes a key. |
| **Doors** | A live list of the resident's doors, each with a plain-language status and an **Open** button for manual opening. |
| **Keys** | Digital keys are fetched from the backend and handed to the SDK. Expired/revoked keys are filtered out and stop being used automatically. |
| **Bluetooth** | Requests Bluetooth permission and shows a friendly, actionable message if it's off or denied. |
| **Background** | Works with the app minimised and the screen locked, within iOS limits (background BLE + Keychain unlocked after first unlock). |
| **Sign-out** | Wipes all keys and tokens from the device. |
| **Feedback** | Success animation + haptics on open; every error has exactly one clear action. |
| **Analytics** | Records feature enable/disable, successful opens, and errors. |

Full requirement-by-requirement mapping: [`docs/REQUIREMENTS.md`](docs/REQUIREMENTS.md).

## Architecture

Clean separation with the SmartAirKey SDK confined to a single seam so the rest
of the app speaks only in product terms (`Door`, `DoorStatus`, `AccessError`).

```
Views (SwiftUI)  ──►  ViewModels  ──►  Services
                                        ├─ SeamlessAccessService  ← SDK boundary
                                        │    ├─ AirKeyAccessService  (real, wraps AirKeySmartDeviceCore)
                                        │    └─ MockAccessService     (Simulator / previews / tests)
                                        ├─ KeyProviding      (backend keys)
                                        ├─ Authenticating    (sign-in)
                                        ├─ BluetoothAuthorization  (CoreBluetooth)
                                        └─ AnalyticsLogging
```

Details: [`docs/ARCHITECTURE.md`](docs/ARCHITECTURE.md).

## Requirements

- macOS with Xcode 15+ / iOS 16+ target
- [XcodeGen](https://github.com/yonaskolb/XcodeGen) (`brew install xcodegen`)
- [CocoaPods](https://cocoapods.org) (`sudo gem install cocoapods`)

The SmartAirKey binary SDK **is included** in this repo under
[`Vendor/SDK/`](Vendor/SDK) (device + simulator slices), so the project builds
without any extra downloads:

- `AirKeySmartDeviceCore.xcframework` (the SDK)
- `AIKAirKite.xcframework`, `BWBluetoothWolf.xcframework`,
  `DIDeviceInteractionLion.xcframework`, `TCTransportCamel.xcframework`

## Setup

```bash
cd smartairkey-ios

# Generate the Xcode project and install the SDK's public pod dependencies.
xcodegen generate
pod install

open SmartAirKey.xcworkspace
```

(`scripts/setup.sh /path/to/TestAppX/TestAppX` does the same and can also
re-copy the SDK from a fresh `iOS_TestApp` bundle if you ever need to update it.)

CocoaPods pulls the SDK's public transitive dependencies
(`CocoaLumberjack`, `Protobuf`, `SSZipArchive`, `RWMRecurrenceRule`,
`TransitionKit`) — see [`Podfile`](Podfile).

### Running without hardware

On **Simulator** (and in SwiftUI previews) the app runs against
`MockAccessService`, which simulates a small building with several doors and
realistic status transitions — so the entire UI is explorable without a phone or
a real controller. Sign in with any email containing `@` and a 4+ character
password (demo mode).

### Connecting a real backend

By default the app runs in demo mode (`AppConfig.demo`): bundled sample keys +
demo sign-in. To use a live SmartAirKey backend, set `backendBaseURL` in
`AppConfig` (see `App/AppEnvironment.swift`). The app then authenticates and
fetches keys over the network and, on a physical device, drives the real SDK.

## Tests

SDK-free logic (status mapping, key expiry, error contracts, the open/clear
flows) is covered by unit tests in `SmartAirKeyTests/`:

```bash
xcodebuild test -workspace SmartAirKey.xcworkspace \
  -scheme SmartAirKey -destination 'platform=iOS Simulator,name=iPhone 15'
```

## Project layout

```
smartairkey-ios/
├── project.yml                 XcodeGen project spec
├── Podfile                     SDK transitive pods
├── scripts/setup.sh            Vendors the SDK + generates the project
├── SmartAirKey/
│   ├── App/                    Entry point, AppDelegate (SDK launch), DI container
│   ├── Domain/                 Door, DoorStatus, AccessError  (SDK-free vocabulary)
│   ├── Access/                 SeamlessAccessService + SDK wrapper + mock + mapping
│   ├── Backend/                Key fetching (network + bundled)
│   ├── Auth/                   Sign-in, Keychain, session
│   ├── Bluetooth/              Bluetooth permission/state (CoreBluetooth)
│   ├── Support/                Localization, logging, analytics, haptics
│   ├── ViewModels/             HomeViewModel, AuthViewModel
│   ├── Views/                  SwiftUI screens & components
│   └── Resources/              Info.plist, entitlements, assets, ru/en strings
└── SmartAirKeyTests/
```

## License

Uses the SmartAirKey SDK (© Airkey, Apache-2.0). Application code follows the
same license.
