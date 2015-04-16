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

#ifndef RENDER_BOX_ACTOR_H
#define RENDER_BOX_ACTOR_H

#include "RenderBaseActor.h"
#include "foundation/PxVec3.h"

namespace SampleRenderer
{
	class Renderer;
}

	class RenderBoxActor : public RenderBaseActor
	{
		public:
						RenderBoxActor(SampleRenderer::Renderer& renderer, const PxVec3& extents, const PxReal* uvs=NULL);
						RenderBoxActor(const RenderBoxActor&);
		virtual			~RenderBoxActor();
	};

#endif
