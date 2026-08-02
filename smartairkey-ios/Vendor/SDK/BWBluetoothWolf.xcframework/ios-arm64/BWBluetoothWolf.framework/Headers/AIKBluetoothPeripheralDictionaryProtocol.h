//
//  AIKBluetoothPeripheralDictionaryProtocol.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 14.03.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;

@protocol AIKBluetoothTransportProtocol <NSObject>

@property(nonatomic, strong, readonly) NSString *deviceName;
@property(nonatomic, strong, readonly) NSString *charDataUuid;
@property(nonatomic, strong, readonly) NSString *serviceUuid;
@property(nonatomic, strong, readonly) NSString *charRssiUuid;

@end

typedef struct {
	NSInteger deviceName : 1;
	NSInteger charDataUuid : 1;
	NSInteger serviceUuid : 1;
	NSInteger charRssiUuid : 1;
} AIKBluetoothTransportProtocolFlags;

AIKBluetoothTransportProtocolFlags createFlagsFromAIKBluetoothTransportProtocol(id<AIKBluetoothTransportProtocol> item);
