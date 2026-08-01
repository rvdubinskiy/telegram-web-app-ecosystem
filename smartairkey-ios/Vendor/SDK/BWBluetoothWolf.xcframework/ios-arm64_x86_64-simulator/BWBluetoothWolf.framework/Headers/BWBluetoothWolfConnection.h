//
//  BWBluetoothWolfConnection.h
//  BWBluetoothWolf
//
//  Created by Lobanov Dmitry on 20.04.16.
//  Copyright © 2016 SmartAirkey. All rights reserved.
//

@import Foundation;
#import <BWBluetoothWolf/BWBluetoothWolfConnectionProtocol.h>
#import <BWBluetoothWolf/BWBluetoothDataStreamingProtocol.h>
#import <BWBluetoothWolf/AIKBluetoothMessage.h>

/**
 enum BWBluetoothWolfConnectionState

 - BWBluetoothWolfConnectionStateOpened:     // connection open. could send data
 - BWBluetoothWolfConnectionStateClosed:     // connection closed. could not send data.
 - BWBluetoothWolfConnectionStateDiscovered: // connection discovered. could be opened.
 */
typedef NS_ENUM(NSInteger, BWBluetoothWolfConnectionState){
    BWBluetoothWolfConnectionStateClosed,
    BWBluetoothWolfConnectionStateOpened,
    BWBluetoothWolfConnectionStateDiscovered
};

typedef NSString BWBluetoothWolfConnectionType;

@interface BWBluetoothWolfConnectionStateDescription : NSObject

+ (NSString *)stringForState:(BWBluetoothWolfConnectionState)state;

@end

@interface BWBluetoothWolfConnectionTypes : NSObject
@property (copy, nonatomic, readonly, class) BWBluetoothWolfConnectionType *AsPeripheral; // Default as peripheral
@property (copy, nonatomic, readonly, class) BWBluetoothWolfConnectionType *AsCentral;
@end

@interface BWBluetoothWolfConnection : NSObject <BWBluetoothDataStreamingProtocol>

#pragma mark - Public
- (void)sendMessage:(AIKBluetoothMessage *)message;
@property (assign, nonatomic, readonly) BWBluetoothWolfConnectionState state;
@property (weak, nonatomic, readonly) NSString *deviceName;
@property (weak, nonatomic, readwrite) id<BWBluetoothWolfConnectionIOProtocol> ioDelegate;
@property (weak, nonatomic, readonly) id<BWBluetoothDataStreamingProtocol> dataStreamingDelegate;
@property (copy, nonatomic, readonly) BWBluetoothWolfConnectionType *connectionType;
@property (atomic) BOOL isV3;
@end

@interface BWBluetoothWolfConnection (BWBluetoothWolfConnectionIOProtocol) <BWBluetoothWolfConnectionIOProtocol>
@end
