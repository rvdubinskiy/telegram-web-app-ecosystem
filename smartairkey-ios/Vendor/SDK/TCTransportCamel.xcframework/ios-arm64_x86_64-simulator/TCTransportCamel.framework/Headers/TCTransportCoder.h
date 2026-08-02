//
//  AIKTransportBluetoothCoder.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 11.10.15.
//  Copyright © 2015 AirkeyTeam. All rights reserved.
//

@import Foundation;
#import <TCTransportCamel/TCTransportCoderProtocol.h>

@interface TCTransportCoder : NSObject <NSCopying, TCTransportCoderProtocol>

+ (NSNumber *)sizeOfData:(NSData *)data;
- (NSNumber *)sizeOfData:(NSData *)data;
+ (NSData *)littleEndianDataFromNumber:(NSNumber *)number;
- (NSData *)littleEndianDataFromNumber:(NSNumber *)number;
+ (NSNumber *)littleEndianEncodedNumberFromData:(NSData *)data;
- (NSNumber *)littleEndianEncodedNumberFromData:(NSData *)data;

@end

@interface TCTransportCoder (Creation)
+ (TCTransportCoder *)coderWithVersion:(TCTransportCoderVersion)version;
@end