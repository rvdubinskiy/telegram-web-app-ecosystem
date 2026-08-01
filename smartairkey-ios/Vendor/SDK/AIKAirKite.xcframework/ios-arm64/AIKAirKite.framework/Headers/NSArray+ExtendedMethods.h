//
//  NSArray+ExtendedMethods.h
//  Buro 247
//
//  Created by Dmitry Lobanov on 12.12.14.
//
//

@import Foundation;
#import "NSObject+ExtendedMethods.h"

typedef NS_ENUM(NSInteger, AIKArrayExtension__F) {
    AIKArrayExtension__F__Empty,
    AIKArrayExtension__HasHead,
    AIKArrayExtension__HasTail
};

@interface AIKArrayExtension <__covariant A, __covariant B> : NSObject
+ (NSArray <A>*)array:(NSArray <A>*)array filterObjectsUsingBlock:(BOOL (^)(A obj, NSUInteger idx))block;

+ (NSArray <B>*)array:(NSArray <A>*)array mapObjectsUsingBlock:(B (^)(A obj, NSUInteger idx))block;

+ (NSArray <B>*)array:(NSArray <A>*)array compactObjectsUsingBlock:(B (^)(A obj, NSUInteger idx))block;

+ (B)array:(NSArray <A>*)array accumulateObjectsUsingBlock:(B (^)(B accumulatedValue, A obj, NSUInteger idx))block withInitialValue:(B)initialValue;
@end

@interface NSArray <__covariant ObjectType> (ExtendedMethods)
- (NSArray *)filterObjectsUsingBlock:(BOOL (^)(ObjectType obj, NSUInteger idx))block;

- (NSArray *)mapObjectsUsingBlock:(id (^)(ObjectType obj, NSUInteger idx))block;

- (NSArray *)compactObjectsUsingBlock:(id (^)(ObjectType obj, NSUInteger idx))block;

- (id)accumulateObjectsUsingBlock:(id (^)(id accumulatedValue, ObjectType obj, NSUInteger idx))block withInitialValue:(id)initialValue;

- (__kindof ObjectType)firstObjectPassingTest:(BOOL (^)(ObjectType obj, NSUInteger idx, BOOL *stop))block;

@property(nonatomic, readonly) NSArray *compactArray;

- (NSArray *)arrayByRemovingObject:(NSObject *)object;

- (NSArray *)arrayByInsertingObject:(id)anObject atIndex:(NSUInteger)index;
//Examples:
//id accumulate =
//[@[@1,@3,@5,@3,@6] accumulateObjectsUsingBlock:^id(id accumulatedValue, id obj, NSUInteger idx) {
//    return @([(NSNumber*) obj integerValue] * [(NSNumber*)accumulatedValue integerValue]);
//} withInitialValue:@1];
//DLog(@"I have mult: %@",(NSNumber*)accumulate);
// I have mult 270 = 3 * 5 * 3 * 6 = 9 * 30 = 270
@end

@interface NSMutableArray (ExtendedMethods)

- (id)dequeueObject;
- (void)enqueueObject:(id)object;

- (id)popObject;
- (void)pushObject:(id)object;

@end
