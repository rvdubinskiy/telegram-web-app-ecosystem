//
//  DIDeviceInteractionCommandRunnerProtocols.h
//  DIDeviceInteractionLion
//
//  Created by Dmitry on 13.04.17.
//  Copyright © 2017 Dmitry. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface DIDeviceInteractionCommandRunnerProtocols : NSObject

@end

@protocol DIDeviceInteractionCommandRunnerPeripheralManagerDataProvider <NSObject>
- (NSString *)nameForPeripheralIdentifier:(NSString *)identifier;
// TODO: Remove it later.
- (nullable NSData *)nameForPeripheralIdentifier:(NSString *)identifier connectedCentralName:(NSString *)centralName;
@end

NS_ASSUME_NONNULL_END
