//
//  BWBluetoothIOProtocolExtension.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 11.01.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;
@import CoreBluetooth;
#import <BWBluetoothWolf/BWBluetoothIOProtocol.h>
//BONE TODO: Later fix it and make parameter type not id but AIKBluetoothPeripheralDictionary
//#import "AIKBluetoothPeripheralDictionary.h"

//TODO: RENAME LATER
//peripheralDictionary to peerDictionary or peer?
//Remove peer from here ( it will be needed later? )
//It will be needed for internal usage.
//Clean extension only need message composition? (!)
@interface BWBluetoothMessageTransferProtocolExtension : NSObject<BWBluetoothMessageTransferProtocol>
- (void)peer:(id)peer didReceivePartData:(NSData *)data toCharacteristic:(CBCharacteristic *)characteristic withFlags:(BWBluetoothMessageTransferProtocolFlags)messageReceivingFlags withDelegate:(id<BWBluetoothIOProtocol>)delegate;

- (void)peer:(id)peer didReceivePartData:(NSData *)data toCharacteristic:(CBCharacteristic *)characteristic withDelegate:(id<BWBluetoothIOProtocol>)delegate;

@end

@interface BWBluetoothMessageStreamingProtocolExtension : NSObject<BWBluetoothMessageTransferProtocol>

- (AIKBluetoothMessage *)createOrUpdateMessage:(AIKBluetoothMessage *)message withData:(NSData *)data;

// internal
- (void)peer:(id)peer didReceivePartData:(NSData *)data toCharacteristic:(CBCharacteristic *)characteristic withFlags:(BWBluetoothMessageTransferProtocolFlags)messageReceivingFlags withDelegate:(id<BWBluetoothIOProtocol>)delegate;

@end
