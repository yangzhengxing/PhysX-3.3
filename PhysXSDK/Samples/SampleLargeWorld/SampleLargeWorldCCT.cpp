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

#include "SampleLargeWorld.h"

#include "KinematicPlatform.h"
#include "SampleCCTActor.h"
#include "SampleCCTCameraController.h"
extern const char* gDynamic;

void SampleLargeWorld::onShapeHit(const PxControllerShapeHit& hit)
{
	defaultCCTInteraction(hit);
}

PxControllerBehaviorFlags SampleLargeWorld::getBehaviorFlags(const PxShape& shape, const PxActor& actor)
{
	return PxControllerBehaviorFlags(0);
}

PxControllerBehaviorFlags SampleLargeWorld::getBehaviorFlags(const PxController&)
{
	return PxControllerBehaviorFlags(0);
}

PxControllerBehaviorFlags SampleLargeWorld::getBehaviorFlags(const PxObstacle&)
{
	return PxControllerBehaviorFlag::eCCT_CAN_RIDE_ON_OBJECT|PxControllerBehaviorFlag::eCCT_SLIDE;
}

PxSceneQueryHitType::Enum SampleLargeWorld::preFilter(const PxFilterData& filterData, const PxShape* shape, const PxRigidActor* actor, PxSceneQueryFlags& queryFlags)
{
	PX_UNUSED(actor);
	const char* actorName = shape->getActor()->getName();
	if(actorName==gDynamic)
		return PxSceneQueryHitType::eNONE;

	return PxSceneQueryHitType::eBLOCK;
}

PxSceneQueryHitType::Enum SampleLargeWorld::postFilter(const PxFilterData& filterData, const PxQueryHit& hit)
{
	return PxSceneQueryHitType::eBLOCK;
}