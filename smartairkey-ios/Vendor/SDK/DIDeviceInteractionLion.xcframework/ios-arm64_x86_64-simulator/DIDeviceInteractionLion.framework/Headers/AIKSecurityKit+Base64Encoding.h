//
//  AIKSecurityKit+Base64Encoding.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 21.10.15.
//  Copyright © 2015 AirkeyTeam. All rights reserved.
//

#import "AIKSecurityKit.h"

@interface AIKSecurityKit (Base64Encoding)

+ (NSString *)base64StringFromString:(NSString *)string;

+ (NSData *)base64DataFromString:(NSString *)string;

+ (NSString *)base64StringFromData:(NSData *)data;

+ (NSData *)base64DataFromData:(NSData *)data;

@end
