//
//  AIKCocoaLumberjackCustomLogFormat.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 17.12.15.
//  Copyright © 2015 AirkeyTeam. All rights reserved.
//

@import Foundation;
@import CocoaLumberjack;
#import "AIKEnumDescription.h"

typedef NS_ENUM(NSInteger, AIKCocoaLumberjackCustomLogFormatFiltering) {
    AIKCocoaLumberjackCustomLogFormatFiltering__Bluetooth,
    AIKCocoaLumberjackCustomLogFormatFiltering__Transport,
    AIKCocoaLumberjackCustomLogFormatFiltering__DeviceInteraction,
    AIKCocoaLumberjackCustomLogFormatFiltering__Database,
    AIKCocoaLumberjackCustomLogFormatFiltering__Network,
    AIKCocoaLumberjackCustomLogFormatFiltering__Delivery,
    AIKCocoaLumberjackCustomLogFormatFiltering__RSSI,
    AIKCocoaLumberjackCustomLogFormatFiltering__Location
};

// Actually, no, but we can :3
// It is only for auxuliary methods.
@interface AIKLoggingFilterEntityDescription: AIKEnumDescription__Localized @end

@interface AIKLoggingFilter: NSObject
- (NSArray <NSString *>*)currentFilters;
- (void)addFilter:(AIKCocoaLumberjackCustomLogFormatFiltering)filter;
- (void)removeFilter:(AIKCocoaLumberjackCustomLogFormatFiltering)filter;
- (BOOL)shouldDiscardMessage:(NSString *)message;
@end

@interface AIKCocoaLumberjackCustomLogFormat: NSObject<DDLogFormatter>
+ (instancetype)createLogFormat;
@property (strong, nonatomic, readwrite) AIKLoggingFilter *filter;
@end
