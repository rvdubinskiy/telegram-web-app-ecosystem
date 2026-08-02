//
//  AIKSecurityKit+SmartDevice.h
//  DIDeviceInteractionLion
//
//  Created by Антон Текутов on 18.11.2024.
//  Copyright © 2024 Dmitry. All rights reserved.
//

#import "DIDeviceInteractionEntitiesProtocols.h"
#import "DIDeviceInteractionStructureSmartDeviceData.h"
#import "AIKSecurityKit.h"

@interface AIKSecurityKit (SmartDevice)

+ (DIDeviceInteractionStructureSmartDeviceData*)generateSmartDeviceData:(NSData*)lockPublicKey;

@end
