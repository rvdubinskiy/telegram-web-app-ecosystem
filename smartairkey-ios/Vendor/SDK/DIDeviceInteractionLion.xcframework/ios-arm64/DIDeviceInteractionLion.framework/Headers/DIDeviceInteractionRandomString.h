//
//  DIDeviceInteractionRandomString.h
//  DIDeviceInteractionLion
//
//  Created by Dmitry on 08.04.17.
//  Copyright © 2017 Dmitry. All rights reserved.
//

@import Foundation;

@interface DIDeviceInteractionRandomString : NSObject
+ (NSString *)createSaltString;
+ (NSString *)createUUIDString;
+ (NSString *)createSaltStringWithLengthLimit:(NSInteger)limit;

- (NSString *)createSaltString;
- (NSString *)createUUIDString;
- (NSString *)createSaltStringWithLengthLimit:(NSInteger)limit;
@end

@interface DIDeviceInteractionRandomString (Create)
+ (instancetype)createForDefault;
+ (instancetype)createForSalt;
@end
