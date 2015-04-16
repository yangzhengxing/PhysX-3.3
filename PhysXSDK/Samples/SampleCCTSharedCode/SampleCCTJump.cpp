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

#include "SampleCCTJump.h"

using namespace physx;

static PxF32 gJumpGravity = -50.0f;

Jump::Jump() :
	mV0			(0.0f),
	mJumpTime	(0.0f),
	mJump		(false)
{
}

void Jump::startJump(PxF32 v0)
{
	if(mJump)	return;
	mJumpTime = 0.0f;
	mV0	= v0;
	mJump = true;
}

void Jump::stopJump()
{
	if(!mJump)	return;
	mJump = false;
//mJumpTime = 0.0f;
//mV0	= 0.0f;
}

PxF32 Jump::getHeight(PxF32 elapsedTime)
{
	if(!mJump)	return 0.0f;
	mJumpTime += elapsedTime;
	const PxF32 h = gJumpGravity*mJumpTime*mJumpTime + mV0*mJumpTime;
	return h*elapsedTime;
}

