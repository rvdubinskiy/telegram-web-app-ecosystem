//
//  AIKSecurityKit.h
//  Airkey
//
//  Created by Lobanov Dmitry on 17.06.15.
//  Copyright (c) 2015 AirkeyTeam. All rights reserved.
//

@import Foundation;

@interface AIKSecurityKit : NSObject

+ (NSData *)AES128EncryptData:(NSData *)data withKey:(NSData *)key;
//
//+ (NSString *)base64StringFromString:(NSString *)string;
//
//+ (NSData *)base64DataFromString:(NSString *)string;
//
//+ (NSString *)base64StringFromData:(NSData *)data;
//
//+ (NSData *)base64DataFromData:(NSData *)data;
//
//+ (NSData *)hmacSha256DataFromString:(NSString *)value andKey:(NSString *)key;
//
//+ (NSString *)base64HmacSha256StringFromString:(NSString *)value andKey:(NSString *)key;
//
//
//// thanks for http://www.xappsoftware.com/wordpress/2012/04/26/how-to-use-sha1-and-md5-in-ios-applications/
//+ (NSString *)SHA1StringFromString:(NSString *)fromString;
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
//
//#pragma mark - JWT
//extern NSString * const AIKJWTNone;
//extern NSString * const AIKJWTHMacSHA256;
//extern NSString * const AIKJWTHMacSHA512;
//+ (NSString *)JWTEncodePayload:(NSDictionary *)payload withSecret:(NSString *)secret withHeaders:(NSDictionary *)headers algorithm:(NSString *)algorithm;
//
//+ (NSDictionary *)JWTDecodeMessage:(NSString *)message withSecret:(NSString *)secret withError:(NSError *__autoreleasing *)error;
//
//+ (NSDictionary *)JWTDecodeMessage:(NSString *)message withSecret:(NSString *)secret;
//
//+ (NSDictionary *)JWTDecodeMessageHeaders:(NSString *)message;

@end
