//
//  AIKEnumDescription.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 25.01.2018.
//  Copyright © 2018 AirkeyTeam. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol AIKEnumDescription__Protocol <NSObject>
+ (NSDictionary *)items;
+ (NSString *)stringForValue:(id)value;
+ (id)valueForString:(NSString *)string;
@end

@protocol AIKEnumDescription__Localized__Protocol <AIKEnumDescription__Protocol>
+ (NSArray *)localizedStrings;
+ (NSString *)localizedStringForValue:(id)value;
+ (id)valueForLocalizedString:(NSString *)string;
@end

@interface AIKEnumDescription: NSObject <AIKEnumDescription__Protocol> @end

@interface AIKEnumDescription__Localized: AIKEnumDescription <AIKEnumDescription__Localized__Protocol> @end

