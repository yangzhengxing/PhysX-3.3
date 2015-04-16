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
#define SAMPLE_PROFILE_DEFINE_AG_PERFMON_EVENT_INFO_H

/**
 *	This header expects the macro:
 *	PX_PROFILE_EVENT_DEFINITION_HEADER to be defined to a string which is included 
 *	multiple times.
 *
 *	This header needs to be of the form:
 *	
DEFINE_EVENT( eventname )
 *
 *	Produces gPxProfileNames, a copyable object that names all the events and 
 *	subsystems.
 *
 *	
 */
#include "physxprofilesdk/PxProfileCompileTimeEventFilter.h"
#include "physxprofilesdk/PxProfileEventNames.h"
#include "PsUtilities.h"

#define DEFINE_EVENT( name ) PxProfileEventName( #name, PxProfileEventId( AgPerfmonEventIds::name, true ) ),
static PxProfileEventName gEventNames[] = {
#include AG_PERFMON_EVENT_DEFINITION_HEADER
};
#undef DEFINE_EVENT

static PxU32 gEventNamesCount = PX_ARRAY_SIZE( gEventNames );
static PxProfileNames gPxProfileNames( gEventNamesCount, gEventNames );

#undef SAMPLE_PROFILE_DEFINE_AG_PERFMON_EVENT_INFO_H
