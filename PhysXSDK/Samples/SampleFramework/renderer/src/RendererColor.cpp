/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererColor.h>

using namespace SampleRenderer;

RendererColor::RendererColor(void)
{

}

RendererColor::RendererColor(PxU8 _r, PxU8 _g, PxU8 _b, PxU8 _a)
{
	r=_r;
	g=_g;
	b=_b;
	a=_a;
}

RendererColor::RendererColor(PxU32 rgba)
{
	b = (PxU8)((rgba>>16) & 0xff);
	g = (PxU8)((rgba>>8)  & 0xff);
	r = (PxU8)((rgba)     & 0xff);
	a = 255;
}

void RendererColor::swizzleRB(void)
{
	PxU8 t = b;
	b = r;
	r = t;
}
