//
//  DIDeviceInteractionStructureDerivedSignatureKey.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 15.09.15.
//  Copyright (c) 2015 AirkeyTeam. All rights reserved.
//

@import Foundation;
#import "DIDeviceInteractionEntitiesProtocols.h"

@interface DIDeviceInteractionStructureDerivedSignatureKey : NSObject< DIDeviceInteractionEntityDerivedSignatureKeyProtocol__Mutable, NSCopying>

- (NSString *)signMessage:(NSString *)message;
- (instancetype)createWithBase64Salt:(NSString *)salt;
- (instancetype)createWithSalt:(NSString *)salt __deprecated_msg("createWithSalt deprecated. it will be replaced by base64 encoded strings or binary representation. Now it used as an entry point.");
+ (instancetype)createWithSigningKey:(id<DIDeviceInteractionEntityDerivedSignatureKeyProtocol>)key;

@end
