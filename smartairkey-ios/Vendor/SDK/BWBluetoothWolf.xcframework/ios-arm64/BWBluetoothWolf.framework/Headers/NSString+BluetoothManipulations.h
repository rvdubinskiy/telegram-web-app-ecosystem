//
//  NSString+BluetoothManipulations.h
//  Airkey
//
//  Created by Lobanov Dmitry on 01.07.15.
//  Copyright (c) 2015 AirkeyTeam. All rights reserved.
//

@import Foundation;

@import CoreBluetooth;

@interface NSString (BluetoothManipulations)

@property(nonatomic, readonly) CBUUID *cbuuid;
@property(nonatomic, readonly) NSNumber *rssiNumber;

@end
