//
//  AIKServiceAdapterProtocol.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 21.03.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;

@protocol AIKServiceAdapter__Protocol__Setup <NSObject>
- (void)setup;
- (void)postSetup; // called after AIKServicesManager.manager.interServicesSetup. We assure that all necessary items provided for services.
- (void)login;
- (void)logout;
@end

@protocol AIKServiceAdapter__Protocol__Startup <NSObject>
// start service.
// not the same as setup.
// these methods just switch service on and off.
- (void)start;
- (void)stop;
@end

typedef NS_ENUM(NSInteger, AIK__Services__Permissions__Status) {
    AIK__Services__Permissions__Status__Unknown,
    AIK__Services__Permissions__Status__Denied,
    AIK__Services__Permissions__Status__PartiallyGranted,
    AIK__Services__Permissions__Status__Granted,
    AIK__Services__Permissions__Status__Restricted // Cannot change this setting at all.
};

@protocol AIKServiceAdapter__Protocol__Permissions__Listener <NSObject>
- (void)didRequestPermissionsWithStatus:(AIK__Services__Permissions__Status)status fromServiceNamed:(NSString *)name;
@end

@protocol AIKServiceAdapter__Protocol__Permissions <NSObject>
- (void)requestPermissions;
- (void)requestPermissionsStatus:(void(^)(AIK__Services__Permissions__Status status))block;
@end

@protocol AIKServiceAdapter__Protocol__Information <NSObject>

@property (nonatomic, readonly) NSDictionary *debugInformation;
@property (nonatomic, readonly) BOOL health;
@property (nonatomic, readonly) BOOL active;
@property (nonatomic, readonly) NSString *name;
+ (NSString *)name;
@property (nonatomic, readonly) NSString *localizedName;

@end
