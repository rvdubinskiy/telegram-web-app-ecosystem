//
//  NSString+SecurityEncoding.h
//  Airkey
//
//  Created by Lobanov Dmitry on 17.06.15.
//  Copyright (c) 2015 AirkeyTeam. All rights reserved.
//

@import Foundation;

@interface NSString (SecurityEncoding)

- (NSString *)base64String;

- (NSData *)base64Data;

- (NSData *)hmacSha256DataWithKey:(NSString *)key;

- (NSString *)base64HmacSha256StringWithKey:(NSString *)key;

- (NSString *)digestSHA1;

@end
