//
//  BWBluetoothWolf.h
//  BWBluetoothWolf
//
//  Created by Lobanov Dmitry on 20.03.16.
//  Copyright © 2016 SmartAirkey. All rights reserved.
//

@import UIKit;
//! Project version number for BWBluetoothWolf.
FOUNDATION_EXPORT double BWBluetoothWolfVersionNumber;

//! Project version string for BWBluetoothWolf.
FOUNDATION_EXPORT const unsigned char BWBluetoothWolfVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <BWBluetoothWolf/PublicHeader.h>
//Wolf
#import <BWBluetoothWolf/BWBluetoothWolfBaseCentralManager.h>
#import <BWBluetoothWolf/BWBluetoothWolfLeaderOfPeripheralOnlyAndCentralOnlyPack.h>
#import <BWBluetoothWolf/BWBluetoothWolfConfiguration.h>
#import <BWBluetoothWolf/BWBluetoothWolfHabitat.h>
#import <BWBluetoothWolf/BWBluetoothWolfBuilder.h>
#import <BWBluetoothWolf/BWBluetoothWolfContext.h>
#import <BWBluetoothWolf/BWBluetoothPeripheralWolf.h>
#import <BWBluetoothWolf/BWBluetoothCentralWolf.h>
#import <BWBluetoothWolf/BWBluetoothBaseWolf.h>
//Connection
#import <BWBluetoothWolf/BWBluetoothWolfConnection.h>
//Transport
#import <BWBluetoothWolf/AIKBluetoothMessage.h>
//Helpers
#import <BWBluetoothWolf/NSData+BluetoothManipulations.h>
#import <BWBluetoothWolf/NSString+BluetoothManipulations.h>
//Errors
#import <BWBluetoothWolf/BWBluetoothWolfDescriptiveErrors.h>
//PublicSupplement
#import <BWBluetoothWolf/BWBluetoothDiagnostics.h>
#import <BWBluetoothWolf/BWBluetoothDeprecations.h>
//Protocols
#import <BWBluetoothWolf/BWBluetoothDebugInformationProtocol.h>
#import <BWBluetoothWolf/BWBluetoothIOProtocolExtension.h>
#import <BWBluetoothWolf/BWBluetoothDataStreamingProtocol.h>
#import <BWBluetoothWolf/BWBluetoothIOProtocol.h>
#import <BWBluetoothWolf/BWBluetoothWolfReportProtocol.h>
#import <BWBluetoothWolf/AIKBluetoothPeripheralDictionaryProtocol.h>
#import <BWBluetoothWolf/BWBluetoothWolfBaseChannelManagerProtocol.h>

//Fix it later. Some protocols are not for public use.
//For example, Some BaseCentralManager protocols are not for public.
//And, for example, Some BasePeripheralManager protocols are not for public.
//Project Protocols
#import <BWBluetoothWolf/BWBluetoothWolfConnectionManagerProtocol.h>
#import <BWBluetoothWolf/BWBluetoothWolfBaseCentralManagerProtocol.h>
#import <BWBluetoothWolf/BWBluetoothWolfConnectionProtocol.h>
#import <BWBluetoothWolf/BWBluetoothWolfBasePeripheralManagerProtocol.h>
