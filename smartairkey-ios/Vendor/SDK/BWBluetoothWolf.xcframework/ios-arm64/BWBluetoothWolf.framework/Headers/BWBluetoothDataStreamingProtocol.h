//
//  BWBluetoothDataStreamingProtocol.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 10.02.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;
#import <BWBluetoothWolf/AIKBluetoothMessage.h>
#import <BWBluetoothWolf/BWBluetoothDeprecations.h>

@protocol BWBluetoothDataStreamingProtocol <NSObject>
- (void)sendMessage:(AIKBluetoothMessage *)message withPeerName:(NSString *)name;
- (void)sendCheckMessage:(AIKBluetoothMessage *)message withPeerName:(NSString *)name;
@end

typedef struct {
    NSInteger sendMessageWithPeerName : 1;
} BWBluetoothDataStreamingProtocolFlags;

BWBluetoothDataStreamingProtocolFlags _createFlagsFrom_BWBluetoothDataStreamingProtocol(id<BWBluetoothDataStreamingProtocol> item);

@protocol BWBluetoothDataInspectionProtocol <NSObject>
- (NSString *)peerNameWithName:(NSString *)name;
@end

typedef struct {
    NSInteger peerNameWithName : 1;
} BWBluetoothDataInspectionProtocolFlags;

BWBluetoothDataInspectionProtocolFlags _createFlagsFrom_BWBluetoothDataInspectionProtocol(id<BWBluetoothDataInspectionProtocol> item);
