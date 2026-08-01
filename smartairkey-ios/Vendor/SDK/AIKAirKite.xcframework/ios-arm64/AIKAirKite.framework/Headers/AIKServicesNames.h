//
//  AIKServicesNames.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 06.10.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;

typedef NSString AIKServicesName;
// in swift it is easy to rewrite as
@interface AIKServicesNames : NSProxy
+ (AIKServicesName *)Project;
+ (AIKServicesName *)Appearance;
+ (AIKServicesName *)Assistance;
+ (AIKServicesName *)Audio;
+ (AIKServicesName *)Bluetooth;
+ (AIKServicesName *)Database;
+ (AIKServicesName *)DeliveryPost;
+ (AIKServicesName *)DeviceInteraction;
+ (AIKServicesName *)DiagnosticsLogging;
+ (AIKServicesName *)Locale;
+ (AIKServicesName *)LocationBase;
+ (AIKServicesName *)LocationFamily;
+ (AIKServicesName *)LocationWithGeneralMonitoring;
+ (AIKServicesName *)LocationWithSignificantChanging;
+ (AIKServicesName *)LocationWithBeaconListening;
+ (AIKServicesName *)Logging;
+ (AIKServicesName *)Model;
+ (AIKServicesName *)Network;
+ (AIKServicesName *)RemoteNotificationsForSystem;
+ (AIKServicesName *)RemoteNotificationsForUser;
+ (AIKServicesName *)LocalNotifications;
+ (AIKServicesName *)NotificationsCenter; // Only for access to UN Notifications Center Delegate.
+ (AIKServicesName *)Search;
+ (AIKServicesName *)Storage;
+ (AIKServicesName *)ThirdPartyFabric;
+ (AIKServicesName *)ThirdPartyGoogleMaps;
+ (AIKServicesName *)UserActivity;
+ (AIKServicesName *)Validation;
+ (AIKServicesName *)ViewControllersRouting;
@end
