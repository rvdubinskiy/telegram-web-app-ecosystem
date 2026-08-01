import UIKit

#if canImport(AirKeySmartDeviceCore)
import AirKeySmartDeviceCore
#endif

/// Boots the SmartAirKey SDK at launch so it can restore BLE connections in the
/// background (req. 7). Kept tiny — everything else lives in the SwiftUI layer.
final class AppDelegate: NSObject, UIApplicationDelegate {

    func application(
        _ application: UIApplication,
        didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]? = nil
    ) -> Bool {
        #if canImport(AirKeySmartDeviceCore) && !targetEnvironment(simulator)
        AirKeySmartDevice.shared.launch(options: launchOptions)
        #endif
        return true
    }
}
