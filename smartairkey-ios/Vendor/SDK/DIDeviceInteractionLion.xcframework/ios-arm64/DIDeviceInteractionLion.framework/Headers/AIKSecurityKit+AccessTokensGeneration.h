//
//  AIKSecurityKit+AccessTokensGeneration.h
//  DIDeviceInteractionLion
//
//  Created by Антон Текутов on 20.11.2024.
//  Copyright © 2024 Dmitry. All rights reserved.
//

#import "AIKSecurityKit.h"
#import "DIDeviceInteractionStructureAccessTokenV3.h"

@interface AIKSecurityKit (AccessTokensGeneration)
+ (NSData *)createAccessToken:(NSData *)clientSalt
                    validFrom:(uint32_t)validFrom
                      validTo:(uint32_t)validTo
                    masterKey:(NSData *)masterKey
                       userId:(int)userId
                      isAdmin:(BOOL)isAdmin;

+ (DIDeviceInteractionStructureAccessTokenV3 *)createAccessTokenV3:(uint32_t)validFrom
                               validTo:(uint32_t)validTo
                             masterKey:(NSData *)masterKey
                                userId:(int)userId
                               isAdmin:(BOOL)isAdmin;
@end
