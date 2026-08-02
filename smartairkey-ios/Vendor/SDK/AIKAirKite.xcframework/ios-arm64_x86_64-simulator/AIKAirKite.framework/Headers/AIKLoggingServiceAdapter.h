//
//  AIKLoggingServiceAdapter.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 31.07.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

#import "AIKBaseServiceAdapter.h"
typedef NS_ENUM(NSInteger, AIKLogLevel) {
    AIKLogLevelOff,
    AIKLogLevelError = AIKLogLevelOff | 1,
    AIKLogLevelWarn = AIKLogLevelError << 1 | AIKLogLevelError,
    AIKLogLevelInfo = AIKLogLevelWarn << 1 | AIKLogLevelWarn,
    AIKLogLevelDebug = AIKLogLevelInfo << 1 | AIKLogLevelInfo,
    AIKLogLevelVerbose = AIKLogLevelDebug << 1 | AIKLogLevelDebug,
    AIKLoglevelAll = AIKLogLevelVerbose << 1 | AIKLogLevelVerbose
};

@interface AIKLoggingServiceAdapter : AIKBaseServiceAdapter @end

@interface AIKLoggingServiceAdapter (LoggingFileInformation)
@property(copy, nonatomic, readonly) NSDictionary *loggingFileInformationDictionary;
@property(copy, nonatomic, readonly) NSString *loggingFileNameKey;
@property(copy, nonatomic, readonly) NSString *loggingFileDataKey;
@property(copy, nonatomic, readonly) NSString *loggingFileMimeTypeKey;
@end

@interface AIKLoggingServiceAdapter (FilesDumping)
- (void)dumpFileByURL:(NSURL *)url filename:(NSString *)filename extension:(NSString *)extension;
- (void)dumpFileByData:(NSData *)data filename:(NSString *)filename extension:(NSString *)extension;
@end

@interface AIKLoggingServiceAdapter (Logging)

+ (void)logLevel:(AIKLogLevel)logLevel message:(NSString *)message;
+ (void)logError:(NSString *)message, ...;
+ (void)logWarn:(NSString *)message, ...;
+ (void)logInfo:(NSString *)message, ...;
+ (void)logDebug:(NSString *)message, ...;
+ (void)logVerbose:(NSString *)message, ...;

@end

@interface AIKLoggingServiceAdapter (Filtering)
- (NSArray <NSString *>*)currentFilters;
- (void)applyFilters:(NSArray *)filters;
- (NSArray <NSString *>*)filtersForDebug;
- (NSArray <NSString *>*)filtersForRelease;
@end
