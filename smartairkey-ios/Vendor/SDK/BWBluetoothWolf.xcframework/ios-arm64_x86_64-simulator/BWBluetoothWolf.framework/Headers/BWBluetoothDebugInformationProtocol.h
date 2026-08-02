//
//  BWBluetoothDebugInformationProtocol.h
//  Pods
//
//  Created by Lobanov Dmitry on 28.04.16.
//
//

@import Foundation;

@protocol BWBluetoothDebugInformationProtocol <NSObject>

@required @property (nonatomic, readonly) NSDictionary *debugInformation;

@end

@interface BWNotNull : NSObject

+ (id)notNull:(id)object;

@end