//
//  NSDictionary+ExtendedMethods.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 08.10.15.
//  Copyright © 2015 AirkeyTeam. All rights reserved.
//

@import Foundation;

@interface NSDictionary (ExtendedMethods)

@end

@interface NSDictionary (ImmerseComparasion)

+ (BOOL)isChild:(NSDictionary *)child immersedIntoParent:(NSDictionary *)parent;
- (BOOL)isImmersedIntoParent:(NSDictionary *)parent;

@end
