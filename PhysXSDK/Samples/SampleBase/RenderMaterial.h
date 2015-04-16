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

#ifndef RENDER_MATERIAL_H
#define RENDER_MATERIAL_H

#include "RenderBaseObject.h"
#include "common/PxPhysXCommonConfig.h"
#include "foundation/PxVec3.h"

namespace SampleRenderer
{
	class Renderer;
	class RendererMaterial;
	class RendererMaterialInstance;
}

	class RenderTexture;

	class RenderMaterial : public RenderBaseObject
	{
		public:
															RenderMaterial(SampleRenderer::Renderer& renderer, 
																			const PxVec3& diffuseColor, 
																			PxReal opacity, 
																			bool doubleSided, 
																			PxU32 id, 
																			RenderTexture* texture,
																			bool lit = true,
																			bool flat = false,
																			bool instanced = false);

															RenderMaterial(SampleRenderer::Renderer& renderer, 
																			SampleRenderer::RendererMaterial* mat, 
																			SampleRenderer::RendererMaterialInstance* matInstance, 
																			PxU32 id);
		virtual												~RenderMaterial();

		// the intent of this function is to update shaders variables, when needed (e.g. on resize)
		virtual void										update(SampleRenderer::Renderer& renderer);
				void										setDiffuseColor(const PxVec4& color);
				void										setParticleSize(const PxReal particleSize);
				void										setShadeMode(bool flat);

				SampleRenderer::RendererMaterial*			mRenderMaterial;
				SampleRenderer::RendererMaterialInstance*	mRenderMaterialInstance;
				PxU32										mID;
				bool										mDoubleSided;
				bool										mOwnsRendererMaterial;
	};

#endif
