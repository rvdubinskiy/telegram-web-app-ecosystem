//
//  BWBluetoothWolfConnectionProtocol.h
//  BWBluetoothWolf
//
//  Created by Lobanov Dmitry on 26.04.16.
//  Copyright © 2016 SmartAirkey. All rights reserved.
//

@import Foundation;
#import <BWBluetoothWolf/BWBluetoothDeprecations.h>

@protocol BWBluetoothWolfConnectionIOProtocol <NSObject>

@optional- (void)connectionDidReceiveData:(NSData *)message withError:(NSError *)error;
@optional- (void)connectionDidSendData:(NSData *)data withError:(NSError *)error;

@end

typedef struct {
    NSInteger connectionDidReceiveDataWithError : 1;
    NSInteger connectionDidSendDataWithError : 1;
} BWBluetoothWolfConnectionIOProtocolFlags;

BWBluetoothWolfConnectionIOProtocolFlags createFlagsFromBWBluetoothWolfConnectionIOProtocol(id<BWBluetoothWolfConnectionIOProtocol>item);