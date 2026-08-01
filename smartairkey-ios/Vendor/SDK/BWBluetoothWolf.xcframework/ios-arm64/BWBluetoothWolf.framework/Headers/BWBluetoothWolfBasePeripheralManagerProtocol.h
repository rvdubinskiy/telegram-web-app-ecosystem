//
//  AIKBluetoothPeripheralManagerProtocol.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 07.01.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

#ifndef BWBluetoothWolfBasePeripheralManagerProtocol_h
#define BWBluetoothWolfBasePeripheralManagerProtocol_h
@class BWBluetoothWolfBasePeripheralManager;
@import CoreBluetooth;

NS_ASSUME_NONNULL_BEGIN

@protocol BWBluetoothWolfBasePeripheralManagerStartUpProtocol <NSObject>

- (void)peripheralManager:(BWBluetoothWolfBasePeripheralManager *)peripheralManager withPeripheral:(CBPeripheralManager *)peripheral didAddService:(CBService *)service withError:(NSError *)error;

- (void)peripheralManager:(BWBluetoothWolfBasePeripheralManager *)peripheralManager withPeripheral:(CBPeripheralManager *)peripheral startAdvertisingWithError:(NSError *)error;

@end

@protocol BWBluetoothWolfBasePeripheralManagerIOProtocol <NSObject>

- (void)peripheralManager:(BWBluetoothWolfBasePeripheralManager *)peripheral withPeripheral:(CBPeripheralManager *)peripheralManager central:(CBCentral *)central didSubscribeToCharacteristic:(CBCharacteristic *)characteristic;
- (void)peripheralManager:(BWBluetoothWolfBasePeripheralManager *)peripheral withPeripheral:(CBPeripheralManager *)peripheralManager central:(CBCentral *)central didUnsubscribeToCharacteristic:(CBCharacteristic *)characteristic;

- (void)peripheralManager:(BWBluetoothWolfBasePeripheralManager *)peripheralManager withPeripheral:(CBPeripheralManager *)peripheral didReceiveWriteRequests:(NSArray *)requests;
- (void)peripheralManager:(BWBluetoothWolfBasePeripheralManager *)peripheralManager withPeripheral:(CBPeripheralManager *)peripheral didReceiveWriteRequests:(NSArray *)requests withResponseResult:(NSNumber *__autoreleasing*)result;
- (void)peripheralManager:(BWBluetoothWolfBasePeripheralManager *)peripheralManager withPeripheral:(CBPeripheralManager *)peripheral didReceiveReadRequest:(CBATTRequest *)request;
- (void)peripheralManager:(BWBluetoothWolfBasePeripheralManager *)peripheralManager withPeripheral:(CBPeripheralManager *)peripheral didReceiveReadRequest:(CBATTRequest *)request withResponseResult:(NSNumber *__autoreleasing*)result;

- (void)peripheralManager:(BWBluetoothWolfBasePeripheralManager *)peripheralManager isReadyToUpdateSubscribersWithPeripheral:(CBPeripheralManager *)peripheral;

@end

@protocol BWBluetoothWolfBasePeripheralManagerStateProtocol <NSObject>
- (void)peripheralManagerDidUpdateState:(CBPeripheralManager *)peripheral;
- (void)peripheralManager:(CBPeripheralManager *)peripheral willRestoreState:(NSDictionary *)dict;
@end

@protocol BWBluetoothWolfBasePeripheralManagerDataProvidingProtocol <NSObject>

- (NSString *)nameForPeripheralIdentifier:(NSString *)peripheralIdentifier;
- (NSData *)nameForPeripheralIdentifier:(NSString *)peripheralIdentifier connectedCentralName:(NSString *)centralName;

@end

typedef struct {
    NSUInteger peripheralManagerWithPeripheralDidAddServiceWithError : 1;
    NSUInteger peripheralManagerWithPeripheralStartAdvertisingWithError : 1;
} BWBluetoothWolfBasePeripheralManagerStartUpProtocolFlags;

BWBluetoothWolfBasePeripheralManagerStartUpProtocolFlags createFlagsFromAIKBluetoothPeripheralManagerStartUpProtocol(id<BWBluetoothWolfBasePeripheralManagerStartUpProtocol> item);

typedef struct {
    NSUInteger peripheralManagerWithPeripheralCentralDidSubscribeToCharacteristic : 1;
    NSUInteger peripheralManagerWithPeripheralCentralDidUnsubscribeToCharacteristic : 1;
    NSUInteger peripheralManagerWithPeripheralDidReceiveWriteRequests : 1;
    NSUInteger peripheralManagerWithPeripheralDidReceiveWriteRequestsWithResponseResult : 1;
    NSUInteger peripheralManagerWithPeripheralDidReceiveReadRequest : 1;
    NSUInteger peripheralManagerWithPeripheralDidReceiveReadRequestWithResponseResult : 1;
    NSUInteger peripheralManagerIsReadyToUpdateSubscribersWithPeripheral : 1;
} BWBluetoothWolfBasePeripheralManagerIOProtocolFlags;

BWBluetoothWolfBasePeripheralManagerIOProtocolFlags createFlagsFromAIKBluetoothPeripheralManagerIOProtocol(id<BWBluetoothWolfBasePeripheralManagerIOProtocol> item);

typedef struct {
    NSInteger peripheralManagerDidUpdateState : 1;
    NSInteger peripheralManagerWillRestoreState : 1;
} BWBluetoothWolfBasePeripheralManagerStateProtocolFlags;

BWBluetoothWolfBasePeripheralManagerStateProtocolFlags createFlagsFromBWBluetoothWolfBasePeripheralManagerStateProtocol(id<BWBluetoothWolfBasePeripheralManagerStateProtocol> item);

typedef struct {
	NSUInteger nameForPeripheralIdentifier : 1;
    NSUInteger nameForPeripheralIdentifierWithConnectedCentralName : 1;
} BWBluetoothWolfBasePeripheralManagerDataProvidingProtocolFlags;

BWBluetoothWolfBasePeripheralManagerDataProvidingProtocolFlags createFlagsFromAIKBluetoothPeripheralManagerDataProvidingProtocol(id<BWBluetoothWolfBasePeripheralManagerDataProvidingProtocol> item);

#endif /* BWBluetoothWolfBasePeripheralManagerProtocol_h */

NS_ASSUME_NONNULL_END
