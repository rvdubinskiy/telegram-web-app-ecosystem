//
//  BWBluetoothWolfConfiguration.h
//  BWBluetoothWolf
//
//  Created by Lobanov Dmitry on 22.04.16.
//  Copyright © 2016 SmartAirkey. All rights reserved.
//

@import Foundation;
#import <BWBluetoothWolf/BWBluetoothWolfBaseChannelManagerProtocol.h>
#import <BWBluetoothWolf/BWBluetoothWolfBaseCentralManagerProtocol.h>
#import <BWBluetoothWolf/BWBluetoothIOProtocol.h>
#import <BWBluetoothWolf/BWBluetoothIOProtocolExtension.h>
#import <BWBluetoothWolf/BWBluetoothDataStreamingProtocol.h>
#import <BWBluetoothWolf/BWBluetoothWolfBasePeripheralManagerProtocol.h>
#import <BWBluetoothWolf/BWBluetoothWolfConnectionManagerProtocol.h>
#import <BWBluetoothWolf/BWBluetoothDebugInformationProtocol.h>
#import <BWBluetoothWolf/BWBluetoothWolfReportProtocol.h>

NS_ASSUME_NONNULL_BEGIN
@interface BWBluetoothWolfConfigurationOptionsKeys : NSObject
@property (copy, nonatomic, readonly, class) NSString *sessionExpirationTimeInSeconds;
@end

@interface BWBluetoothWolfConfigurationOptionsPeripheralManagerKeys : BWBluetoothWolfConfigurationOptionsKeys
@property (copy, nonatomic, readonly, class) NSString *operationDelayInMilliseconds;
@property (copy, nonatomic, readonly, class) NSString *desiredConnectionLatency;
@property (copy, nonatomic, readonly, class) NSString *updateCharacteristicFirstChunkTimeOutInMilliseconds;
@property (copy, nonatomic, readonly, class) NSString *restartPolicyFailsCountBeforeRestart;
@property (copy, nonatomic, readonly, class) NSString *restorePolicyShouldCleanupAfterServiceAdded;
@property (copy, nonatomic, readonly, class) NSString *restorePolicyShouldCleanupAfterAdvertising;
@end

@interface BWBluetoothWolfConfigurationOptionsCentralManagerKeys : BWBluetoothWolfConfigurationOptionsKeys
@property (copy, nonatomic, readonly, class) NSString *scanEnabled;
@property (copy, nonatomic, readonly, class) NSString *scanDuplicatesAllowed;
@end

@interface BWBluetoothWolfConfiguration : NSObject <BWBluetoothDebugInformationProtocol>

@property (weak, nonatomic) id<BWBluetoothIOProtocol> bluetoothIODelegate;
@property (weak, nonatomic) BWBluetoothMessageTransferProtocolExtension *messageReceivingProtocolExtensionDelegate;
@property (copy, nonatomic) NSDictionary *options;
@end

@interface BWBluetoothWolfConfigurationCentralPeripheral : BWBluetoothWolfConfiguration
@property (weak, nonatomic) id<BWBluetoothWolfBaseChannelManagerStateProtocol> channelManagerStateDelegate;
@property (weak, nonatomic) id<BWBluetoothWolfBaseChannelManagerDiscoveryProtocol> channelManagerDiscoveryDelegate;

@property (weak, nonatomic) id<BWBluetoothWolfBaseCentralManagerStateProtocol> centralManagerStateDelegate;
@property (weak, nonatomic) id<BWBluetoothWolfBaseCentralManagerDisconnectProtocol> centralManagerDiscoveryDisconnectDelegate;

@property (weak, nonatomic) id<BWBluetoothWolfBasePeripheralManagerDataProvidingProtocol> peripheralManagerDataProvidingDelegate;
@end

@interface BWBluetoothWolfConfigurationNew : BWBluetoothWolfConfiguration
@property (weak, nonatomic) id<BWBluetoothWolfConnectionManagerIOProtocol> connectionManagerIODelegate;
@property (weak, nonatomic) id<BWBluetoothWolfConnectionManagerStateProtocol> connectionManagerStateDelegate;
@property (weak, nonatomic) id<BWBluetoothWolfReportProtocol> reportDelegate;
@end

@interface BWBluetoothWolfConfigurationPeripheralOnly : BWBluetoothWolfConfigurationNew
@property (weak, nonatomic) id<BWBluetoothWolfBaseChannelManagerStateProtocol> channelManagerStateDelegate;
@property (weak, nonatomic) id<BWBluetoothWolfBaseChannelManagerDiscoveryProtocol> channelManagerDiscoveryDelegate;

@property (weak, nonatomic) id<BWBluetoothWolfBasePeripheralManagerStateProtocol> peripheralManagerStateDelegate;
@property (weak, nonatomic) id<BWBluetoothWolfBasePeripheralManagerDataProvidingProtocol> peripheralManagerDataProvidingDelegate;
@end

@interface BWBluetoothWolfConfigurationCentralOnly : BWBluetoothWolfConfigurationNew
@property (weak, nonatomic) id<BWBluetoothWolfBaseChannelManagerDiscoveryProtocol> channelManagerDiscoveryDelegate;
@property (weak, nonatomic) id<BWBluetoothWolfBaseChannelManagerEstablishmentProtocol> channelManagerEstablishmentDelegate;

@property (weak, nonatomic) id<BWBluetoothWolfBaseCentralManagerStateProtocol> centralManagerStateDelegate;
@property (weak, nonatomic) id<BWBluetoothWolfBaseCentralManagerDisconnectProtocol> centralManagerDisconnectDelegate;
// custom
@property (assign, nonatomic, readonly) BOOL optionsScanEnabled;
@property (assign, nonatomic, readonly) BOOL optionsScanDuplicatesAllowed;
@end

#pragma mark - Aggregated Configuration
@interface BWBluetoothWolfConfigurationAggregationCentralOnlyAndPeripheralOnly : BWBluetoothWolfConfiguration
@property (strong, nonatomic, readonly) BWBluetoothWolfConfigurationPeripheralOnly *peripheralOnlyConfiguration;
@property (strong, nonatomic, readonly) BWBluetoothWolfConfigurationCentralOnly *centralOnlyConfiguration;
@end

@interface BWBluetoothWolfConfiguration (Create)

+ (instancetype)configuration;
+ (BWBluetoothWolfConfigurationCentralPeripheral *)centralPeripheralConfiguration;
+ (BWBluetoothWolfConfigurationPeripheralOnly *)peripheralOnlyConfiguration;
+ (BWBluetoothWolfConfigurationCentralOnly *)centralOnlyConfiguration;
+ (BWBluetoothWolfConfigurationAggregationCentralOnlyAndPeripheralOnly *)aggregationCentralOnlyAndPeripheralOnlyConfiguration;
@end
NS_ASSUME_NONNULL_END
