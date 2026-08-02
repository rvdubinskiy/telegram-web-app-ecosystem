//
//  TCTransportDataStreamingManagerProtocol.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 27.04.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;
#import <TCTransportCamel/TCTransportDataStreamingProtocol.h>

typedef NS_ENUM(NSInteger, TCTransportDataStreamerState){
    TCTransportDataStreamerStateClosed,
    TCTransportDataStreamerStateOpened
};

@interface TCTransportDataStreamerStateDescription : NSObject

+ (NSString *)stringForState:(TCTransportDataStreamerState)state;

@end

@protocol TCTransportDataStreamingManagerStateProtocol <NSObject>

@optional - (void)dataStreamer:(id<TCTransportDataStreamingProtocol>)dataStreamer changeState:(TCTransportDataStreamerState)state withPeerName:(NSString *)name withDataStreamingType:(NSString *)type;

@end

typedef struct {
    NSInteger dataStreamerChangeStateWithPeerNameWithDataStreamingType : 1;
} TCTransportDataStreamingManagerStateProtocolFlags;

TCTransportDataStreamingManagerStateProtocolFlags createFlagsFromTCTransportDataStreamingManagerStateProtocol(id<TCTransportDataStreamingManagerStateProtocol> item);
