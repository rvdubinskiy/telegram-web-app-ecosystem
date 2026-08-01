//
//  DIDeviceInteractionEntitiesConfigurationProtocols.h
//  DIDeviceInteractionLion
//
//  Created by Lobanov Dmitry on 16.08.17.
//  Copyright © 2017 Dmitry. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DIDeviceInteractionEntitiesConfigurationProtocols : NSObject

@end

@interface DIDeviceInteractionEntities__Configuration__Setting__Internal : NSObject
@property (copy, nonatomic, readwrite) id currentValue;
@end

@interface DIDeviceInteractionEntities__Configuration__Setting__Internal__Text : DIDeviceInteractionEntities__Configuration__Setting__Internal
@property (copy, nonatomic, readwrite) NSString *hint;
@property (copy, nonatomic, readwrite) NSString *regularExpression;
@property (copy, nonatomic, readwrite) NSNumber *minimumLength;
@property (copy, nonatomic, readwrite) NSNumber *maximumLength;
@property (copy, nonatomic, readwrite) NSString *typedCurrentValue;
@end

@interface DIDeviceInteractionEntities__Configuration__Setting__Internal__Range : DIDeviceInteractionEntities__Configuration__Setting__Internal
@property (copy, nonatomic, readwrite) NSNumber *minimum;
@property (copy, nonatomic, readwrite) NSNumber *maximum;
@property (copy, nonatomic, readwrite) NSNumber *typedCurrentValue;

// setting if decimal or float
@property (assign, nonatomic, readwrite) BOOL decimal;
@end

@interface DIDeviceInteractionEntities__Configuration__Setting__Internal__Boolean : DIDeviceInteractionEntities__Configuration__Setting__Internal
@property (copy, nonatomic, readwrite) NSArray *descriptions;
@property (copy, nonatomic, readwrite) NSNumber *typedCurrentValue;
@end

@interface DIDeviceInteractionEntities__Configuration__Setting__Internal__Multivalue : DIDeviceInteractionEntities__Configuration__Setting__Internal
@property (copy, nonatomic, readwrite) NSArray *values;
@property (copy, nonatomic, readwrite) NSArray *descriptions;
@property (copy, nonatomic, readonly) NSArray *typedCurrentValue;

// setting if inclusive ( YES ) or exclusive ( NO )
@property (assign, nonatomic, readwrite) BOOL allowMultipleSelection;
@end

@interface DIDeviceInteractionEntities__Configuration__Setting__Internal__CurrentDateTime : DIDeviceInteractionEntities__Configuration__Setting__Internal
@property (copy, nonatomic, readwrite) NSNumber *timestamp;
@end

@interface DIDeviceInteractionEntities__Configuration__Setting : NSObject
@property (copy, nonatomic, readwrite) NSString *title;
@property (copy, nonatomic, readwrite) NSString *settingDescription;
@property (copy, nonatomic, readwrite) NSNumber *settingType;
@property (copy, nonatomic, readwrite) NSNumber *readonly;
@property (copy, nonatomic, readwrite) NSNumber *invisible;
@property (strong, nonatomic, readwrite) DIDeviceInteractionEntities__Configuration__Setting__Internal *currentSetting;
@property (copy, nonatomic, readwrite) NSNumber *settingId;
@end

@interface DIDeviceInteractionEntities__Configuration__Setting__Internal__Group : DIDeviceInteractionEntities__Configuration__Setting__Internal
@property (copy, nonatomic, readwrite) NSArray <DIDeviceInteractionEntities__Configuration__Setting *>*settings;

// setting if childPane or group. Default is group.
@property (assign, nonatomic, readwrite) BOOL childPane;
@end


@interface DIDeviceInteractionEntities__Configuration__Settings : NSObject
@property (copy, nonatomic, readwrite) NSArray <DIDeviceInteractionEntities__Configuration__Setting *>*settings;
@end

