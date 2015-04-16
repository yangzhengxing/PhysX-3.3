/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_MATERIAL_DESC_H
#define RENDERER_MATERIAL_DESC_H

#include <RendererMaterial.h>

namespace SampleRenderer
{

	class RendererMaterialDesc
	{
	public:
		RendererMaterial::Type          type;

		RendererMaterial::AlphaTestFunc alphaTestFunc;
		float                           alphaTestRef;

		bool                            blending;
		bool							instanced;
		RendererMaterial::BlendFunc     srcBlendFunc;
		RendererMaterial::BlendFunc     dstBlendFunc;

		const char                     *geometryShaderPath;
		const char                     *hullShaderPath;
		const char                     *domainShaderPath;
		const char                     *vertexShaderPath;
		const char                     *fragmentShaderPath;

		//all passes enabled
		bool							enabledPasses[RendererMaterial::NUM_PASSES];
		//instancing enabled
		bool							enableInstancing;

	public:
		RendererMaterialDesc(void);

		bool isValid(void) const;
	};

} // namespace SampleRenderer

#endif
