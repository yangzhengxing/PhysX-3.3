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

#ifndef RENDER_SPHERE_ACTOR_H
#define RENDER_SPHERE_ACTOR_H

#include "RenderBaseActor.h"
#include "foundation/PxSimpleTypes.h"

	class RenderSphereActor : public RenderBaseActor
	{
		public:
					RenderSphereActor(SampleRenderer::Renderer& renderer, PxReal radius);
					RenderSphereActor(const RenderSphereActor&);
		virtual		~RenderSphereActor();
	};

#endif
