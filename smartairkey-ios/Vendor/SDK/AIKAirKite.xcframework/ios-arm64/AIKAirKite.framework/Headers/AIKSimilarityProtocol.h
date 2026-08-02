//
//  AIKSimilarityProtocol.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 05.04.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

@import Foundation;

@protocol AIKSimilarityProtocol <NSObject>

- (BOOL)theSameAs:(id)item;

@end

@protocol AIKKindaProtocol <NSObject>

- (BOOL)theKindOf:(id)item;

@end
