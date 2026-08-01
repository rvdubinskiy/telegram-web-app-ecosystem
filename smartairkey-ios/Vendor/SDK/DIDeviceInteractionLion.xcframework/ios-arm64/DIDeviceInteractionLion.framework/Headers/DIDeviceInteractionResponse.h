//
//  DIDeviceInteractionResponse.h
//  DIDeviceInteractionLion
//
//  Created by Lobanov Dmitry on 16.08.17.
//  Copyright © 2017 Dmitry. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DIDeviceInteractionResponse <ObjectType> : NSObject
@property (strong, nonatomic, readwrite) ObjectType response;
- (instancetype)initWithResponse:(ObjectType)response;
@end
