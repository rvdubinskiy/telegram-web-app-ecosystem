//
//  NSDate+SecurityEncoding.h
//  Airkey
//
//  Created by Lobanov Dmitry on 17.06.15.
//  Copyright (c) 2015 AirkeyTeam. All rights reserved.
//

@import Foundation;

@interface NSDate (SecurityEncoding)

- (NSString *)utcISO8601String;

+ (NSDate *)dateFromUtcISO8601String:(NSString *)string;

- (NSString *)shortDateShortTimeString;

@end