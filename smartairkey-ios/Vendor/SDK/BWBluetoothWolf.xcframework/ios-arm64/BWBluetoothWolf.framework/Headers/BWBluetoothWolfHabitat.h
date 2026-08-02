//
//  BWBluetoothWolfHabitat.h
//  BWBluetoothWolf
//
//  Created by Lobanov Dmitry on 22.04.16.
//  Copyright © 2016 SmartAirkey. All rights reserved.
//

@import Foundation;

@class BWBluetoothBaseWolf;
/*Deprecated.
@class AIKBluetoothWolf;
 */
@class BWBluetoothPeripheralWolf;
@class BWBluetoothCentralWolf;
@protocol BWBluetoothDataStreamingProtocol;
@protocol BWBluetoothDataInspectionProtocol;

NS_ASSUME_NONNULL_BEGIN

@interface BWBluetoothWolfHabitat : NSObject

#pragma mark - Instantiation
+ (instancetype)habitat;

#pragma mark - Setters
@property (strong, nonatomic, readwrite) BWBluetoothBaseWolf * _Nullable wolf;

#pragma mark - Getters
/*Deprecated.
@property (strong, nonatomic, readonly) AIKBluetoothWolf *centralWolf;
 */
@property (strong, nonatomic, readonly) BWBluetoothPeripheralWolf *peripheralOnlyWolf;
@property (strong, nonatomic, readonly) BWBluetoothCentralWolf *centralOnlyWolf;

@property (weak, nonatomic, readonly) id<BWBluetoothDataStreamingProtocol> dataStreamingDelegate;
@property (weak, nonatomic, readonly) id<BWBluetoothDataInspectionProtocol> dataInspectionDelegate;

@end

@interface BWBluetoothWolfHabitat (Debug)

- (BOOL)debugHealthCheck;
- (NSDictionary *)debugInformation;

@end

NS_ASSUME_NONNULL_END
