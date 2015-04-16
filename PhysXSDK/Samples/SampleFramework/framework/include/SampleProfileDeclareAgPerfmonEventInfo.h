/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

// no include guard on purpose!
#define SAMPLE_PROFILE_DECLARE_AG_PERFMON_EVENT_INFO_H

/**
 *	This header expects the macro:
 *	PX_PROFILE_EVENT_DEFINITION_HEADER to be defined to a string which is included 
 *	in order to produce the enum and event id lists.
 * 
 *	This header needs to be of the form:
 *	
DEFINE_EVENT( eventname )
 */
#include "physxprofilesdk/PxProfileCompileTimeEventFilter.h"
#include "physxprofilesdk/PxProfileEventNames.h"


//Event id enumeration
#define DEFINE_EVENT( name ) name,
struct AgPerfmonEventIds
{
	enum Enum
	{
		UnknownEvent = 0,
#include AG_PERFMON_EVENT_DEFINITION_HEADER
	};
};
#undef DEFINE_EVENT



#undef SAMPLE_PROFILE_DECLARE_AG_PERFMON_EVENT_INFO_H
