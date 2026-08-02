//
//  DIDeviceInteractionStructureAccessTokenV3.h
//  DIDeviceInteractionLion
//
//  Created by Антон Текутов on 20.11.2024.
//  Copyright © 2024 Dmitry. All rights reserved.
//

@import Foundation;

@interface DIDeviceInteractionStructureAccessTokenV3 : NSObject

@property (strong, nonatomic) NSString* tokenV3;
@property (strong, nonatomic) NSString* signatureKey;

@end
