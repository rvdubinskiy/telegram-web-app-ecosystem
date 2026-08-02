//
//  AIKSecurityKit+DigestSHA.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 05.04.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

#import "AIKSecurityKit.h"

@interface AIKSecurityKit (DigestSHA)

+ (NSString *)SHA1StringFromString:(NSString *)fromString;

@end
