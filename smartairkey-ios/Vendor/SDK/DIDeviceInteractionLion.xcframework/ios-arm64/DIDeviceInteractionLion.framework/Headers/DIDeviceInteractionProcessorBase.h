//
//  DIDeviceInteractionProcessorBase.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 11.11.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;
#import "DIDeviceInteractionCommand.h"
#import "DIDeviceInteractionProcessorProtocol.h"
#import "DIDeviceInteractionCommandProcessorProtocols.h"
@import BWBluetoothWolf;
@import TCTransportCamel;

/*!
 * @class DIDeviceInteractionProcessorBase.
 * @discussion Declares the most needed methods for Processor.
 * Implements most of them as empty.
 */
@interface DIDeviceInteractionProcessorBase : NSObject
@property (weak, nonatomic, readwrite) id <DIDeviceInteractionProcessor__Protocol__Notifications> notificationsDelegate;
@property (weak, nonatomic, readwrite) id <DIDeviceInteractionProcessor__Protocol__Measurements> measurementsDelegate;
@property (weak, nonatomic, readwrite) id <DIDeviceInteractionProcessor__Protocol__Receiving> receivingDelegate;
@property (weak, nonatomic, readwrite) id <DIDeviceInteractionProcessor__Protocol__Sending> sendingDelegate;
@end

@interface DIDeviceInteractionProcessorBase(AIKLockCommandProcessorNotificationsProtocol) <DIDeviceInteractionProcessor__Protocol__Notifications, DIDeviceInteractionProcessor__Protocol__Notifications__DataProvider> @end

@interface DIDeviceInteractionProcessorBase(AIKLockCommandProcessorSessionProtocol)<DIDeviceInteractionProcessorSessionProtocol> @end

@interface DIDeviceInteractionProcessorBase(AIKLockCommandProcessorTransferProtocol)<DIDeviceInteractionProcessor__Protocol__Transfer> @end
@interface DIDeviceInteractionProcessorBase(AIKLockCommandProcessorTerminateProtocol)<DIDeviceInteractionProcessorTerminateProtocol> @end
@interface DIDeviceInteractionProcessorBase(AIKLockCommandProcessorReopenProtocol)<DIDeviceInteractionProcessorReopenProtocol> @end

// cover with data streaming protocol
// DataStreamingManagerStateProtocol, for example.
// Map BluetoothWolfBaseChannelManagerStateProtocol on DataStreamingManagerStateProtocol

//MARK: Deprecated. Should be replaced with another abstraction layer.
//Reason: Too close to bluetooth layer.
//Implemented in LockCommandProcessorBaseOldAPI
//@interface DIDeviceInteractionProcessorBase(BWBluetoothWolfBaseChannelManagerStateProtocol) <BWBluetoothWolfBaseChannelManagerStateProtocol> @end

//MARK: Deprecated. Should be replaced with another abstraction layer.
//Reason: Too close to bluetooth layer.
@interface DIDeviceInteractionProcessorBase(BWBluetoothWolfBaseChannelManagerDiscoveryProtocol) <BWBluetoothWolfBaseChannelManagerDiscoveryProtocol> @end

//MARK: Deprecated. Should be replaced with another abstraction layer.
//Reason: Too close to bluetooth layer.
@interface DIDeviceInteractionProcessorBase(BWBluetoothWolfBaseChannelManagerEstablishmentProtocol)<BWBluetoothWolfBaseChannelManagerEstablishmentProtocol> @end

@interface DIDeviceInteractionProcessorBase(TCTransportDataStreamingManagerStateProtocol)<TCTransportDataStreamingManagerStateProtocol> @end

//MARK: Deprecated.
//Reason: Not actual anymore.
//Implemented in LockCommandProcessorBaseOldAPI
//@interface DIDeviceInteractionProcessorBase(BWBluetoothIOProtocol) <BWBluetoothIOProtocol> @end

@interface DIDeviceInteractionProcessorBase(TCTransportDataStreamingIOProtocol) <TCTransportDataStreamingIOProtocol> @end

@interface DIDeviceInteractionProcessorBase(DataStreaming)
- (BWBluetoothWolfConfiguration *)connectedConfiguration:(BWBluetoothWolfConfiguration *)configuration;
- (void)setupDataStreaming;

//Deprecated
- (void)connectDataStreamingDelegate:(id<BWBluetoothDataStreamingProtocol>)delegate;
@end

@interface DIDeviceInteractionProcessorBase(DataInspection)
- (void)connectDataInspectionDelegate:(id<BWBluetoothDataInspectionProtocol>)delegate;
@end

@interface DIDeviceInteractionProcessorBase(Spawning)

+ (instancetype)createProcessor;
+ (instancetype)pureProcessor;
+ (instancetype)debugProcessor;
@end

@interface DIDeviceInteractionProcessorBase(SubclassAccessors)
@property (strong, nonatomic, readwrite) TCTransportDataStreamingManager *dataStreamingManager;

@end

@interface DIDeviceInteractionProcessorBase (DeviceInformationProvider)
@property (weak, nonatomic, readwrite) id<DIDeviceInteractionProcessorDeviceInformationProviderProtocol> deviceInformationProvider;
@property (weak, nonatomic, readwrite) id<DIDeviceInteractionProcessorEstablishConnectionProviderProtocol> establishConnectionProvider;
@property (weak, nonatomic, readwrite) id<DIDeviceInteractionProcessorDestroyConnectionProviderProtocol> destroyConnectionProvider;
@end
