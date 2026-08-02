//
//  AIKBluetoothBaseWolf.h
//  BWBluetoothWolf
//
//  Created by Lobanov Dmitry on 21.04.16.
//  Copyright © 2016 SmartAirkey. All rights reserved.
//

@import Foundation;
@import CoreBluetooth;
#import <BWBluetoothWolf/BWBluetoothDataStreamingProtocol.h>
#import <BWBluetoothWolf/BWBluetoothDebugInformationProtocol.h>

NS_ASSUME_NONNULL_BEGIN

@class BWBluetoothWolfContext;
@class BWBluetoothWolfConfiguration;

@interface BWBluetoothBaseWolf : NSObject
- (instancetype)initWithConfiguration:(BWBluetoothWolfConfiguration *)configuration;
- (void)updateWithConfiguration:(BWBluetoothWolfConfiguration *)configuration;
@property (strong, nonatomic) BWBluetoothWolfConfiguration *configuration;
@property (strong, nonatomic, readonly) BWBluetoothWolfConfiguration *gatheredConfiguration;

@end

@interface BWBluetoothBaseWolf (States)
@property (nonatomic, readonly) BOOL poweredOn;
@property (nonatomic, readonly) BOOL breededByMilk;
@end

@interface BWBluetoothBaseWolf (Cleanup)
- (void)cleanupPeerStorage;
- (void)forgetAllInformation;
- (void)resetPeerWithName:(NSString *)name;
- (void)resetPeerWithName:(NSString *)name withContext:(BWBluetoothWolfContext *)context;
@end

@interface BWBluetoothBaseWolf (Lifecycle)

#pragma mark - Instincts
- (void)awakeFromSleep; // last method in this shit.
- (void)callOnTheMoon;
- (void)fallAsleep;
- (void)stop;

#pragma mark - New Connections
- (void)startConnectionsForServicesUUIDS:(NSArray *)servicesUUIDS;
- (void)establishConnectionsForServicesUUIDS:(NSArray *)servicesUUIDS;
- (void)stopConnectionsForServicesUUIDS:(NSArray *)servicesUUIDS;

#pragma mark - New New Connections
- (void)startConnectionsForServicesUUIDS:(NSArray *)servicesUUIDS inContext:(BWBluetoothWolfContext *)context;
- (void)establishConnectionsForServicesUUIDS:(NSArray *)servicesUUIDS inContext:(BWBluetoothWolfContext *)context;
- (void)establishConnectionOnPeerWithName:(NSString *)name inContext:(BWBluetoothWolfContext *)context;
- (void)stopConnectionsForServicesUUIDS:(NSArray *)servicesUUIDS inContext:(BWBluetoothWolfContext *)context;
- (void)ruinConnectionOnPeerWithName:(NSString *)name inContext:(BWBluetoothWolfContext *)context;
- (void)holdConnectionsForServicesUUIDS:(NSArray *)servicesUUIDS inContext:(BWBluetoothWolfContext *)context;

#pragma mark - New Work in background
- (void)gracefullyDisconnectPeersWithServices:(NSArray *)servicesUUIDS;

#pragma mark - New New Work in background // not tested
- (void)gracefullyDisconnectPeersWithServices:(NSArray *)servicesUUIDS inContext:(BWBluetoothWolfContext *)context;
@end

@interface BWBluetoothBaseWolf (Restoration)
- (void)restore;
- (void)restoreInContext:(BWBluetoothWolfContext *)context;
- (void)restoreCentralManagersWithIdentifiers:(NSArray *)identifiers;
- (void)restorePeripheralManagersWithIdentifiers:(NSArray *)identifiers;
@end

@interface BWBluetoothBaseWolf (IOAdoption) <BWBluetoothDataStreamingProtocol>

@end

@interface BWBluetoothBaseWolf (DataInspection) <BWBluetoothDataInspectionProtocol>

@end

@interface BWBluetoothBaseWolf (BWBluetoothDebugInformationProtocol) <BWBluetoothDebugInformationProtocol>

@end

NS_ASSUME_NONNULL_END
