/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_TARGET_DESC_H
#define RENDERER_TARGET_DESC_H

#include <RendererConfig.h>

namespace SampleRenderer
{

	class RendererTargetDesc
	{
	public:
		RendererTexture2D **textures;
		PxU32               numTextures;

		RendererTexture2D  *depthStencilSurface;

	public:
		RendererTargetDesc(void);

		bool isValid(void) const;
	};

} // namespace SampleRenderer

#endif
