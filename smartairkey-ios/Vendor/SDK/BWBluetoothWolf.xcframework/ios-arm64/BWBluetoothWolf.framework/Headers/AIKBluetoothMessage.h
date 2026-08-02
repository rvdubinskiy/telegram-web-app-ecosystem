//
//  AIKBluetoothMessage.h
//  Airkey
//
//  Created by Alexandr Novikov on 04.07.15.
//  Copyright (c) 2015 AirkeyTeam. All rights reserved.
//

@import Foundation;
#import <BWBluetoothWolf/BWBluetoothDeprecations.h>

@interface AIKBluetoothMessage : NSObject

- (instancetype)initWithData:(NSData *)data;
- (instancetype)messageByAppendingData:(NSData *)data;

@property(assign, nonatomic, readonly) NSInteger chunkLength;

@property(strong, nonatomic, readonly) NSData *messageData;

/*!
 * @property internalData
 *
 * @discussion Main purpose: separate messageData ( as a face ) and internalData ( as a body ) of bluetooth message data. As a default @property messageData is an alias to internalData.
 */
@property(strong, nonatomic, readonly) NSData *internalData;
@property(strong, nonatomic, readonly) NSNumber *hexidecimalNumber;

@property(strong, nonatomic, readonly) NSData *currentChunk;
@property(assign, nonatomic, readonly) NSInteger currentPointer;

- (void)moveChunkPointer;
- (void)movedChunkPointerByAmount:(NSUInteger)amount; // hm, possible shit is bluetooth 5.0 and updated size of chunks for it?

- (NSData *)messageDataWithOffset:(NSUInteger)offset withMaximumLength:(NSUInteger)maximumLength;

// implement by subclasses
@property (assign, nonatomic, readonly) BOOL completed;

@end
