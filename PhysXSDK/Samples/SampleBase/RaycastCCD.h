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

#ifndef RAYCAST_CCD_H
#define RAYCAST_CCD_H

#include "common/PxPhysXCommonConfig.h"

using namespace physx;

namespace physx
{
	class PxShape;
	class PxRigidActor;
};

	PxVec3	getShapeCenter(PxRigidActor* actor, PxShape* shape, const PxVec3& localOffset);
	bool	doRaycastCCD(PxRigidActor* actor, PxShape* shape, PxTransform& pose, PxVec3& newShapeCenter, const PxVec3& ccdWitness, const PxVec3& ccdWitnessOffset);

#endif
