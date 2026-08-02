//
//  DIDeviceInteractionAmaterasuEnvelopeSerializerProtocol.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 24.06.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;
#import <DIDeviceInteractionLion/DIDeviceInteractionStructureDerivedSignatureKey.h>

NS_ASSUME_NONNULL_BEGIN

@class DIDeviceInteractionAmaterasuEnvelope;
typedef NS_ENUM(NSInteger, DIDeviceInteractionAmaterasuSessionConfigurationEnvelopeSerializerVersion){
    DIDeviceInteractionAmaterasuSessionConfigurationEnvelopeSerializerVersionJWT,
    DIDeviceInteractionAmaterasuSessionConfigurationEnvelopeSerializerVersionProtobuf__Legacy,
    DIDeviceInteractionAmaterasuSessionConfigurationEnvelopeSerializerVersionProtobuf__Base,
    DIDeviceInteractionAmaterasuSessionConfigurationEnvelopeSerializerVersionProtobuf = DIDeviceInteractionAmaterasuSessionConfigurationEnvelopeSerializerVersionProtobuf__Base,
};

@interface DIDeviceInteractionAmaterasuSessionConfigurationEnvelopeSerializerVersion__Description : NSObject
+ (NSString *)localizedStringFromEnumeration:(DIDeviceInteractionAmaterasuSessionConfigurationEnvelopeSerializerVersion)version;
+ (NSArray *)localizedValues;
+ (DIDeviceInteractionAmaterasuSessionConfigurationEnvelopeSerializerVersion)enumerationFromLocalizedString:(NSString *)string;
@end

@protocol DIDeviceInteractionAmaterasuEnvelopeSerializerProtocol <NSObject>

- (NSData *)encodeEnvelope:(DIDeviceInteractionAmaterasuEnvelope *)envelope withSecretKey:(DIDeviceInteractionStructureDerivedSignatureKey *)secret;
@optional - (NSData *)encodeEnvelope:(DIDeviceInteractionAmaterasuEnvelope *)envelope withSecret:(NSString *)secret;

- (DIDeviceInteractionAmaterasuEnvelope *)decodeData:(NSData *)data withSecretKey:(DIDeviceInteractionStructureDerivedSignatureKey *)secret withError:(NSError *__autoreleasing *)error;

@end

@protocol DIDeviceInteractionAmaterasuEnvelopeSerializerWithVersioningProtocol <DIDeviceInteractionAmaterasuEnvelopeSerializerProtocol>
@optional - (NSData *)encodeEnvelope:(DIDeviceInteractionAmaterasuEnvelope *)envelope withSecretKey:(DIDeviceInteractionStructureDerivedSignatureKey *)secret version:(id)version;
@optional - (DIDeviceInteractionAmaterasuEnvelope *)decodeData:(NSData *)data secretKey:(DIDeviceInteractionStructureDerivedSignatureKey *)secret error:(NSError *__autoreleasing *)error version:(id)version;
@end

@interface DIDeviceInteractionAmaterasuEnvelopeSerializerFactory : NSObject

+ (id<DIDeviceInteractionAmaterasuEnvelopeSerializerProtocol>) serializerWithVersion:(DIDeviceInteractionAmaterasuSessionConfigurationEnvelopeSerializerVersion)version;

@end

NS_ASSUME_NONNULL_END
