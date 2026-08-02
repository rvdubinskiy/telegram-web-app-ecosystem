//
//  NSData+ExtendedMethods.h
//  Buro 247
//
//  Created by Dmitry Lobanov on 12.12.14.
//
//

@import Foundation;
#import "NSObject+ExtendedMethods.h"

@interface NSData (ExtendedMethods)
#pragma mark - JSON Serialization

- (NSObject *)jsonObject;

+ (NSObject *)jsonObjectFromData:(NSData *)data;
@end
