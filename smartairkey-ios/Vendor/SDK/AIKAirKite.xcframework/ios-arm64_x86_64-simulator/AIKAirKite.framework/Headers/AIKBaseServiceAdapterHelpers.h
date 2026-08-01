//
//  AIKBaseServiceAdapterHelpers.h
//  SmartAirkey
//
//  Created by Dmitry on 08.04.17.
//  Copyright © 2017 AirkeyTeam. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AIKDeprecationDefines.h"

@interface AIKBaseServiceAdapterHelpers : NSObject

@end

#pragma message SMARTAIRKEY__warning__name_and_msg_and_solution(SMARTAIRKEY_TODOS,SMARTAIRKEY_TODOS_DONT_FORGET_TO_REMOVE,"Could be removed in case that all subclasses which marked as final or in current usage, all of them don't use neither of its abilities except +(instancetype)createRepository")
@interface AIKBaseServiceAdapterRepository : NSObject
@property (strong, nonatomic, readwrite) NSArray *items;
@property (copy, nonatomic, readwrite) BOOL (^availableBlock)(void);
@property (copy, nonatomic, readwrite) NSArray *(^generateBlock)(void);
@property (copy, nonatomic, readwrite) void (^setupBlock)(void);

// override if you wish.
- (NSArray *)preprocessedItems:(NSArray *)rawItems;
- (NSArray *)postprocessedItems:(NSArray *)rawItems;

//TODO: rewrite somehow :/
// not ok :/
// If locked - all uuids are blocked.
@property (assign, nonatomic, readwrite) BOOL locked;
- (void)resetCache;
- (void)resetCacheByRawItems:(NSArray *)rawItems;
- (void)setup;
- (void)cleanup;
@end

@interface AIKBaseServiceAdapterRepository (Create)
+ (instancetype)createRepository;
@end
