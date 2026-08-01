//
//  BWBluetoothWolfConnectionManagerProtocol.h
//  BWBluetoothWolf
//
//  Created by Lobanov Dmitry on 22.04.16.
//  Copyright © 2016 SmartAirkey. All rights reserved.
//

@import Foundation;
#import <BWBluetoothWolf/BWBluetoothWolfConnection.h>
#import <BWBluetoothWolf/BWBluetoothDeprecations.h>

@protocol BWBluetoothWolfConnectionManagerStateProtocol <NSObject>

@optional - (void)connection:(BWBluetoothWolfConnection *)connection changeState:(BWBluetoothWolfConnectionState)state;
@optional - (void)connection:(BWBluetoothWolfConnection *)connection changeState:(BWBluetoothWolfConnectionState)state withPeerName:(NSString *)name;
@end

@protocol BWBluetoothWolfConnectionManagerIOInputProtocol <NSObject>

@optional - (void)connection:(BWBluetoothWolfConnection *)connection didSendData:(NSData *)data withPeerName:(NSString *)name withError:(NSError *)error withConnectionType:(NSString *)type;

@end

@protocol BWBluetoothWolfConnectionManagerIOOutputProtocol <NSObject>
@optional - (void)connection:(BWBluetoothWolfConnection *)connection didReceiveData:(NSData *)data withPeerName:(NSString *)name withError:(NSError *)error withConnectionType:(NSString *)type;
@end

@protocol BWBluetoothWolfConnectionManagerIOProtocol <BWBluetoothWolfConnectionManagerIOInputProtocol, BWBluetoothWolfConnectionManagerIOOutputProtocol>
@end

typedef struct {
    NSInteger connectionChangeState : 1;
    NSInteger connectionChangeStateWithPeerName : 1;
} BWBluetoothWolfConnectionManagerStateProtocolFlags;

BWBluetoothWolfConnectionManagerStateProtocolFlags createFlagsFromBWBluetoothWolfConnectionManagerStateProtocol(id<BWBluetoothWolfConnectionManagerStateProtocol> item);

typedef struct {
    NSInteger connectionDidSendDataWithPeerNameWithErrorWithConnectionType : 1;
    NSInteger connectionDidReceiveDataWithPeerNameWithErrorWithConnectionType : 1;
} BWBluetoothWolfConnectionManagerIOProtocolFlags;

BWBluetoothWolfConnectionManagerIOProtocolFlags _createFlagsFrom_BWBluetoothWolfConnectionManagerIOProtocol(id<BWBluetoothWolfConnectionManagerIOProtocol> item);
