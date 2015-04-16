/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_COLOR_H
#define RENDERER_COLOR_H

#include <RendererConfig.h>

namespace SampleRenderer
{

	class RendererColor
	{
		public:

			// use the API color format for OpenGL platforms
#if !(defined(RENDERER_PS3) || defined(RENDERER_ANDROID))
			PxU8 b, g, r, a;
#else
			PxU8 r, g, b, a;
#endif

		public:
			RendererColor(void);
			RendererColor(PxU8 r, PxU8 g, PxU8 b, PxU8 a = 255);

			// conversion constructor, format must be 0xAARRGGBB (but alpha is ignored)
			RendererColor(PxU32 rgba);
			void swizzleRB(void);
	};

	PX_INLINE RendererColor lerp( const RendererColor& start, const RendererColor& end, float s )
	{
		return RendererColor(
			start.r + PxU8(( end.r - start.r ) * s),
			start.g + PxU8(( end.g - start.g ) * s),
			start.b + PxU8(( end.b - start.b ) * s),
			start.a + PxU8(( end.a - start.a ) * s));
	}

} // namespace SampleRenderer

#endif
