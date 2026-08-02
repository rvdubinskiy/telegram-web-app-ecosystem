//
//  TCTransportDataStreamingManager.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 27.04.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;
@import BWBluetoothWolf;
//#import <BWBluetoothWolf/BWBluetoothIOProtocol.h>
//#import <BWBluetoothWolf/BWBluetoothWolfConnectionManagerProtocol.h>
//#import <BWBluetoothWolf/BWBluetoothIOProtocolExtension.h>

#import <TCTransportCamel/TCTransportCoderProtocol.h>
#import <TCTransportCamel/TCTransportDataStreamingManagerProtocol.h>
#import <TCTransportCamel/TCTransportDataStreamingProtocol.h>

@interface TCTransportDataStreamerConnection : NSObject
@property (strong, nonatomic, readwrite) id<TCTransportDataStreamingProtocol> dataStreaming;
@property (strong, nonatomic, readwrite) NSNumber *state;
@end

@protocol TCTransportDataStreamingConnectionsProtocol <NSObject>
- (TCTransportDataStreamerConnection *)objectForKeyedSubscript:(id <NSCopying>)key;
@end

@interface TCTransportDataStreamingManager : NSObject

- (instancetype)initWithStateDelegate:(id<TCTransportDataStreamingManagerStateProtocol>)stateDelegate;
- (instancetype)_initWithStateDelegate:(id<TCTransportDataStreamingManagerStateProtocol>)stateDelegate withWriter:(id<BWBluetoothIOInputProtocol>)writer withReader:(id<BWBluetoothIOOutputProtocol>)reader;
- (instancetype)initWithStateDelegate:(id<TCTransportDataStreamingManagerStateProtocol>)stateDelegate withWriter:(id<TCTransportDataStreamingIOInputProtocol>)writer withReader:(id<TCTransportDataStreamingIOOutputProtocol>)reader;

@property (weak, nonatomic, readwrite) id<TCTransportDataStreamingManagerStateProtocol> stateDelegate;
@end

@interface TCTransportDataStreamingManager (Accessors)
@property (nonatomic, readonly) id<TCTransportDataStreamingConnectionsProtocol> defaultConnections;
@property (nonatomic, readonly) id<TCTransportDataStreamingConnectionsProtocol> fromPeripheralConnections;
@property (nonatomic, readonly) id<TCTransportDataStreamingConnectionsProtocol> fromCentralConnections;
- (id<TCTransportDataStreamingConnectionsProtocol>)objectForKeyedSubscript:(id<NSCopying>)key;
@end

@interface TCTransportDataStreamingManager (Channels)
@property (strong, nonatomic, readonly) NSArray *activeChannelNames;
- (id<TCTransportDataStreamingProtocol>)channelForKeyedSubscript:(id<NSCopying>)key;
- (id<TCTransportDataStreamingProtocol>)channelForKeyedSubscript:(id <NSCopying>)key withType:(TCTransportDataStreamingType *)type;
@end

@interface TCTransportDataStreamingManager (DataStreaming)

@property (strong, nonatomic, readonly) BWBluetoothMessageTransferProtocolExtension *simpleMessageReceivingHandler;
@property (strong, nonatomic, readonly) BWBluetoothMessageTransferProtocolExtension *wrappedMessageReceivingHandler;
@property (strong, nonatomic, readonly) BWBluetoothMessageTransferProtocolExtension *wrappedWithFilterMessageReceivingHandler;

@end

@interface TCTransportDataStreamingManager (Coding)

- (void)updateCoderWithVersion:(TCTransportCoderVersion)version;

@end

@interface TCTransportDataStreamingManager (BWBluetoothWolfConnectionManagerStateProtocol) <BWBluetoothWolfConnectionManagerStateProtocol>

@end

@interface TCTransportDataStreamingManager (BWBluetoothIOProtocol) <BWBluetoothIOProtocol>
@end

@interface TCTransportDataStreamingManager (BWBluetoothWolfConnectionManagerIOProtocol) <BWBluetoothWolfConnectionManagerIOProtocol>
@end

