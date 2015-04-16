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

#include "SampleCharacterCloth.h"

#include "SampleCharacterClothPlatform.h"


///////////////////////////////////////////////////////////////////////////////
SampleCharacterClothPlatform::SampleCharacterClothPlatform() : 
	mActor(NULL), 
	mCurrentTime(0.0f), 
	mTravelTime(0.0f), 
	mStart(0.0f),
	mTarget(0.0f),
	mFlip(false),
	mType(ePLATFORM_TYPE_MOVING),
	mActive(true)
	{
	}

///////////////////////////////////////////////////////////////////////////////
void SampleCharacterClothPlatform::init(PxRigidDynamic* actor, PxReal travelTime, const PxVec3& offsetTarget)
{
	mActor = actor;
	mCurrentTime = 0.0f;
	mTravelTime = travelTime;

	mStart = mActor->getGlobalPose().p;
	mTarget = mStart + offsetTarget;

	reset();
}

///////////////////////////////////////////////////////////////////////////////
void SampleCharacterClothPlatform::release()
{
	delete this;
}

///////////////////////////////////////////////////////////////////////////////
void SampleCharacterClothPlatform::reset()
{
	mCurrentTime = 0.0f;
	mFlip = false;

	switch (mType)
	{
	case ePLATFORM_TYPE_MOVING:
		mActive = true;
		break;
	default:
		mActive = false;
	}

	update(0.0f);
}

///////////////////////////////////////////////////////////////////////////////
void SampleCharacterClothPlatform::update(PxReal dtime)
{
	PxReal t = mCurrentTime / mTravelTime;

	PxTransform pose = mActor->getGlobalPose();
	if (!mFlip)
	{
		pose.p = (1 - t) * mStart + t * mTarget;
	}
	else
		pose.p = t * mStart + (1-t) * mTarget;

	mActor->setKinematicTarget(pose);

	if (mActive == false)
		return;

	mCurrentTime += dtime;

	if (mCurrentTime > mTravelTime)
	{
		mCurrentTime -= mTravelTime;
		mFlip = !mFlip;
	}
}

///////////////////////////////////////////////////////////////////////////////
void SampleCharacterCloth::updatePlatforms(float dtime)
{
	const size_t nbPlatforms = mPlatforms.size();
	for(PxU32 i = 0;i < nbPlatforms;i++)
	{
		mPlatforms[i]->update(dtime);
	}
}