//
//  TCTransportCamel.h
//  TCTransportCamel
//
//  Created by Lobanov Dmitry on 18.08.16.
//  Copyright © 2016 SmartAirkey. All rights reserved.
//

@import UIKit;

//! Project version number for TCTransportCamel.
FOUNDATION_EXPORT double TCTransportCamelVersionNumber;

//! Project version string for TCTransportCamel.
FOUNDATION_EXPORT const unsigned char TCTransportCamelVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <TCTransportCamel/PublicHeader.h>

// DataStreaming
#import <TCTransportCamel/TCTransportDataStreamer.h>
#import <TCTransportCamel/TCTransportDataStreamingManager.h>
#import <TCTransportCamel/TCTransportDataStreamingManagerProtocol.h>
#import <TCTransportCamel/TCTransportDataStreamingProtocol.h>

// IO/MessageReceiving
#import <TCTransportCamel/TCTransportMessageReceivingHandler.h>

// Transport/Coder
#import <TCTransportCamel/TCTransportCoderFactory.h>
#import <TCTransportCamel/TCTransportCoderProtocol.h>
#import <TCTransportCamel/TCTransportCoder.h>
