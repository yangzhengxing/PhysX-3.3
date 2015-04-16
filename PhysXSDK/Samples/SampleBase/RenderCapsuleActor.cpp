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

#include "RenderCapsuleActor.h"
#include "RendererCapsuleShape.h"
#include "extensions/PxShapeExt.h"

using namespace physx;
using namespace SampleRenderer;

RenderCapsuleActor::RenderCapsuleActor(Renderer& renderer, PxReal radius, PxReal halfHeight)
{
	RendererShape* rs = new RendererCapsuleShape(renderer, halfHeight, radius);
	setRenderShape(rs);

	// PT: seems there's a mismatch between the renderer's and the SDK's idea of what a default capsule pose should be
	mPhysicsToGraphicsRot = PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f));
}

void RenderCapsuleActor::setDimensions(PxReal halfHeight, PxReal radius0, PxReal radius1)
{
	RendererCapsuleShape* capsuleShape = static_cast<RendererCapsuleShape*>(getRenderShape());
	capsuleShape->setDimensions(halfHeight, radius0, radius1);
}

RenderCapsuleActor::RenderCapsuleActor(const RenderCapsuleActor& src) : RenderBaseActor(src)
{
}

RenderCapsuleActor::~RenderCapsuleActor()
{
}
