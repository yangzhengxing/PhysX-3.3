/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  

#ifndef SNIPPET_VEHICLE_PROFILER_H
#define SNIPPET_VEHICLE_PROFILER_H

#ifdef PX_PROFILE

#include "PxPhysicsAPI.h"
#include "physxprofilesdk/PxProfileZone.h"
#include "../SnippetUtils/SnippetUtils.h"

using namespace physx;

class VehicleProfiler
{
public:

	VehicleProfiler()
		: mStartTimes(NULL),
		  mAccumulatedTimes(NULL),
		  mProfileEventNames(NULL),
		  mNumProfileEventNames(0),
		  mEventNameProvider(NULL, 0),
		  mProfiler(NULL)
	{
	}

	~VehicleProfiler()
	{
	}

	enum
	{
		eMAX_NAME_LENGTH = 64
	};

	static VehicleProfiler* allocate(const char profileNames[][eMAX_NAME_LENGTH], const PxU32 numProfileZones, PxProfileZoneManager* profileZoneManager, PxAllocatorCallback& allocator)
	{
		const PxU32 byteSize = sizeof(VehicleProfiler) + sizeof(PxU64)*numProfileZones + sizeof(PxU64)*numProfileZones + sizeof(PxProfileEventName)*numProfileZones;
		PxU8* buffer = (PxU8*)allocator.allocate(byteSize, NULL, NULL, 0);

		VehicleProfiler* vehProfiler = (VehicleProfiler*)buffer;
		new(vehProfiler) VehicleProfiler();
		buffer += sizeof(VehicleProfiler);

		vehProfiler->mStartTimes = (PxU64*)buffer;
		buffer += sizeof(PxU64)*numProfileZones;
		PxMemZero(vehProfiler->mStartTimes, sizeof(PxU64)*numProfileZones);

		vehProfiler->mAccumulatedTimes = (PxU64*)buffer;
		buffer += sizeof(PxU64)*numProfileZones;
		PxMemZero(vehProfiler->mAccumulatedTimes, sizeof(PxU64)*numProfileZones);

		vehProfiler->mProfileEventNames = (PxProfileEventName*)buffer;
		buffer += sizeof(PxProfileEventName)*numProfileZones;
		for(PxU16 i = 0; i < numProfileZones; i++)
		{
			vehProfiler->mProfileEventNames[i] = PxProfileEventName(profileNames[i], PxProfileEventId(i, true));
		}
		vehProfiler->mNumProfileEventNames = numProfileZones;

		vehProfiler->mEventNameProvider = EventNameProvider(vehProfiler->mProfileEventNames, numProfileZones);

		vehProfiler->mProfiler = &PxProfileZone::createProfileZone(&allocator, "VehicleProfiler", vehProfiler->mEventNameProvider);

		profileZoneManager->addProfileZone(*vehProfiler->mProfiler);

		return vehProfiler;
	}

	void free(PxAllocatorCallback& allocator)
	{
		mProfiler->release();
		allocator.deallocate(this);
	}

	void start(const PxU16 zone)
	{
		mStartTimes[zone] = SnippetUtils::getCurrentTimeCounterValue();
		mProfiler->startEvent(zone, 0);
	}
	void stop(const PxU16 zone)
	{
		mAccumulatedTimes[zone] += SnippetUtils::getCurrentTimeCounterValue() - mStartTimes[zone];
		mProfiler->stopEvent(zone, 0);
	}

	PxF32 getTotalTimeMs(const PxU16 zone) const
	{
		return SnippetUtils::getElapsedTimeInMilliseconds(mAccumulatedTimes[zone]);
	}

private:

	PxU64* mStartTimes;
	PxU64* mAccumulatedTimes;

	PxProfileEventName* mProfileEventNames;
	PxU32 mNumProfileEventNames;

	class EventNameProvider : public physx::PxProfileNameProvider
	{
	public:

		EventNameProvider(PxProfileEventName* profileEventNames, const PxU32 numProfileEventNames)
			: mProfileEventNames(profileEventNames),
			  mNumProfileEventNames(numProfileEventNames)
		{
		}

		virtual PxProfileNames getProfileNames() const {return PxProfileNames(mNumProfileEventNames, mProfileEventNames);}

	private:

		PxProfileEventName* mProfileEventNames;
		PxU32 mNumProfileEventNames;
	};
	EventNameProvider mEventNameProvider;

	PxProfileZone* mProfiler;	


};

#endif // PX_PROFILE

#endif //SNIPPET_VEHICLE_PROFILER_H
