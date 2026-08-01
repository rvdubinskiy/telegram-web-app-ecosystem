//
//  AIKBaseServiceAdapter.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 03.08.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;
#import "AIKServiceAdapterProtocol.h"
@import UIKit;

@interface AIKBaseServiceAdapter: NSObject
@property (weak, nonatomic, readwrite) id <AIKServiceAdapter__Protocol__Permissions> permissionsGuard;
@property (weak, nonatomic, readwrite) id <AIKServiceAdapter__Protocol__Permissions__Listener> permissionsListener;
@end

@interface AIKBaseServiceAdapter (UIApplicationDelegateAdoption) <UIApplicationDelegate> @end

@interface AIKBaseServiceAdapter (AIKServiceAdapterSetupProtocol) <AIKServiceAdapter__Protocol__Setup> @end

@interface AIKBaseServiceAdapter (AIKServiceAdapterInformationProtocol) <AIKServiceAdapter__Protocol__Information> @end

@interface AIKBaseServiceAdapter (AIKServiceAdapter__Protocol__Startup) <AIKServiceAdapter__Protocol__Startup> @end

@interface AIKBaseServiceAdapter (Access)
+ (instancetype)service;
@end

#import "AIKBaseStorageWithSubscriptions.h"
@interface AIKBaseServiceAdapter__With__Subscriptions: AIKBaseServiceAdapter
@property (strong, nonatomic, readwrite) AIKBaseStorageWithSubscriptions *subscriptionsStorage;
@end

@interface AIKBaseServiceAdapter__With__Subscriptions (AIKBaseStorageWithSubscriptions__Protocol__Subscriptions) <AIKBaseStorageWithSubscriptions__Protocol__Subscriptions>
@end
