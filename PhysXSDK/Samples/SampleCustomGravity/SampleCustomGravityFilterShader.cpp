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


#include "PxPhysicsAPI.h"
#include "SampleCustomGravity.h"

static PxFilterFlags filter(PxFilterObjectAttributes attributes0, PxFilterData filterData0, 
							PxFilterObjectAttributes attributes1, PxFilterData filterData1,
							PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	pairFlags = PxPairFlag::eCONTACT_DEFAULT;
	return PxFilterFlags();
}

void SampleCustomGravity::customizeSceneDesc(PxSceneDesc& sceneDesc)
{
	sceneDesc.gravity		= PxVec3(0);
	sceneDesc.filterShader	= filter;
	sceneDesc.flags			|= PxSceneFlag::eREQUIRE_RW_LOCK;
}
