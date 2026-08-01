//
//  DIDeviceInteractionCommandRunner.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 08.09.15.
//  Copyright (c) 2015 AirkeyTeam. All rights reserved.
//

@import Foundation;
#import "DIDeviceInteractionCommand.h"
@import BWBluetoothWolf;
#import "DIDeviceInteractionCommandProcessorProtocols.h"
#import "DIDeviceInteractionCommandRunnerProtocols.h"
#import "DIDeviceInteractionProcessorBase.h"
#import "DIDeviceInteractionStructureAccessTokenV3.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 *
 * @class DIDeviceInteractionCommandRunner
 *
 * @discussion Provides interface for top-level message sending to Lock.
 * It operates with AIKLockCommand subclasses
 *
 * @seealso AIKLockCommand
 *
 */
@interface DIDeviceInteractionCommandRunner : NSObject
- (void)setup;
- (void)executeCommand:(DIDeviceInteractionCommand *)action;
@end

@interface DIDeviceInteractionCommandRunner (Locks)
- (void)executeOpenOnLockWithName:(NSString *)lockName;
- (void)executeCloseOnLockWithName:(NSString *)lockName;
- (void)executeSettingsCommandOnLockWithName:(NSString *)lockName;
- (void)executeRequestSmartDoorPublicKey:(NSString *)lockName;
@end

@interface DIDeviceInteractionCommandRunner (Configuration)
- (void)execute__Configuration__GetWithDeviceName:(NSString *)deviceName;
- (void)execute__Configuration__SetWithDeviceName:(NSString *)deviceName configuration:(id)configuration;
@end

@interface DIDeviceInteractionCommandRunner (BWBluetoothWolfConfiguration)

- (BWBluetoothWolfConfiguration *)connectedConfiguration:(BWBluetoothWolfConfiguration *)configuration;

@end

@interface DIDeviceInteractionCommandRunner (PrivateCommandProcessor)
@property (strong, nonatomic, readonly) DIDeviceInteractionProcessorBase *commandProcessor;
@end

@interface DIDeviceInteractionCommandRunner (PeripheralManagerDataProvider)
@property (strong, nonatomic, readwrite) id<DIDeviceInteractionCommandRunnerPeripheralManagerDataProvider> peripheralManagerDataProvider;
@end

@interface DIDeviceInteractionCommandRunner (DIDeviceInteractionProcessorDeviceInformationProvider__Fetching__Protocol) <DIDeviceInteractionProcessorDeviceInformationProvider__Fetching__Protocol>
@end

@interface DIDeviceInteractionCommandRunner (Create)
+ (instancetype)createRunner;
@end
NS_ASSUME_NONNULL_END
