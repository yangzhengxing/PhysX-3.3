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

#include "ExtPulleyJoint.h"
#include "ExtConstraintHelper.h"
#include "PxTolerancesScale.h"

namespace physx
{
namespace Ext
{
	PxU32 PulleyJointSolverPrep(Px1DConstraint* constraints,
		PxVec3& body0WorldOffset,
		PxU32 maxConstraints,
		PxConstraintInvMassScale&,
		const void* constantBlock,
		const PxTransform& bA2w,
		const PxTransform& bB2w)
	{		
		PX_UNUSED(maxConstraints);

		const PulleyJointData& data = *reinterpret_cast<const PulleyJointData*>(constantBlock);

		PxTransform cA2w = bA2w.transform(data.c2b[0]);
		PxTransform cB2w = bB2w.transform(data.c2b[1]);

		body0WorldOffset = cB2w.p - bA2w.p;

		PxVec3 directionA = data.pulley[0] - cA2w.p;
		PxReal distanceA = directionA.normalize();

		PxVec3 directionB = data.pulley[1] - cB2w.p;
		PxReal distanceB = directionB.normalize();
		directionB *= data.ratio;

		PxReal totalDistance = distanceA + distanceB;

		// compute bias:
		PxReal bias = (data.distance - totalDistance); 

		Px1DConstraint *c = constraints;
		// constraint is breakable, so we need to output forces
		c->flags = Px1DConstraintFlag::eOUTPUT_FORCE;

		if (bias < 0.0f) 
		{
			c->maxImpulse = PX_MAX_F32;
			c->minImpulse = 0;
			c->geometricError = bias + data.tolerance; 
		}
		else if(bias > 0.0f)
		{
			c->maxImpulse = 0;
			c->minImpulse = -PX_MAX_F32;
			c->geometricError = bias - data.tolerance; 
		}

		c->linear0 = directionA;		c->angular0 = (cA2w.p - bA2w.p).cross(c->linear0);		
		c->linear1 = -directionB;		c->angular1 = (cB2w.p - bB2w.p).cross(c->linear1);		

		if (data.stiffness)
		{
			c->flags |= Px1DConstraintFlag::eSPRING;
			c->mods.spring.stiffness = data.stiffness;
			c->mods.spring.damping  = data.damping;
		}

		return 1;
	}


}//namespace

}

