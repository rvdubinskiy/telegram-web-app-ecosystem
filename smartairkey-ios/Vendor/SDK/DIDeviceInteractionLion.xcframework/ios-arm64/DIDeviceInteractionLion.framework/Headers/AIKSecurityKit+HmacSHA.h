//
//  AIKSecurityKit+HmacSHA.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 21.10.15.
//  Copyright © 2015 AirkeyTeam. All rights reserved.
//

#import "AIKSecurityKit.h"

typedef NS_ENUM(NSInteger, AIKSecurityHmacAlgorithm) {
    AIKSecurityHmacAlgorithmSHA1,
    AIKSecurityHmacAlgorithmMD5,
    AIKSecurityHmacAlgorithmSHA256,
    AIKSecurityHmacAlgorithmSHA384,
    AIKSecurityHmacAlgorithmSHA512,
    AIKSecurityHmacAlgorithmSHA224
};

@interface AIKSecurityKit (HmacSHA)

+ (NSData *)HmacSHADataOnAlgorithm:(AIKSecurityHmacAlgorithm)algorithm withString:(NSString *)string withKey:(NSString *)key;
+ (NSString *)HmacSHAStringOnAlgorithm:(AIKSecurityHmacAlgorithm)algorithm withString:(NSString *)string withKey:(NSString *)key;

+ (NSData *)HmacSHADataOnAlgorithm:(AIKSecurityHmacAlgorithm)algorithm withData:(NSData *)data withKey:(NSString *)key;
+ (NSData *)HmacSHADataOnAlgorithm:(AIKSecurityHmacAlgorithm)algorithm withData:(NSData *)data withKeyData:(NSData *)key;
@end
