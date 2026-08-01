//
//  BWBluetoothWolfContext.h
//  BWBluetoothWolf
//
//  Created by Lobanov Dmitry on 23.10.16.
//  Copyright © 2016 SmartAirkey. All rights reserved.
//

@import Foundation;
typedef NS_ENUM(NSInteger, BWBluetoothWolfContextUsageType){
    BWBluetoothWolfContextUsageType__None = 0,
    BWBluetoothWolfContextUsageType__Peripheral,
    BWBluetoothWolfContextUsageType__Central,
    BWBluetoothWolfContextUsageType__PeripheralAndCentral
};
@interface BWBluetoothWolfContext : NSObject
@property (assign, nonatomic, readonly) BWBluetoothWolfContextUsageType usageType;
@end

@interface BWBluetoothWolfContext (Create)
//+ (instancetype)isExclusiveUsage:(BOOL)usage;
//+ (instancetype)isApplicationInUse:(BOOL)usage;
@property (assign, nonatomic, readonly) BOOL applicationInUse;
@property (assign, nonatomic, readonly) BOOL exclusiveUsage;
+ (instancetype)hasUsageType:(BWBluetoothWolfContextUsageType)type;
@property (copy, nonatomic, readonly) BWBluetoothWolfContext *(^isExclusiveUsage)(BOOL value);
@property (copy, nonatomic, readonly) BWBluetoothWolfContext *(^isApplicationInUse)(BOOL value);
@property (copy, nonatomic, readonly) BWBluetoothWolfContext *(^hasUsageType)(BWBluetoothWolfContextUsageType value);
@end
