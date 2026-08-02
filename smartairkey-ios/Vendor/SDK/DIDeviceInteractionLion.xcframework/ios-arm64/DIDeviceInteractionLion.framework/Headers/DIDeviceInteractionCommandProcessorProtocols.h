//
//  DIDeviceInteractionCommandProcessorProtocols.h
//  DIDeviceInteractionLion
//
//  Created by Dmitry on 05.04.17.
//  Copyright © 2017 Dmitry. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DIDeviceInteractionEntitiesProtocols.h"
#import "DIDeviceInteractionProcessorChannelTypeDescription.h"

NS_ASSUME_NONNULL_BEGIN

@interface DIDeviceInteractionCommandProcessorProtocols : NSObject

@end

typedef NS_ENUM(NSInteger, DIDeviceInteractionProcessorDeviceInformationProvider__Fetching__UpdateType) {
    DIDeviceInteractionProcessorDeviceInformationProvider__Fetching__UpdateType__Delete,
    DIDeviceInteractionProcessorDeviceInformationProvider__Fetching__UpdateType__Update,
    DIDeviceInteractionProcessorDeviceInformationProvider__Fetching__UpdateType__Insert
};

@protocol DIDeviceInteractionProcessorDeviceInformationProvider__Fetching__Protocol
- (void)willUpdateData;
- (void)didUpdateItem:(id<DIDeviceInteractionEntityDeviceInformationProtocol>)item type:(DIDeviceInteractionProcessorDeviceInformationProvider__Fetching__UpdateType)type;
- (void)didUpdateData;
@end

@protocol DIDeviceInteractionProcessorDeviceInformationProviderProtocol <NSObject>

@property (weak, nonatomic, readwrite) id<DIDeviceInteractionProcessorDeviceInformationProvider__Fetching__Protocol> _Nullable delegate;
- (id<DIDeviceInteractionEntityDeviceInformationProtocol> _Nullable)deviceInformationForName:(nullable NSString *)name;

@end
//
@protocol DIDeviceInteractionProcessorEstablishConnectionProviderProtocol <NSObject>
- (void)establishConnectionOnPeerWithName:(NSString *)name type:(DIDeviceInteractionProcessorChannelType *)type highPriority:(BOOL)priority;
@end

@protocol DIDeviceInteractionProcessorDestroyConnectionProviderProtocol <NSObject>
- (void)closeConnectionOnPeerWithName:(NSString *)name type:(DIDeviceInteractionProcessorChannelType *)type forced:(BOOL)forced;
@end

NS_ASSUME_NONNULL_END
