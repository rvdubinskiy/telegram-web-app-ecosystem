//
//  DIDeviceInteractionProcessorChannelTypeDescription.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 11.11.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;
@import TCTransportCamel;

typedef NSString DIDeviceInteractionProcessorChannelType;

@interface DIDeviceInteractionProcessorChannelTypeDescription : NSObject
- (DIDeviceInteractionProcessorChannelType *)channelTypeForStreamingType:(TCTransportDataStreamingType *)streamingType;
+ (DIDeviceInteractionProcessorChannelType *)channelTypeForStreamingType:(TCTransportDataStreamingType *)streamingType;
+ (TCTransportDataStreamingType *)streamingTypeForChannelType:(DIDeviceInteractionProcessorChannelType *)channelType;

+ (BOOL)isDirectChannelType:(DIDeviceInteractionProcessorChannelType *)type;
+ (BOOL)isReverseChannelType:(DIDeviceInteractionProcessorChannelType *)type;
@end

@interface DIDeviceInteractionProcessorChannelTypes: NSObject
@property (copy, nonatomic, readonly, class) DIDeviceInteractionProcessorChannelType *Direct;
@property (copy, nonatomic, readonly, class) DIDeviceInteractionProcessorChannelType *Reverse;
@end
