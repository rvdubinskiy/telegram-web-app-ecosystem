//
//  AIKBluetoothMessageReceivingHandler.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 15.10.15.
//  Copyright © 2015 AirkeyTeam. All rights reserved.
//

@import Foundation;
@import BWBluetoothWolf;
//#import <BWBluetoothWolf/BWBluetoothIOProtocolExtension.h>
#import <TCTransportCamel/TCTransportCoderProtocol.h>

@interface TCTransportDummyMessageReceivingHandler : BWBluetoothMessageTransferProtocolExtension
- (AIKBluetoothMessage *)createOrUpdateMessage:(AIKBluetoothMessage *)message withData:(NSData *)data;
@property (weak, nonatomic, readwrite) id<TCTransportCoderProtocol>coder;
@end

@interface TCTransportSimpleMessageReceivingHandler : TCTransportDummyMessageReceivingHandler
@end

@interface TCTransportWrappedMessageReceivingHandler : TCTransportDummyMessageReceivingHandler
@end

@interface TCTransportWrappedMessageWithLengthConstraintsReceivingHandler : TCTransportWrappedMessageReceivingHandler 
@end
