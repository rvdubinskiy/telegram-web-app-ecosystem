//
//  AIKSecurityKit+OldMethods.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 21.10.15.
//  Copyright © 2015 AirkeyTeam. All rights reserved.
//

#import "AIKSecurityKit.h"

@interface AIKSecurityKit (OldMethods)
//
+ (NSData *)hmacSha256DataFromString:(NSString *)value andKey:(NSString *)key;

+ (NSString *)base64HmacSha256StringFromString:(NSString *)value andKey:(NSString *)key;
//
//
//// thanks for http://www.xappsoftware.com/wordpress/2012/04/26/how-to-use-sha1-and-md5-in-ios-applications/
//+ (NSString *)__old__SHA1StringFromString:(NSString *)fromString;
//
//// thanks for https://gist.github.com/matsuda/9204276
//+ (NSData *)AES128EncryptData:(NSData *)data withKey:(NSString *)key;
//
//+ (NSData *)AES128DecryptData:(NSData *)data withKey:(NSString *)key;
//
//+ (NSData *)AES128EncryptData:(NSData *)data withKey:(NSString *)key iv:(NSString *)iv;
//
//+ (NSData *)AES128DecryptData:(NSData *)data withKey:(NSString *)key iv:(NSString *)iv;
//
//// strings encryption
//+ (NSString *)AES128EncryptString:(NSString *)string withKey:(NSString *)key;
//
//+ (NSString *)AES128DecryptString:(NSString *)string withKey:(NSString *)key;
//
//+ (NSString *)AES128EncryptString:(NSString *)string withKey:(NSString *)key iv:(NSString *)iv;
//
//+ (NSString *)AES128DecryptString:(NSString *)string withKey:(NSString *)key iv:(NSString *)iv;
//
//#pragma mark - RNCryptor
//extern NSUInteger const AIKAlgSHA1;
//extern NSUInteger const AIKAlgSHA256;
//+ (NSString *)Alg:(uint32_t)alg encryptString:(NSString *)pureString withPassword:(NSString *)password;
//
//+ (NSString *)AES256EncryptString:(NSString *)pureString withPassword:(NSString *)password;
//
//+ (NSString *)AES256DecryptString:(NSString *)encryptedString withPassword:(NSString *)password;
@end

