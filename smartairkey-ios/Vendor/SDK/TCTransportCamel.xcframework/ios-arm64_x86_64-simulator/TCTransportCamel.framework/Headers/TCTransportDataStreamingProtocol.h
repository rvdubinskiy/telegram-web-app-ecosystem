//
//  TCTransportDataStreamingProtocol.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 10.05.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;

typedef NSString TCTransportDataStreamingType;

@interface TCTransportDataStreamingTypeDescription : NSObject
+ (NSString *)streamingTypeFromConnectionType:(NSString *)connectionType;
@end

@interface TCTransportDataStreamingTypes: NSObject
@property (copy, nonatomic, readonly, class) TCTransportDataStreamingType *BluetoothAsPeripheral; // Default as Peripheral?
@property (copy, nonatomic, readonly, class) TCTransportDataStreamingType *BluetoothAsCentral;
@end

@protocol TCTransportDataStreamingProtocol <NSObject>

//Modern
@optional - (void)sendBytes:(NSData *)bytes toDeviceWithName:(NSString *)name;
@optional - (void)sendCheckBytes:(NSData *)bytes toDeviceWithName:(NSString *)name;
@optional - (void)sendBytes:(NSData *)bytes andPackIt:(BOOL)packIt toDeviceWithName:(NSString *)name;
@property (atomic) BOOL isV3;
@end

typedef struct {
    NSInteger sendBytesToDeviceWithName : 1;
    NSInteger sendBytesAndPackItToDeviceWithName : 1;
    
} TCTransportDataStreamingProtocolFlags;

TCTransportDataStreamingProtocolFlags createFlagsFromTCTransportDataStreamingProtocol(id<TCTransportDataStreamingProtocol> item);

@protocol TCTransportDataStreamingIOOutputProtocol <NSObject>
@optional - (void)didReceiveData:(NSData *)data withPeerName:(NSString *)name withError:(NSError *)error withType:(NSString *)type;
@end

@protocol TCTransportDataStreamingIOInputProtocol <NSObject>
@optional - (void)didSendData:(NSData *)data withPeerName:(NSString *)name withError:(NSError *)error withType:(NSString *)type;
@end

@protocol TCTransportDataStreamingIOProtocol <TCTransportDataStreamingIOOutputProtocol, TCTransportDataStreamingIOInputProtocol>
@end

typedef struct {
    NSInteger didSendDataWithPeerNameWithErrorWithType : 1;
    NSInteger didReceiveDataWithPeerNameWithErrorWithType : 1;
} TCTransportDataStreamingIOProtocolFlags;

TCTransportDataStreamingIOProtocolFlags _createFlagsFrom_TCTransportDataStreamingIOProtocol(id<TCTransportDataStreamingIOProtocol> item);
