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

#include "SampleCharacterClothJump.h"

using namespace physx;

static PxF32 gJumpGravity = -25.0f;

SampleCharacterClothJump::SampleCharacterClothJump() :
	mV          (0.0f),
	mTime	(0.0f),
	mJump		(false),
	mFreefall   (false)
{
}

void SampleCharacterClothJump::startJump(PxF32 v0)
{
	if (mJump) return;
	if (mFreefall) return;
	mV = v0;
	mJump = true;
}

void SampleCharacterClothJump::reset()
{
	// reset jump state at most every half a second
	// otherwise we might miss jump events
	if (mTime < 0.5f)
		return;

	mFreefall = false;
	mJump = false;
	mV = 0.0f;
	mTime = 0.0f;
}

void SampleCharacterClothJump::tick(PxF32 dtime)
{
	mTime += dtime;
	mV += gJumpGravity * dtime;
	const PxReal vlimit = -25.0f;
	if (mV < vlimit)
	{
		// limit velocity in freefall so that character does not fall at rocket speed.
		mV = vlimit;
		mFreefall = true;
		mJump = false;
	}
}

PxF32 SampleCharacterClothJump::getDisplacement(PxF32 dtime)
{
	return mV * dtime;
}

