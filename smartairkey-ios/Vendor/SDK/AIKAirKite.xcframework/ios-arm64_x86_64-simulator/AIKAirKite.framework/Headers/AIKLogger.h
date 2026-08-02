//
//  AIKLogger.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 11.03.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;

// macroses

@interface AIKLogger : NSObject

- (void)verbose:(nonnull SEL)selector :(nonnull NSString *)string, ...;
- (void)debug:(nonnull SEL)selector :(nonnull NSString *)string, ...;
- (void)info:(nonnull SEL)selector :(nonnull NSString *)string, ...;
- (void)warn:(nonnull SEL)selector :(nonnull NSString *)string, ...;
- (void)error:(nonnull SEL)selector :(nonnull NSString *)string, ...;
- (void)fatal:(nonnull SEL)selector :(nonnull NSString *)string, ...;

@end