//
//  BWBluetoothWolfBuilder.h
//  BWBluetoothWolf
//
//  Created by Lobanov Dmitry on 22.04.16.
//  Copyright © 2016 SmartAirkey. All rights reserved.
//

@import Foundation;
@class BWBluetoothBaseWolf;
@class BWBluetoothWolfConfiguration;

NS_ASSUME_NONNULL_BEGIN

@interface BWBluetoothWolfBuilder : NSObject

+ (BWBluetoothBaseWolf *)buildWolfWithConfiguration:(BWBluetoothWolfConfiguration *)configuration;

@end

NS_ASSUME_NONNULL_END
