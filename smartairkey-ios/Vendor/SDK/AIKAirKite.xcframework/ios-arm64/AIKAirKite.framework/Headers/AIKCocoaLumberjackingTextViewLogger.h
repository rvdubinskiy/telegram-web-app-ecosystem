//
//  AIKCocoaLumberjackingTextViewLogger.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 05.02.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;
@import UIKit;
@import CocoaLumberjack;

@interface AIKCocoaLumberjackingTextViewLogger : NSObject<DDLogger>

+ (instancetype)sharedInstance;

@property (weak, nonatomic, readwrite) NSString *cellIdentifier;
@property (weak, nonatomic, readwrite) UITableView *loggingView;
@property (assign, nonatomic, readwrite) BOOL autoScrollsToBottom;

@end
