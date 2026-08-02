//
// Created by Lobanov Dmitry on 09.09.15.
// Copyright (c) 2015 AirkeyTeam. All rights reserved.
//

@import Foundation;
#import <BWBluetoothWolf/AIKBluetoothMessage.h>
#import <BWBluetoothWolf/BWBluetoothDeprecations.h>
@import CoreBluetooth;
@class BWBluetoothWolfBaseCentralManager;

#pragma mark - New
NS_ASSUME_NONNULL_BEGIN
@protocol BWBluetoothWolfBaseCentralManagerDiscoveryProtocol <NSObject>
- (BOOL)centralManager:(BWBluetoothWolfBaseCentralManager *)centralManager central:(CBCentralManager *)central shouldDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI;
- (void)centralManager:(BWBluetoothWolfBaseCentralManager *)centralManager central:(CBCentralManager *)central establishConnectionWithPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI;
@end
@protocol BWBluetoothWolfBaseCentralManagerSessionProtocol <NSObject>
// save peripheral for further usage.
- (void)centralManager:(BWBluetoothWolfBaseCentralManager *)centralManager central:(CBCentralManager *)central savePeripheral:(CBPeripheral *)peripheral withPeripheralName:(NSString *)name;
// connection retrieving
- (void)centralManager:(BWBluetoothWolfBaseCentralManager *)centralManager central:(CBCentralManager *)central discoverCharacteristicInServiceForPeripheral:(CBPeripheral *)peripheral withPeripheralName:(NSString *)name;
// callbacks
- (void)centralManager:(BWBluetoothWolfBaseCentralManager *)centralManager central:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral;
- (void)centralManager:(BWBluetoothWolfBaseCentralManager *)centralManager central:(CBCentralManager *)central didDiscoverServicesInPeripheral:(CBPeripheral *)peripheral withError:(NSError *)error;
- (void)centralManager:(BWBluetoothWolfBaseCentralManager *)centralManager central:(CBCentralManager *)central didDiscoverCharacteristicsInService:(CBService *)service forPeripheral:(CBPeripheral *)peripheral;
- (void)centralManager:(BWBluetoothWolfBaseCentralManager *)centralManager central:(CBCentralManager *)central didOpenConnectionOnPeripheral:(CBPeripheral *)peripheral;
// part of session handling from IO.
- (void)centralManager:(BWBluetoothWolfBaseCentralManager *)centralManager peripheral:(CBPeripheral *)peripheral didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic error:(nullable NSError *)error;
@end
@protocol BWBluetoothWolfBaseCentralManagerStateProtocol <NSObject>
- (void)centralManagerDidUpdateState:(CBCentralManager *)central;
- (void)centralManager:(CBCentralManager *)central willRestoreState:(NSDictionary *)dict;
@end
@protocol BWBluetoothWolfBaseCentralManagerDisconnectProtocol <NSObject>
- (void)centralManager:(BWBluetoothWolfBaseCentralManager *)centralManager central:(CBCentralManager *)central wasDisconnectedFromPeripheral:(CBPeripheral *)peripheral withError:(NSError *)error;
- (BOOL)centralManager:(BWBluetoothWolfBaseCentralManager *)centralManager central:(CBCentralManager *)central wasDisconnectedGracefullyFromPeripheral:(CBPeripheral *)peripheral withError:(NSError *)error;
@end
@protocol BWBluetoothWolfBaseCentralManagerIOProtocol <NSObject>
- (void)centralManager:(BWBluetoothWolfBaseCentralManager *)centralManager peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(nullable NSError *)error;
- (void)centralManager:(BWBluetoothWolfBaseCentralManager *)centralManager peripheral:(CBPeripheral *)peripheral didWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(nullable NSError *)error;
@end

typedef struct {
    NSInteger centralManagerCentralShouldDiscoverPeripheralAdvertisementDataRSSI : 1;
    NSInteger centralManagerCentralEstablishConnectionWithPeripheralAdvertisementDataRSSI : 1;
} BWBluetoothWolfBaseCentralManagerDiscoveryProtocolFlags;
typedef struct {
    // save peripheral for further usage.
    NSInteger centralManagerCentralSavePeripheralWithPeripheralName : 1;
    // connection retrieving
    NSInteger centralManagerCentralDiscoverCharacteristicInServiceForPeripheralWithPeripheralName : 1;
    // callbacks
    NSInteger centralManagerCentralDidConnectPeripheral : 1;
    NSInteger centralManagerCentralDidDiscoverServicesInPeripheralWithError : 1;
    NSInteger centralManagerCentralDidDiscoverCharacteristicsInServiceForPeripheral : 1;
    // now here. from IO.
    NSInteger centralManagerPeripheralDidUpdateNotificationStateForCharacteristicError : 1;
    // connection retrieved.
    NSInteger centralManagerCentralDidOpenConnectionOnPeripheral : 1;
} BWBluetoothWolfBaseCentralManagerSessionProtocolFlags;
typedef struct {
    NSInteger centralManagerDidUpdateState : 1;
    NSInteger centralManagerWillRestoreState : 1;
} BWBluetoothWolfBaseCentralManagerStateProtocolFlags;
typedef struct {
    NSInteger centralManagerCentralWasDisconnectedFromPeripheralWithError : 1;
    NSInteger centralManagerCentralWasDisconnectedGracefullyFromPeripheralWithError : 1;
} BWBluetoothWolfBaseCentralManagerDisconnectProtocolFlags;
typedef struct {
    NSInteger centralManagerPeripheralDidUpdateValueForCharacteristicError : 1;
    NSInteger centralManagerPeripheralDidWriteValueForCharacteristicError : 1;
} BWBluetoothWolfBaseCentralManagerIOProtocolFlags;


BWBluetoothWolfBaseCentralManagerDiscoveryProtocolFlags _createFlagsFrom_BWBluetoothWolfBaseCentralManagerDiscoveryProtocol(id<BWBluetoothWolfBaseCentralManagerDiscoveryProtocol> item);
BWBluetoothWolfBaseCentralManagerSessionProtocolFlags _createFlagsFrom_BWBluetoothWolfBaseCentralManagerSessionProtocol(id<BWBluetoothWolfBaseCentralManagerSessionProtocol> item);
BWBluetoothWolfBaseCentralManagerStateProtocolFlags _createFlagsFrom_BWBluetoothWolfBaseCentralManagerStateProtocol(id<BWBluetoothWolfBaseCentralManagerStateProtocol> item);
BWBluetoothWolfBaseCentralManagerDisconnectProtocolFlags _createFlagsFrom_BWBluetoothWolfBaseCentralManagerDisconnectProtocol(id<BWBluetoothWolfBaseCentralManagerDisconnectProtocol> item);
BWBluetoothWolfBaseCentralManagerIOProtocolFlags _createFlagsFrom_BWBluetoothWolfBaseCentralManagerIOProtocol(id<BWBluetoothWolfBaseCentralManagerIOProtocol> item);


NSString *_NSStringFrom_BWBluetoothWolfBaseCentralManagerSessionProtocolFlags(BWBluetoothWolfBaseCentralManagerSessionProtocolFlags flags);
NS_ASSUME_NONNULL_END
