//
//  DIDeviceInteractionEntitiesProtocols.h
//  DIDeviceInteractionLion
//
//  Created by Dmitry on 05.04.17.
//  Copyright © 2017 Dmitry. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DIDeviceInteractionLionDeprecations.h"
@interface DIDeviceInteractionEntitiesProtocols : NSObject

@end

@protocol DIDeviceInteractionEntityDerivedSignatureKeyProtocol <NSObject, NSCopying>
@property(copy, nonatomic, readonly) NSString *token;
@property(copy, nonatomic, readonly) NSString *salt;
@property(assign, nonatomic, readonly) double algorithm;
@end

@protocol DIDeviceInteractionEntityKeySettingsProtocol <NSObject, NSCopying>
@property(assign, nonatomic, readonly) double activeDistance;
@property(assign, nonatomic, readonly) double activeTime;
@property(assign, nonatomic, readonly) BOOL autoOpen;
@property(assign, nonatomic, readonly) BOOL autoClose;
@property(assign, nonatomic, readonly) BOOL keepOpenNear;
@property(assign, nonatomic, readonly) BOOL openOnTap;
@end

@protocol DIDeviceInteractionEntityDeviceTransportProtocol <NSObject, NSCopying>
@property(copy, nonatomic, readonly) NSString *deviceName;
@property(copy, nonatomic, readonly) NSString *charDataUuid;
@property(copy, nonatomic, readonly) NSString *serviceUuid;
@property(copy, nonatomic, readonly) NSString *charRssiUuid;
@end

@protocol DIDeviceInteractionEntityDeviceInformation__IdentifierProtocol <NSObject, NSCopying>
@property(copy, nonatomic, readonly) NSString *identifier;
@end

@protocol DIDeviceInteractionEntityDeviceInformationProtocol <NSObject, NSCopying>
@property(copy, nonatomic, readonly) id<DIDeviceInteractionEntityDeviceInformation__IdentifierProtocol> identifier;
@property(copy, nonatomic, readonly) NSString *accessToken;
@property(copy, nonatomic, readonly) id<DIDeviceInteractionEntityKeySettingsProtocol> keySettings;
@property(copy, nonatomic, readwrite) NSString *accessTokenV3;
@property(copy, nonatomic, readwrite) id<DIDeviceInteractionEntityDerivedSignatureKeyProtocol> signatureKeyV3;
@property(copy, nonatomic, readonly) id<DIDeviceInteractionEntityDerivedSignatureKeyProtocol> signatureKey;
@property(copy, nonatomic, readonly) id<DIDeviceInteractionEntityDeviceTransportProtocol> deviceTransport;
@end

@protocol DIDeviceInteractionStructureSmartDeviceDataProtocol <NSObject, NSCopying>
@property(strong, nonatomic, readwrite) NSString *sid;
@property(strong, nonatomic, readwrite) NSString *pid;
@property(strong, nonatomic, readwrite) NSString *masterKey;
@property(strong, nonatomic, readwrite) NSData *salt;
@property(strong, nonatomic, readwrite) NSData *publicKey;
@end

@protocol DIDeviceInteractionEntityDerivedSignatureKeyProtocol__Mutable <DIDeviceInteractionEntityDerivedSignatureKeyProtocol>
@property(copy, nonatomic, readwrite) NSString *token;
@property(copy, nonatomic, readwrite) NSString *salt;
@property(assign, nonatomic, readwrite) double algorithm;
@end

@protocol DIDeviceInteractionEntityKeySettingsProtocol__Mutable <DIDeviceInteractionEntityKeySettingsProtocol>
@property(assign, nonatomic, readwrite) double activeDistance;
@property(assign, nonatomic, readwrite) double activeTime;
@property(assign, nonatomic, readwrite) BOOL autoOpen;
@property(assign, nonatomic, readwrite) BOOL autoClose;
@property(assign, nonatomic, readwrite) BOOL keepOpenNear;
@property(assign, nonatomic, readwrite) BOOL openOnTap;
@end

@protocol DIDeviceInteractionEntityDeviceTransportProtocol__Mutable <DIDeviceInteractionEntityDeviceTransportProtocol>
@property(copy, nonatomic, readwrite) NSString *deviceName;
@property(copy, nonatomic, readwrite) NSString *charDataUuid;
@property(copy, nonatomic, readwrite) NSString *serviceUuid;
@property(copy, nonatomic, readwrite) NSString *charRssiUuid;
@end

@protocol DIDeviceInteractionEntityDeviceInformation__IdentifierProtocol__Mutable <DIDeviceInteractionEntityDeviceInformation__IdentifierProtocol>
@property(copy, nonatomic, readwrite) NSString *identifier;
@end

@protocol DIDeviceInteractionEntityDeviceInformationProtocol__Mutable <DIDeviceInteractionEntityDeviceInformationProtocol>
@property(copy, nonatomic, readwrite) id<DIDeviceInteractionEntityDeviceInformation__IdentifierProtocol> identifier;
@property(copy, nonatomic, readwrite) NSString *accessToken;
@property(copy, nonatomic, readwrite) NSString *accessTokenV3;
@property(copy, nonatomic, readwrite) id<DIDeviceInteractionEntityDerivedSignatureKeyProtocol> signatureKeyV3;
@property(copy, nonatomic, readwrite) id<DIDeviceInteractionEntityKeySettingsProtocol> keySettings;
@property(copy, nonatomic, readwrite) id<DIDeviceInteractionEntityDerivedSignatureKeyProtocol> signatureKey;
@property(copy, nonatomic, readwrite) id<DIDeviceInteractionEntityDeviceTransportProtocol> deviceTransport;
@end
