//
//  TCTransportDataStreamer.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 15.10.15.
//  Copyright © 2015 AirkeyTeam. All rights reserved.
//

@import Foundation;
@import BWBluetoothWolf;
//#import <BWBluetoothWolf/BWBluetoothIOProtocolExtension.h>
//#import <BWBluetoothWolf/BWBluetoothDataStreamingProtocol.h>

#import <TCTransportCamel/TCTransportDataStreamingProtocol.h>
#import <TCTransportCamel/TCTransportCoderProtocol.h>


/* 
 *	TODO: move to transport part (it knows how to code and decode messages)
 *	Also, cleanup all protocols like 'Bluetooth Central Manager IO Protocol' (it is not 'BluetoothCentral protocol, it is DataStreamingInput and DataStreamingOutput')
 *	Also, add special protocol for Bluetooth Central like changing state and did send data to peripheral characteristic
 *	Also, don't forget to change 'Bluetooth restartConnections to startConnections' in BaseKeysItems fetchedResults didchange content.
 *	And don't forget to put [Bluetooth restartConnections] to completion block in reload data.
 *	And after all, add for user 'modified and created' fields
 *	Possibly, rename rssiObserver -> (remove Bluetooth suffix)
 */
@interface TCTransportDataStreamer : NSObject<BWBluetoothIOProtocol, TCTransportDataStreamingProtocol>

- (instancetype)initWithDataStreamingDelegate:(id<BWBluetoothDataStreamingProtocol>)dataStreamingDelegate withTransportCoder:(id<TCTransportCoderProtocol>)coder;
- (instancetype)initWithDataStreamingDelegate:(id<BWBluetoothDataStreamingProtocol>)dataStreamingDelegate withTransportCoder:(id<TCTransportCoderProtocol>)coder withConnectionType:(TCTransportDataStreamingType *)type;

@property (weak, nonatomic) id <BWBluetoothDataStreamingProtocol> dataStreamingDelegate;
@property (strong, nonatomic, readonly) BWBluetoothMessageTransferProtocolExtension *simpleMessageReceivingHandler;
@property (strong, nonatomic, readonly) BWBluetoothMessageTransferProtocolExtension *wrappedMessageReceivingHandler;
@property (strong, nonatomic, readonly)
   BWBluetoothMessageTransferProtocolExtension *wrappedWithFilterMessageReceivingHandler;
@property (copy, nonatomic, readonly) TCTransportDataStreamingType *type;
@property (atomic) BOOL isV3;
@end
