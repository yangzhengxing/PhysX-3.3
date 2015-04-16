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

#ifndef TEST_MOTION_GENERATOR
#define TEST_MOTION_GENERATOR

#include "PxPhysicsAPI.h"
#include "Test.h"


struct MotionGenerator
{
public:
	MotionGenerator();
	MotionGenerator(const PxTransform &pose, const PxVec3& linear, const PxVec3& angular);

public:
	const PxTransform& update(float time, float dt);

	PxVec3 getLinearVelocity(float time);
	PxVec3 getAngularVelocity(float time);

	PxVec3 mLinear, mAngular;
	PxTransform mTransform;
};

#endif // TEST_MOTION_GENERATOR
