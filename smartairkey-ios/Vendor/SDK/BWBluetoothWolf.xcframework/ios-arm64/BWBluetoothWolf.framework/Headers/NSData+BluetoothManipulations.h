//
//  NSData+BluetoothManipulations.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 20.03.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;

@interface NSData (BluetoothManipulations)

// thanks for answer: http://stackoverflow.com/questions/1305225/best-way-to-serialize-a-nsdata-into-an-hexadeximal-string
+ (NSString *)hexadecimalStringFromData:(NSData *)data;
@property(nonatomic, readonly) NSString *hexadecimalString;

#pragma mark - Number conversions
+ (NSInteger)integerFromData:(NSData *)data;
+ (NSData *)dataFromInteger:(NSInteger)value;
@property(nonatomic, readonly) NSInteger integerValue;

+ (SInt8)int8FromData:(NSData *)data;
+ (NSData *)dataFromInt8:(SInt8)value;
@property(nonatomic, readonly) SInt8 int8Value;
@end
