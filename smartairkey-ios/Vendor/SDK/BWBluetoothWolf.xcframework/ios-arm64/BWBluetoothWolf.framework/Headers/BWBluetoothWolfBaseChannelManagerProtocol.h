//
//  BWBluetoothWolfBaseChannelManagerProtocol.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 09.02.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;
#import <BWBluetoothWolf/AIKBluetoothPeripheralDictionaryProtocol.h>

typedef NS_ENUM(NSUInteger, BWBluetoothWolfBaseChannelManagerState) {
    BWBluetoothWolfBaseChannelManagerStateDisconnected,
    BWBluetoothWolfBaseChannelManagerStateDiscovered,
    BWBluetoothWolfBaseChannelManagerStateConnecting,
    BWBluetoothWolfBaseChannelManagerStateConnected,
    // unknown
    BWBluetoothWolfBaseChannelManagerStateInactive,
    BWBluetoothWolfBaseChannelManagerStateClosed,
    BWBluetoothWolfBaseChannelManagerStateOpened
};

@interface BWBluetoothWolfBaseChannelManagerStateDescription : NSObject

+ (NSString *)stringForState:(BWBluetoothWolfBaseChannelManagerState)state;

@end

@class BWBluetoothWolfBaseChannelManager;

@protocol BWBluetoothWolfBaseChannelManagerStateProtocol <NSObject>

- (void)channelManager:(BWBluetoothWolfBaseChannelManager *)manager didChangeState:(BWBluetoothWolfBaseChannelManagerState)state withPeerName:(NSString *)name;

@end

@protocol BWBluetoothWolfBaseChannelManagerDiscoveryProtocol <NSObject>

- (BOOL)shouldConnectToDeviceWithName:(NSString *)name;
- (BOOL)shouldSkipDiscoveryOnDeviceWithName:(NSString *)name;
- (id<AIKBluetoothTransportProtocol>)profileForDeviceWithName:(NSString *)name;
- (BOOL)hasV3TokenFor:(NSString *)name;

@end
@protocol BWBluetoothWolfBaseChannelManagerEstablishmentProtocol <NSObject>
- (void)didDiscoverDeviceWithName:(NSString *)deviceName;
- (void)didDiscoverDeviceWithName:(NSString *)deviceName advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)rssi;
@end

typedef struct {
    NSInteger channelManagerDidChangeStateWithPeerName : 1;
} BWBluetoothWolfBaseChannelManagerStateProtocolFlags;

typedef struct {
    NSInteger shouldConnectToDeviceWithName : 1;
    NSInteger shouldSkipDiscoveryOnDeviceWithName: 1;
    NSInteger profileForDeviceWithName : 1;
} BWBluetoothWolfBaseChannelManagerDiscoveryProtocolFlags;

typedef struct {
    NSInteger didDiscoverDeviceWithName : 1;
    NSInteger didDiscoverDeviceWithName_advertisementData_RSSI : 1;
} BWBluetoothWolfBaseChannelManagerEstablishmentProtocolFlags;

BWBluetoothWolfBaseChannelManagerStateProtocolFlags _createFlagsFrom_BWBluetoothWolfBaseChannelManagerStateProtocol(id<BWBluetoothWolfBaseChannelManagerStateProtocol> item);

BWBluetoothWolfBaseChannelManagerDiscoveryProtocolFlags _createFlagsFrom_BWBluetoothWolfBaseChannelManagerDiscoveryProtocol(id<BWBluetoothWolfBaseChannelManagerDiscoveryProtocol> item);

BWBluetoothWolfBaseChannelManagerEstablishmentProtocolFlags _createFlagsFrom_BWBluetoothWolfBaseChannelManagerEstablishmentProtocolFlags(id<BWBluetoothWolfBaseChannelManagerEstablishmentProtocol> item);
