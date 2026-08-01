//
//  BWBluetoothWolfDescriptiveErrors.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 03.09.15.
//  Copyright (c) 2015 AirkeyTeam. All rights reserved.
//

@import Foundation;

@import CoreBluetooth;

#define EXTERNAL_ERROR_PART_OF_LEGACY_DONT_CHANGE
typedef NS_ENUM(NSUInteger, BWBluetoothError) {
    BWBluetoothErrorIOSend = 0xD1,
    BWBluetoothErrorIOReceive = 0xD2,
    BWBluetoothErrorIORead = 0xD3,  
    EXTERNAL_ERROR_PART_OF_LEGACY_DONT_CHANGE BWBluetoothErrorUnknownDevice = 0xD4,
    BWBluetoothErrorPeripheralManagerUpdateCharacteristic = 0xD5,
    BWBluetoothErrorPeripheralManagerUpdateCharacteristicTimeout = 0xD6,
    BWBluetoothErrorConsistencyPeerNotFound = 0xD7
};

@interface BWBluetoothWolfDescriptiveErrors : NSObject

+ (NSString *)descriptiveAttributeError:(CBATTError)error;
+ (NSString *)descriptiveError:(CBError)error;
+ (NSString *)errorDescription:(NSInteger)error;

@end

@interface BWBluetoothWolfDescriptiveError : NSError
+ (instancetype)bwUnknownDeviceError;
+ (instancetype)bwIOSendError;
+ (instancetype)bwIOReadError;
+ (instancetype)bwPeripheralManagerUpdateCharacteristicError;
+ (instancetype)bwPeripheralManagerUpdateCharacteristicTimeoutError;
+ (instancetype)bwBluetoothErrorConsistencyPeerNotFound;
@end
