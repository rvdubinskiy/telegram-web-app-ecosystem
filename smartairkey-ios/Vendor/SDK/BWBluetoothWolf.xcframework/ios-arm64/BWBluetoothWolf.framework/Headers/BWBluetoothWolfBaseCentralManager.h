//
//  BWBluetoothWolfBaseCentralManager.h
//  BWBluetoothWolf
//
//  Created by Lobanov Dmitry on 21.10.16.
//  Copyright © 2016 SmartAirkey. All rights reserved.
//

@import Foundation;
@import CoreBluetooth;
#import <BWBluetoothWolf/BWBluetoothIOProtocolExtension.h>
#import <BWBluetoothWolf/BWBluetoothIOProtocol.h>
#import <BWBluetoothWolf/BWBluetoothWolfBaseCentralManagerProtocol.h>

@interface BWBluetoothWolfBaseCentralManager : NSObject

#pragma mark - Initialization
- (instancetype)init;
- (instancetype)initWithBreeding:(void(^)(BWBluetoothWolfBaseCentralManager *steamCell))breedingBlock;
- (instancetype)initWithRestorationIdentifier:(NSString *)identifier withBreeding:(void(^)(BWBluetoothWolfBaseCentralManager *steamCell))breedingBlock;

@property(strong, nonatomic, readonly) CBCentralManager *centralManager;
@property(weak, nonatomic) id<BWBluetoothIOProtocol> transferDelegate;
@property(weak, nonatomic) BWBluetoothMessageTransferProtocolExtension *messageReceivingDelegate;
@property(weak, nonatomic) id<BWBluetoothWolfBaseCentralManagerDiscoveryProtocol> discoveryDelegate;
@property(weak, nonatomic) id<BWBluetoothWolfBaseCentralManagerSessionProtocol> sessionDelegate;
@property(weak, nonatomic) id<BWBluetoothWolfBaseCentralManagerStateProtocol> stateDelegate;
@property(weak, nonatomic) id<BWBluetoothWolfBaseCentralManagerDisconnectProtocol> disconnectDelegate;
@property(weak, nonatomic) id<BWBluetoothWolfBaseCentralManagerIOProtocol> ioDelegate;

@end

@interface BWBluetoothWolfBaseCentralManager (Reset)
- (void)resetCentralManager;
- (void)resetCentralManagerWithRestorationIdentifier:(NSString *)identifier;
@end

@interface BWBluetoothWolfBaseCentralManager (CBCentralManagerDelegate)<CBCentralManagerDelegate> @end
@interface BWBluetoothWolfBaseCentralManager (CBPeripheralDelegate)<CBPeripheralDelegate> @end
