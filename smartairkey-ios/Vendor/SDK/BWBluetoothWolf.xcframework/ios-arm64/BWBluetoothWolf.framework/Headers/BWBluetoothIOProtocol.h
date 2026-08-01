//
//  BWBluetoothIOProtocol.h
//  BWBluetoothWolf
//
//  Created by Lobanov Dmitry on 23.08.16.
//  Copyright © 2016 SmartAirkey. All rights reserved.
//

@import Foundation;
#import <BWBluetoothWolf/AIKBluetoothMessage.h>

@protocol BWBluetoothIOInputProtocol <NSObject>

- (void)didSendData:(NSData *)data withPeerName:(NSString *)name withError:(NSError *)error;

@end

@protocol BWBluetoothIOOutputProtocol <NSObject>

- (void)didReadRSSI:(NSNumber *)rssi withPeerName:(NSString *)name withError:(NSError *)error;
- (void)didReceiveData:(NSData *)data withPeerName:(NSString *)name withError:(NSError *)error;

@end

@protocol BWBluetoothIOProtocol <BWBluetoothIOInputProtocol, BWBluetoothIOOutputProtocol>

@end

typedef struct {
    NSInteger didSendDataWithPeerNameWithError : 1;
    NSInteger didReadRSSIWithPeerNameWithError : 1;
    NSInteger didReceiveDataWithPeerNameWithError : 1;
} BWBluetoothIOProtocolFlags;

BWBluetoothIOProtocolFlags _createFlagsFrom_BWBluetoothIOProtocol(id<BWBluetoothIOProtocol> item);

@protocol BWBluetoothMessageTransferProtocol <NSObject>

- (BOOL)isMessage:(AIKBluetoothMessage *)message notCompleteWithData:(NSData *)data;
- (BOOL)isMessage:(AIKBluetoothMessage *)message firstWithData:(NSData *)data;
@optional
- (AIKBluetoothMessage *)firstMessage:(AIKBluetoothMessage *)message withData:(NSData *)data;
- (AIKBluetoothMessage *)updatedMessage:(AIKBluetoothMessage *)message withData:(NSData *)data;
- (AIKBluetoothMessage *)message:(AIKBluetoothMessage *)message completedWithData:(NSData *)data;
- (NSError *)errorForMessage:(AIKBluetoothMessage *)message withData:(NSData *)data;
@end

typedef struct {
    NSInteger isMessageNotCompleteWithData : 1;
    NSInteger isMessageFirstWithData : 1;
    NSInteger firstMessageWithData : 1;
    NSInteger updatedMessageWithData : 1;
    NSInteger messageCompletedWithData : 1;
} BWBluetoothMessageTransferProtocolFlags;

BWBluetoothMessageTransferProtocolFlags _createFlagsFrom_BWBluetoothMessageTransferProtocol(id<BWBluetoothMessageTransferProtocol> item);
