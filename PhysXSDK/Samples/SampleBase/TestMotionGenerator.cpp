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

#include "TestMotionGenerator.h"

//----------------------------------------------------------------------------//
MotionGenerator::MotionGenerator() 
:	mLinear(0.0f),
	mAngular(0.0f),
	mTransform(PxTransform(PxIdentity))
{
}

//----------------------------------------------------------------------------//
MotionGenerator::MotionGenerator(const PxTransform &pose, const PxVec3& linear, const PxVec3& angular) 
:	mLinear(linear),
	mAngular(angular),
	mTransform(pose)
{
}

//----------------------------------------------------------------------------//
PxVec3 MotionGenerator::getLinearVelocity( float time )
{
	float t = time - (int(time) & ~0xf);
	const float scale = 0.25f * PxPi;

	if(t > 0 && t < 2)
		return -scale * sinf(t * 0.5f * PxPi) * mLinear;

	if(t > 8 && t < 10)
		return +scale * sinf(t * 0.5f * PxPi) * mLinear;

	return PxVec3(0.0f);
}

//----------------------------------------------------------------------------//
PxVec3 MotionGenerator::getAngularVelocity( float time )
{
	float t = time - (int(time) & ~0xf);

	if(t > 4 && t < 6)
		return +PxPi * mAngular;

	if(t > 12 && t < 14)
		return -PxPi * mAngular;

	return PxVec3(0.0f);
}

static PxQuat computeQuatFromAngularVelocity(const PxVec3 &omega)
{
	PxReal angle = omega.magnitude();

	if (angle < 1e-5f) 
	{
		return PxQuat(PxIdentity);
	} else {
		PxReal s = sin( 0.5f * angle ) / angle;
		PxReal x = omega[0] * s;
		PxReal y = omega[1] * s;
		PxReal z = omega[2] * s;
		PxReal w = cos( 0.5f * angle );
		return PxQuat(x,y,z,w);
	}
}
//----------------------------------------------------------------------------//
const PxTransform& MotionGenerator::update(float time, float dt)
{
	PxVec3 dw = dt * getAngularVelocity(time);
	PxQuat dq = computeQuatFromAngularVelocity(dw);

	mTransform.q = (dq * mTransform.q).getNormalized();
	mTransform.p += dt * getLinearVelocity(time);
	
	return mTransform;
}





