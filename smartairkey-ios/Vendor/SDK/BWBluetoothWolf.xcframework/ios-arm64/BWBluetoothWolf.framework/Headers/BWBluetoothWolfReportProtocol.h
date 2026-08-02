//
//  BWBluetoothWolfReportProtocol.h
//  BWBluetoothWolf
//
//  Created by Lobanov Dmitry on 23.11.16.
//  Copyright © 2016 SmartAirkey. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

@protocol BWBluetoothWolfReportProtocol <NSObject>
- (void)reportWithError:(NSError *)error withInformation:(NSDictionary *)information;
@end

typedef struct {
    NSInteger reportWithErrorWithInformation : 1;
} BWBluetoothWolfReportProtocolFlags;

BWBluetoothWolfReportProtocolFlags _createFlagsFrom_BWBluetoothWolfReportProtocol(id<BWBluetoothWolfReportProtocol> item);

NS_ASSUME_NONNULL_END
