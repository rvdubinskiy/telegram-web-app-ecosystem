//
//  AIKDeprecationDefines.h
//  SmartAirkey
//
//  Created by Lobanov Dmitry on 20.06.16.
//  Copyright © 2016 AirkeyTeam. All rights reserved.
//

#ifndef AIKDeprecationDefines_h
#define AIKDeprecationDefines_h

#ifndef STR
#define STR(str) #str
#endif

#pragma mark - Versions
#define SMARTAIRKEY_VERSION_1_1_15 1.1.15
#define SMARTAIRKEY_VERSION_1_1_16 1.1.16
#define SMARTAIRKEY_VERSION_1_1_17 1.1.17
#define SMARTAIRKEY_VERSION_1_1_18 1.1.18
#define SMARTAIRKEY_VERSION_1_2_0 1.2.0
#define SMARTAIRKEY_VERSION_2_1_0 2.1.0
#define SMARTAIRKEY_VERSION_2_2_0 2.2.0
#define SMARTAIRKEY_VERSION_2_3_0 2.3.0

#pragma mark - Deprecations
#ifndef __deprecated_default_msg_at_next_release_versions
#define __deprecated_default_msg_at_next_release_versions __deprecated_msg("method is deprecated. don't forget to remove it later in next release or releases. possible doom version: somewhere in future.")
#endif
#ifndef __deprecated_default_msg_at_next_release_version
#define __deprecated_default_msg_at_next_release_version(version) __deprecated_msg("deprecated. don't forget to remove it later in next release. possible doom version: "STR(version))
#endif

#ifndef __deprecated_default_msg_at_next_release_version_1_1_15
#define __deprecated_default_msg_at_next_release_version_1_1_15 __deprecated_default_msg_at_next_release_version(SMARTAIRKEY_VERSION_1_1_15)
#endif

#ifndef __deprecated_default_msg_at_next_release_version_1_1_16
#define __deprecated_default_msg_at_next_release_version_1_1_16 __deprecated_default_msg_at_next_release_version(SMARTAIRKEY_VERSION_1_1_16)
#endif

#ifndef __deprecated_default_msg_at_next_release_version_1_1_17
#define __deprecated_default_msg_at_next_release_version_1_1_17 __deprecated_default_msg_at_next_release_version(SMARTAIRKEY_VERSION_1_1_17)
#endif
#ifndef __deprecated_default_msg_at_next_release_version_1_1_18
#define __deprecated_default_msg_at_next_release_version_1_1_18 __deprecated_default_msg_at_next_release_version(SMARTAIRKEY_VERSION_1_1_18)
#endif

#ifndef __deprecated_default_msg_at_next_release_version_2_1_0
#define __deprecated_default_msg_at_next_release_version_2_1_0 __deprecated_default_msg_at_next_release_version(SMARTAIRKEY_VERSION_2_1_0)
#endif

#pragma mark - Warnings
#ifndef SMARTAIRKEY__warning__name_and_msg
#define SMARTAIRKEY__warning__name_and_msg(name, msg) ("Warning "STR(name)" occured. Do the following to fixit. "STR(msg))
#endif

#ifndef SMARTAIRKEY__warning__name_and_msg_and_solution
#define SMARTAIRKEY__warning__name_and_msg_and_solution(name, msg, solution) ("Warning "STR(name)" occured. Do the following to fixit. "STR(msg)". Solution: "STR(solution))
#endif

#define SMARTAIRKEY_WARNING_DEPENDENCY_IMPROPER_DEPENDENCY_INJECTION "Improper dependency injection!"
#define SMARTAIRKEY_WARNING_DEPENDENCY_IMPROPER_DEPENDENCY_INJECTION_DESCRIPTION "You may need to somehow pass this dependency or even remove it one day. I suggest to remove it when you've become more powerful."

#define SMARTAIRKEY_WARNING_SERVICES_INCONSISTENCY "Services Inconsistency!"
#define SMARTAIRKEY_WARNING_SERVICES_INCONSISTENCY_DESCRIPTION "You need to separate applications states (login/logout) from system states (setup, teardown). System states are emitted by system events in UIApplicationDelegate like applicationDidFinishLaunching:"
#define SMARTAIRKEY_WARNING_SERVICES_CORE_REPLACEMENT "Services Core Replacement"
#define SMARTAIRKEY_WARNING_SERVICES_CORE_REPLACEMENT_DESCRIPTION "This service functionality could be replaced or extended by appropriate service"
#define SMARTAIRKEY_WARNING_SERVICES_CORE_REPLACEMENT_NAME_SPOTLIGHT_INDEX "Spotlight Index Extension"
#define SMARTAIRKEY_WARNING_SERVICES_CORE_REPLACEMENT_NAME_NOTIFICATIONS "Notification Extension"

#define SMARTAIRKEY_WARNING_MODULES_TANGLED_UP "Modules are tangled up!"
#define SMARTAIRKEY_WARNING_MODULES_TANGLED_UP_DESCRIPTION "You need to separate several modules. This place is belong to one of the modules. Choose one and wipe out all others."
#define SMARTAIRKEY_WARNING_OBSOLETE_FILE_CONTENT "File content is obsolete"
#define SMARTAIRKEY_WARNING_OBSOLETE_FILE_CONTENT_DESCRIPTION "You should consider several options from deprecating file by removing it to Deprecated folder or even removing file from project and moving it to trash."
#define SMARTAIRKEY_TODOS "TODO:"
#define SMARTAIRKEY_TODOS_DONT_FORGET_TO_LOCALIZE "Don't forget to localize"
#define SMARTAIRKEY_TODOS_DONT_FORGET_TO_UNCOMMENT_WHEN_NEEDED "Don't forget to uncomment when needed"
#define SMARTAIRKEY_TODOS_DONT_FORGET_TO_REMOVE "Don't forget to remove"
#define SMARTAIRKEY_TODOS_DONT_FORGET_TO_REVIEW_FILE_CONTENT "Don't forget to review file content"
#define SMARTAIRKEY_TODOS_SOLVE_ARCHITECTURE_PUZZLE "Solve Architecture puzzle."
#define SMARTAIRKEY_TODOS_SOLVE_ARCHITECTURE_PUZZLE_STRONG_VS_WEAK_CYCLES "Solve Architecture puzzle. Strong vs weak cycles."
#endif /* AIKDeprecationDefines_h */
