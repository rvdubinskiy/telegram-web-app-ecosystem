//
//  DIDeviceInteractionAmaterasuSessionConfiguration.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 06.05.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;
#import <DIDeviceInteractionLion/DIDeviceInteractionAmaterasuEnvelopeSerializerProtocol.h>

@interface DIDeviceInteractionAmaterasuSessionConfiguration : NSObject

/**
 expirationTimeInSeconds - general expiration time in seconds.
 default: 15 * 60 seconds.
 */
@property (strong, nonatomic, readwrite) NSNumber *expirationTimeInSeconds;


/**
 startedExpirationTimeInSeconds - started expiration time in seconds.
 this interval is used between session states: notStarted -> started.
 default: 5 * 60 seconds.
 */
@property (strong, nonatomic, readwrite) NSNumber *startedExpirationTimeInSeconds;

/**
 openingExpirationTimeInSeconds - opening expiration time in seconds.
 this interval is used when session is in opening state.
 default: 1 * 60 seconds.
 */
@property (strong, nonatomic, readwrite) NSNumber *openingExpirationTimeInSeconds;

@property (strong, nonatomic, readonly) id<DIDeviceInteractionAmaterasuEnvelopeSerializerProtocol> envelopeSerializer;
@property (assign, nonatomic, readwrite) DIDeviceInteractionAmaterasuSessionConfigurationEnvelopeSerializerVersion envelopeSerializerVersion;

@end
