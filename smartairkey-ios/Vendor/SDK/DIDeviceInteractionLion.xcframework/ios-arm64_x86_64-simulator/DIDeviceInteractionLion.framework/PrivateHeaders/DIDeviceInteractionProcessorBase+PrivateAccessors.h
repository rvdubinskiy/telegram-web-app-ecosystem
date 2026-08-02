//
//  DIDeviceInteractionProcessorBase+PrivateAccessors.h
//  DIDeviceInteractionLion
//
//  Created by Dmitry on 07.04.17.
//  Copyright © 2017 Dmitry. All rights reserved.
//

#import <DIDeviceInteractionLion/DIDeviceInteractionLion.h>
#import <DIDeviceInteractionLion/DIDeviceInteractionAmaterasuSessionConfiguration.h>
@interface DIDeviceInteractionProcessorBase (PrivateAccessors)

@end


@interface DIDeviceInteractionProcessorBase (Private_SessionConfiguration)
- (void)updateSessionConfiguration:(DIDeviceInteractionAmaterasuSessionConfiguration *)configuration;
@property (strong, nonatomic, readonly) DIDeviceInteractionAmaterasuSessionConfiguration *sessionConfiguration;
@end
