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

#include "RenderSphereActor.h"
#include "RendererCapsuleShape.h"

using namespace physx;
using namespace SampleRenderer;

RenderSphereActor::RenderSphereActor(Renderer& renderer, PxReal radius)
{
	RendererShape* rs = new RendererCapsuleShape(renderer, 0.0f, radius);
	setRenderShape(rs);
}

RenderSphereActor::RenderSphereActor(const RenderSphereActor& src) : RenderBaseActor(src)
{
}

RenderSphereActor::~RenderSphereActor()
{
}
