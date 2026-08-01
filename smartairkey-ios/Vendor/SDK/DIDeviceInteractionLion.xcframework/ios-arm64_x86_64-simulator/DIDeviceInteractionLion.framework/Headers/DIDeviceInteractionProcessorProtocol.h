//
//  DIDeviceInteractionProcessorProtocol.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 31.10.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;
@class DIDeviceInteractionCommand;
@class DIDeviceInteractionAmaterasuSession;
@class DIDeviceInteractionResponse;
@protocol DIDeviceInteractionEntityDeviceInformation__IdentifierProtocol;

NS_ASSUME_NONNULL_BEGIN
@protocol DIDeviceInteractionProcessorOpenProtocol <NSObject>

@end

@protocol DIDeviceInteractionProcessor__Protocol__Notifications__DataProvider/*Accessing.(on self)*/ <NSObject>
- (NSString *)stateWithDeviceId:(id)deviceId;
@end

@protocol DIDeviceInteractionProcessor__Protocol__Notifications/*Receiving?*/ <NSObject>
- (void)didChangeState:(NSString *)state deviceId:(NSString *)name;
@end

@protocol DIDeviceInteractionProcessor__Protocol__Sending <NSObject>
// TODO: Rewrite them later by combining deviceInformation.identifier and deviceName into one structure to outer world.
- (void)didSendPayload:(id)payload deviceName:(NSString *)name deviceId:(id<DIDeviceInteractionEntityDeviceInformation__IdentifierProtocol>)deviceId error:(NSError *)error __deprecated;
@end

@protocol DIDeviceInteractionProcessor__Protocol__Receiving <NSObject>
// TODO: Rewrite them later by combining deviceInformation.identifier and deviceName into one structure to outer world.
- (void)didReceiveResponse:(DIDeviceInteractionResponse *)response deviceName:(NSString *)name deviceId:(id<DIDeviceInteractionEntityDeviceInformation__IdentifierProtocol>)deviceId error:(NSError *)error __deprecated;
@end

@protocol DIDeviceInteractionProcessor__Protocol__MessagingObserver <DIDeviceInteractionProcessor__Protocol__Sending, DIDeviceInteractionProcessor__Protocol__Receiving> @end

@protocol DIDeviceInteractionProcessor__Protocol__Measurements <NSObject>
- (void)didDiscoverDeviceWithName:(NSString *)deviceName advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)rssi;
@end

@protocol DIDeviceInteractionProcessorSessionProtocol <NSObject>
- (void)prolongateSessionWithDeviceName:(NSString *)name;
- (void)expireSessionWithDeviceName:(NSString *)name;
//TODO: rename later when needed.
//choose word active against valid. or even fresh.
- (BOOL)isSessionValidWithDeviceName:(NSString *)name;
- (DIDeviceInteractionAmaterasuSession *)sessionWithName:(NSString *)name withType:(NSString *)type;
@end

@interface DIDeviceInteractionProcessorTransferProtocol
@end

@interface DIDeviceInteractionProcessor__Protocol__Transfer__Action : NSObject <NSCopying>
+ (instancetype)mainApp;
+ (instancetype)notifications;
+ (instancetype)default;
- (BOOL)isEqual:(id)object;
@end

@protocol DIDeviceInteractionProcessor__Protocol__Transfer <NSObject>
- (void)sendMessage:(DIDeviceInteractionCommand *)lockCommand;
- (void)sendMessage:(DIDeviceInteractionCommand *)lockCommand action:(DIDeviceInteractionProcessor__Protocol__Transfer__Action *)action;
@optional - (void)sendMessage:(DIDeviceInteractionCommand *)lockCommand onChannelWithType:(NSString *)type __deprecated;

@end

typedef NS_ENUM(NSUInteger, DIDeviceInteractionProcessorTerminateProtocol__Action) {
    DIDeviceInteractionProcessorTerminateProtocol__Action__CloseSession,
    DIDeviceInteractionProcessorTerminateProtocol__Action__CloseConnection,
    DIDeviceInteractionProcessorTerminateProtocol__Action__TerminateSession
};

@protocol DIDeviceInteractionProcessorTerminateProtocol <NSObject>
// close session - destroy all information
// close connection with force - force flag is default to YES.
// close connection without force - close connection and leave channel.
// close connection with force - close connection and destroy channel.
// terminate session - close session and close connection with appropriate rule based on force flag.

- (void)closeSessionWithDeviceName:(NSString *)name;
- (void)closeConnectionWithDeviceName:(NSString *)name;
- (void)closeConnectionWithDeviceName:(NSString *)name force:(BOOL)force;
- (void)terminateSessionWithDeviceName:(NSString *)name;
- (void)terminateSessionWithDeviceName:(NSString *)name forceCloseConnection:(BOOL)force;
- (void)terminateAllSessions;

// and alternative with channels
- (void)closeSessionWithDeviceName:(NSString *)name withChannelType:(NSString *)type;
- (void)closeConnectionWithDeviceName:(NSString *)name withChannelType:(NSString *)type force:(BOOL)force;
- (void)terminateSessionWithDeviceName:(NSString *)name withChannelType:(NSString *)type forceCloseConnection:(BOOL)force;
- (void)terminateAllSessionsWithChannelType:(NSString *)type;

- (void)closeInactiveConnections;
- (void)closeInactiveConnectionsWithChannelType:(NSString *)type;
- (void)closingAction:(DIDeviceInteractionProcessorTerminateProtocol__Action)action filter:(id)filter;
/* the very awesome names, bbbitch!
- (void)abortSessionWithDeviceName:(NSString *)name;
- (void)abortSessionWithDeviceName:(NSString *)name withChannelType:(NSString *)type;
- (void)abortConnectionWithDeviceName:(NSString *)name withChannelType:(NSString *)type;
 */
@end

@protocol DIDeviceInteractionProcessorReopenProtocol <NSObject>

- (void)reopenStalledSessionWithDeviceName:(NSString *)name;
- (void)reopenAllStalledSessions;
// and alternative with channels
- (void)reopenStalledSessionWithDeviceName:(NSString *)name withChannelType:(NSString *)type;
- (void)reopenAllStalledSessionsWithChannelType:(NSString *)type;

@end

NS_ASSUME_NONNULL_END
