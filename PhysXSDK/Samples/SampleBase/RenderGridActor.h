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

#ifndef RENDER_GRID_ACTOR_H
#define RENDER_GRID_ACTOR_H

#include "RenderBaseActor.h"

namespace SampleRenderer
{
	class Renderer;
}

	class RenderGridActor : public RenderBaseActor
	{
		public:
			RenderGridActor(SampleRenderer::Renderer& renderer, PxU32 size, PxReal cellSize, PxQuat v = PxQuat(PxIdentity));
		virtual			~RenderGridActor();

		virtual	void	update(float deltaTime);
	};

#endif
