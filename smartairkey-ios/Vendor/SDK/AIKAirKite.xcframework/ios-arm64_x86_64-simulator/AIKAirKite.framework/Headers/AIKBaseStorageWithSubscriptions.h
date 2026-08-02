//
//  AIKBaseStorageWithSubscriptions.h
//  SmartAirkey
//
//  Created by Dmitry Lobanov on 26.06.2018.
//  Copyright © 2018 AirkeyTeam. All rights reserved.
//

@import Foundation;
#import "AIKBaseDictionaryStorage.h"
NS_ASSUME_NONNULL_BEGIN

@interface AIKBaseStorageWithSubscriptions__Subscriber__Holder<SubscriberType> : NSObject
@property (weak, nonatomic, readwrite, nullable) SubscriberType subscriber;
@property (copy, nonatomic, readwrite, nonnull) NSString *token;
- (void)moveSubsriberToPersistence:(BOOL)move;
- (instancetype)initWithSubscriber:(SubscriberType)subscriber token:(NSString *)token;
- (instancetype)initWithSubscriber:(SubscriberType)subscriber token:(NSString *)token shouldPersistSubscriber:(BOOL)shouldPersistSubscriber;
- (void)cancel;
@end

@protocol AIKBaseStorageWithSubscriptions__Protocol__Subscriptions <NSObject>
- (void)willSubscribe:(AIKBaseStorageWithSubscriptions__Subscriber__Holder *)holder;
- (void)didSubscribe:(AIKBaseStorageWithSubscriptions__Subscriber__Holder *)holder;
- (void)willUnsubscribe:(AIKBaseStorageWithSubscriptions__Subscriber__Holder *)holder;
- (void)didUnsubscribe:(AIKBaseStorageWithSubscriptions__Subscriber__Holder *)holder;
@end

@interface AIKBaseStorageWithSubscriptions : AIKBaseDictionaryStorage
- (AIKBaseStorageWithSubscriptions__Subscriber__Holder *)objectForKeyedSubscript:(id <NSCopying>)key;
- (void)setObject:(AIKBaseStorageWithSubscriptions__Subscriber__Holder *)obj forKeyedSubscript:(id <NSCopying>)key;
@property (weak, nonatomic, readwrite) id <AIKBaseStorageWithSubscriptions__Protocol__Subscriptions> delegate;
@end

@interface AIKBaseStorageWithSubscriptions (Subscriptions)
- (NSString *)tokenForObject:(nonnull NSObject *)object;
- (AIKBaseStorageWithSubscriptions__Subscriber__Holder *)subscribeOnEvents:(nonnull id)delegate token:(nonnull NSString *)token;
- (void)unsubscribeFromEvents:(nonnull id)delegate token:(NSString *)token;
@end

@interface AIKBaseStorageWithSubscriptions (Access)
#pragma mark - Subscribers
- (NSArray *)allSubscribers;
- (NSArray *)subscribers;
- (void)onEachSubscriber:(void(^)(id))block;
@end

NS_ASSUME_NONNULL_END
