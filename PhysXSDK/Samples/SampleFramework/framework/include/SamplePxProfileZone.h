/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef SAMPLE_PROFILE_ZONE_H
#define SAMPLE_PROFILE_ZONE_H


#ifdef PHYSX_PROFILE_SDK

#include "physxprofilesdk/PxProfileScopedEvent.h"
#include "physxprofilesdk/PxProfileEventSender.h"
#include "physxprofilesdk/PxProfileEventNames.h"
#include "physxprofilesdk/PxProfileZone.h"

namespace physx { namespace profile {
#define AG_PERFMON_EVENT_DEFINITION_HEADER "AgPerfMonEventDefs.h"
#include "SampleProfileDeclareAgPerfmonEventInfo.h"
#undef AG_PERFMON_EVENT_DEFINITION_HEADER
}}

struct SampleProfileEventNameProvider : public physx::PxProfileNameProvider
{
	virtual physx::PxProfileNames getProfileNames() const;
};

#ifdef SAMPLE_PERF_SCOPE
#undef SAMPLE_PERF_SCOPE
#endif

#ifdef SAMPLE_PERF_SCOPE_PERF_DSCOPE
#undef SAMPLE_PERF_SCOPE_PERF_DSCOPE
#endif

#ifdef SAMPLE_PERF_SCOPE_PERF_SCOPE_STOP
#undef SAMPLE_PERF_SCOPE_PERF_SCOPE_STOP
#endif

#define SAMPLE_PERF_SCOPE(name)							   physx::profile::ScopedEventWithContext<true,physx::PxProfileEventSender,physx::profile::AgPerfmonEventIds::name> __scope(getEventBuffer(),0);
#define SAMPLE_PERF_SCOPE_PERF_DSCOPE(name, data)          physx::profile::eventValue( true,getEventBuffer(),physx::PxProfileEventSender,physx::profile::AgPerfmonEventIds::name,0,static_cast<PxI64>(data)); \
														   SAMPLE_PERF_SCOPE(name)
#define SAMPLE_PERF_SCOPE_PERF_SCOPE_STOP(data)            //unsupported at this time

#else

#define SAMPLE_PERF_SCOPE(name)
#define SAMPLE_PERF_SCOPE_PERF_DSCOPE(name, data)
#define SAMPLE_PERF_SCOPE_PERF_SCOPE_STOP(data)

#endif //PHYSX_PROFILE_SDK
 
#endif //SAMPLE_PROFILE_SDK_H
