//
//  AIKBluetoothTransportCoderFactory.h
//  TCTransportCamel
//
//  Created by Lobanov Dmitry on 18.08.16.
//  Copyright © 2016 SmartAirkey. All rights reserved.
//

@import Foundation;
#import <TCTransportCamel/TCTransportCoderProtocol.h>

@interface TCTransportCoderHolderProxy : NSProxy <TCTransportCoderProtocol>

+ (instancetype) decoratedInstanceOf:(id<TCTransportCoderProtocol>)instance;
@property (strong, nonatomic, readonly) id<TCTransportCoderProtocol>instance;
@property (nonatomic, readwrite) TCTransportCoderVersion version;

@end

@interface TCTransportCoderFactory : NSObject

+ (id<TCTransportCoderProtocol>)coderWithVersion:(TCTransportCoderVersion)version;

@end