//
//  DIDeviceInteractionLionDeprecations.h
//  DIDeviceInteractionLion
//
//  Created by Dmitry on 05.04.17.
//  Copyright © 2017 Dmitry. All rights reserved.
//

#ifndef DIDeviceInteractionLionDeprecations_h
#define DIDeviceInteractionLionDeprecations_h

#ifndef STR
#define STR(str) #str
#endif

#pragma mark - Versions
#define DIDeviceInteractionLion_VERSION_0_5_0 0.5.0

#pragma mark - Deprecations

#ifndef __deprecated_msg_at_version
#define __deprecated_msg_at_version(version) __deprecated_msg("Deprecated. Could be removed in next version" STR(version))
#endif

#pragma mark - Warnings

#define DIDeviceInteractionLion_BIG_BONE_LEG "Big Bone Leg"
#define DIDeviceInteractionLion_BIG_BONE_LEG_Description "Big Bone Leg Description"

#ifndef DIDeviceInteractionLion__warning__name_and_msg_and_solution
#define DIDeviceInteractionLion__warning__name_and_msg_and_solution(name, msg, solution) ("Warning "STR(name)" occured. Try to refactoring code later. "STR(msg) "Possible solution: "STR(solution))
#endif

/*
 USAGE: WARNING
 
 #pragma message
 __warning__name_and_msg_and_solution(name, msg)
 */
#endif /* DIDeviceInteractionLionDeprecations_h */
