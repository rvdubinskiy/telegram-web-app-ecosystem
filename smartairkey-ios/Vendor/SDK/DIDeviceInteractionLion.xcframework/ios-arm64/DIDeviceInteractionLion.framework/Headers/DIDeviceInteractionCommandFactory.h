//
//  DIDeviceInteractionCommandFactory.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 08.09.15.
//  Copyright (c) 2015 AirkeyTeam. All rights reserved.
//

@import Foundation;
#import "DIDeviceInteractionCommand.h"
#import "DIDeviceInteractionEntitiesProtocols.h"

@interface DIDeviceInteractionCommandFactory : NSObject

+ (DIDeviceInteractionCommand *)openLockCommandWithDeviceInformation:(id<DIDeviceInteractionEntityDeviceInformationProtocol>)deviceInformation;

+ (DIDeviceInteractionCommand *)closeLockCommandWithDeviceInformation:(id<DIDeviceInteractionEntityDeviceInformationProtocol>)deviceInformation;

+ (DIDeviceInteractionCommand *)settingsLockCommandWithDeviceInformation:(id<DIDeviceInteractionEntityDeviceInformationProtocol>)deviceInformation;

+ (DIDeviceInteractionCommand *)smartDoorDeviceInformation:
    (id<DIDeviceInteractionEntityDeviceInformationProtocol>)deviceInformation;

@end
