//
//  AIKBluetoothTransportCoderProtocol.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 25.07.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;

typedef NS_ENUM(NSInteger, TCTransportCoderVersion) {
    TCTransportCoderVersionPure,
    TCTransportCoderVersionGZIP
};

@protocol TCTransportCoderProtocol <NSObject>
- (NSData *)packedMessageWithSourceData:(NSData *)data;
- (NSData *)unpackedMessageWithSourceData:(NSData *)data;
@end