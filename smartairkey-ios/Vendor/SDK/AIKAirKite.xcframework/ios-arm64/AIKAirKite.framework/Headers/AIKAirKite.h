//
//  AIKAirKite.h
//  AIKAirKite
//
//  Created by Dmitry Lobanov on 12.10.2018.
//  Copyright © 2018 Dmitry Lobanov. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for AIKAirKite.
FOUNDATION_EXPORT double AIKAirKiteVersionNumber;

//! Project version string for AIKAirKite.
FOUNDATION_EXPORT const unsigned char AIKAirKiteVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <AIKAirKite/PublicHeader.h>

// well, a bitter in this honey.
// you should take into account headers that are in either Project or Public group.
// So, you can't just copy them, you must filter them by NOT IN PROJECT group. ( ONLY PUBLIC HEADERS! )
// find . -name '*.h' | pbcopy
// pbpaste | perl -lne 'm/([\w\+]+\.h)/ && print qq(#import <AIKAirKite/$1> // $_)' | pbcopy


#import <AIKAirKite/NSDate+SecurityEncoding.h> // ./Security/SecurityKit/NSDate+SecurityEncoding.h

#import <AIKAirKite/AIKCocoaLumberjackCustomLogFormat.h> // ./Services/Logging/AIKCocoaLumberjackCustomLogFormat.h
#import <AIKAirKite/AIKCocoaLumberjackingTextViewLogger.h> // ./Services/Logging/AIKCocoaLumberjackingTextViewLogger.h
#import <AIKAirKite/AIKLogger.h> // ./Services/Logging/AIKLogger.h

#import <AIKAirKite/AIKDeprecationDefines.h> // ./Supplement/AIKDeprecationDefines.h

#import <AIKAirKite/AIKBaseArrayStorage.h> // ./Utilities/Helpers/AIKBaseArrayStorage.h
#import <AIKAirKite/AIKBaseDictionaryStorage.h> // ./Utilities/Helpers/AIKBaseDictionaryStorage.h
#import <AIKAirKite/AIKBaseMapTableStorage.h> // ./Utilities/Helpers/AIKBaseMapTableStorage.h
#import <AIKAirKite/AIKBaseStorageWithSubscriptions.h> // ./Utilities/Helpers/AIKBaseStorageWithSubscriptions.h
#import <AIKAirKite/AIKBaseThresholdInterval.h> // ./Utilities/Helpers/AIKBaseThresholdInterval.h
#import <AIKAirKite/AIKEnumDescription.h> // ./Utilities/Helpers/AIKEnumDescription.h
#import <AIKAirKite/AIKSimilarityProtocol.h> // ./Utilities/Helpers/AIKSimilarityProtocol.h

#import <AIKAirKite/NSDictionary+ExtendedMethods.h> // ./Utilities/NSFoundation/NSDictionary+ExtendedMethods.h
#import <AIKAirKite/NSFoundationExtendedMethods.h> // ./Utilities/NSFoundation/NSFoundationExtendedMethods.h
#import <AIKAirKite/NSNumber+ExtendedMethods.h> // ./Utilities/NSFoundation/NSNumber+ExtendedMethods.h
#import <AIKAirKite/NSObject+ExtendedMethods.h> // ./Utilities/NSFoundation/NSObject+ExtendedMethods.h
#import <AIKAirKite/NSOperationQueue+ExtendedMethods.h> // ./Utilities/NSFoundation/NSOperationQueue+ExtendedMethods.h
#import <AIKAirKite/NSPointerArray+ExtendedMethods.h> // ./Utilities/NSFoundation/NSPointerArray+ExtendedMethods.h
#import <AIKAirKite/NSString+ExtendedMethods.h> // ./Utilities/NSFoundation/NSString+ExtendedMethods.h
#import <AIKAirKite/NSArray+ExtendedMethods.h> // ./Utilities/NSFoundation/NSArray+ExtendedMethods.h
#import <AIKAirKite/NSData+ExtendedMethods.h> // ./Utilities/NSFoundation/NSData+ExtendedMethods.h
#import <AIKAirKite/NSDate+ExtendedMethods.h> // ./Utilities/NSFoundation/NSDate+ExtendedMethods.h

#import <AIKAirKite/AIKLoggingServiceAdapter.h> // ./Services/ServicesManager/Logging/AIKLoggingServiceAdapter.h
#import <AIKAirKite/AIKBaseServiceAdapter.h> // ./Services/ServicesManager/AIKBaseServiceAdapter.h
#import <AIKAirKite/AIKBaseServiceAdapterHelpers.h> // ./Services/ServicesManager/AIKBaseServiceAdapterHelpers.h
#import <AIKAirKite/AIKServiceAdapterProtocol.h> // ./Services/ServicesManager/AIKServiceAdapterProtocol.h
#import <AIKAirKite/AIKServicesNames.h> // ./Services/ServicesManager/AIKServicesNames.h

