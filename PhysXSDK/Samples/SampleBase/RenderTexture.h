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

#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H

#include "RenderBaseObject.h"
#include "common/PxPhysXCommonConfig.h"
#include "foundation/PxVec3.h"
#include <RendererTexture2D.h>

namespace SampleRenderer
{
	class Renderer;
}

	class RenderTexture : public RenderBaseObject
	{
		public:
													RenderTexture(SampleRenderer::Renderer& renderer, PxU32 id, PxU32 width, PxU32 height, const void* data);
													RenderTexture(SampleRenderer::Renderer& renderer, PxU32 id, SampleRenderer::RendererTexture2D* texture);
		virtual										~RenderTexture();

				PxU32								mID;
				SampleRenderer::RendererTexture2D*	mTexture;
				bool								mOwnsTexture;
	};

#endif
