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

#ifndef SAMPLE_CHARACTER_CLOTH_PLATFORM_H
#define SAMPLE_CHARACTER_CLOTH_PLATFORM_H

#include "PhysXSample.h"
#include "characterkinematic/PxController.h" 
#include "SampleAllocator.h"
#include "SampleAllocatorSDKClasses.h"

///////////////////////////////////////////////////////////////////////////////
class SampleCharacterClothPlatform : public SampleAllocateable
{
public:

	///////////////////////////////////////////////////////////////////////////////
	enum {
		ePLATFORM_TYPE_STATIC,
		ePLATFORM_TYPE_MOVING,
		ePLATFORM_TYPE_TRIGGERED,
	};

	///////////////////////////////////////////////////////////////////////////////
	SampleCharacterClothPlatform();
	~SampleCharacterClothPlatform() {}

	///////////////////////////////////////////////////////////////////////////////
	PX_FORCE_INLINE	PxRigidDynamic*	getPhysicsActor() { return mActor;}
	PX_FORCE_INLINE	PxReal getTravelTime() const { return mTravelTime; }
	PX_FORCE_INLINE PxU32 getType() const { return mType; }

	PX_FORCE_INLINE void   setActive(bool b) { mActive = b; }
	PX_FORCE_INLINE	void   setTravelTime(PxReal t) { mTravelTime = t; }
	PX_FORCE_INLINE void   setType(PxU32 t) { mType = t; }

	///////////////////////////////////////////////////////////////////////////////
	void init(PxRigidDynamic* actor, PxReal travelTime, const PxVec3& offsetTarget = PxVec3(0,0,0) );
	void release();
	void reset();
	void update(PxReal dtime);

protected:
	PxRigidDynamic*		mActor;
	PxReal				mCurrentTime;
	PxReal				mTravelTime;
	PxVec3              mStart;
	PxVec3              mTarget;
	bool                mFlip;
	PxU32               mType;
	bool                mActive;
};

#endif
