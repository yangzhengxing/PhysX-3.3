/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_TEXTURE_DESC_H
#define RENDERER_TEXTURE_DESC_H

#include <RendererTexture.h>

namespace SampleRenderer
{

	class RendererTextureDesc
	{
	public:
		RendererTexture::Format     format;
		RendererTexture::Filter     filter;
		RendererTexture::Addressing addressingU;
		RendererTexture::Addressing addressingV;
		RendererTexture::Addressing addressingW;

		PxU32						width;
		PxU32						height;
		PxU32						depth;
		PxU32						numLevels;

		bool						renderTarget;

		void*						data;

	public:
		RendererTextureDesc(void);

		bool isValid(void) const;
	};

} // namespace SampleRenderer

#endif
