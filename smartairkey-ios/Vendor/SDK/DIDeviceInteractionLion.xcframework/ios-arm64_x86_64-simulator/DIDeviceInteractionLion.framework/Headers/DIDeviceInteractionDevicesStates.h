//
//  DIDeviceInteractionDevicesStates.h
//  DIDeviceInteractionLion
//
//  Created by Dmitry on 05.04.17.
//  Copyright © 2017 Dmitry. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NSString* DIDeviceInteractionDevicesStateItem;

@interface DIDeviceInteractionDevicesStates : NSObject
@property(copy, nonatomic, readonly, class) DIDeviceInteractionDevicesStateItem StateUndefined;
@property(copy, nonatomic, readonly, class) DIDeviceInteractionDevicesStateItem StateInactive;
@property(copy, nonatomic, readonly, class) DIDeviceInteractionDevicesStateItem StateChannelDiscovered;
@property(copy, nonatomic, readonly, class) DIDeviceInteractionDevicesStateItem StateChannelConnecting;
@property(copy, nonatomic, readonly, class) DIDeviceInteractionDevicesStateItem StateChannelConnected;
@property(copy, nonatomic, readonly, class) DIDeviceInteractionDevicesStateItem StateDiscovered;
@property(copy, nonatomic, readonly, class) DIDeviceInteractionDevicesStateItem StateConnecting;
@property(copy, nonatomic, readonly, class) DIDeviceInteractionDevicesStateItem StateConnected;
@property(copy, nonatomic, readonly, class) DIDeviceInteractionDevicesStateItem StateOpened;
@property(copy, nonatomic, readonly, class) DIDeviceInteractionDevicesStateItem StateOpenOpening;
@property(copy, nonatomic, readonly, class) DIDeviceInteractionDevicesStateItem StateClosed;
@property(copy, nonatomic, readonly, class) DIDeviceInteractionDevicesStateItem StateError;
@property(copy, nonatomic, readonly, class) DIDeviceInteractionDevicesStateItem StateErrorUnauthorized;
@property(copy, nonatomic, readonly, class) DIDeviceInteractionDevicesStateItem StateSmartDoorCreated;
@end

