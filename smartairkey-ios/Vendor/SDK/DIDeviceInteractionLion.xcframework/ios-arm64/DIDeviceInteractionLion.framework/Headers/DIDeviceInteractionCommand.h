//
//  DIDeviceInteractionCommand.h
//  Airkey
//
//  Created by Lobanov Dmitry on 15.06.15.
//  Copyright (c) 2015 AirkeyTeam. All rights reserved.
//

@import Foundation;
#import "DIDeviceInteractionEntitiesProtocols.h"

/*!
 * @class DIDeviceInteractionCommand
 *
 * @discussion This class encapsulates logic for command sending to locks over bluetooth connection
 * 
 */
@interface DIDeviceInteractionCommand : NSObject

/*!
 * @property deviceInformation
 *
 * @discussion Provided device information.
 * 
 */
@property(strong, nonatomic, readonly) id<DIDeviceInteractionEntityDeviceInformationProtocol> deviceInformation;

/*!
 * @method initWithDeviceInformation
 *
 * @discussion Designed Initializer
 *
 * @param deviceInformation Device information.
 *
 */
- (instancetype)initWithDeviceInformation:(id<DIDeviceInteractionEntityDeviceInformationProtocol>)deviceInformation;

@end
