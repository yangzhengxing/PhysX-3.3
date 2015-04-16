/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererTextureDesc.h>

using namespace SampleRenderer;

RendererTextureDesc::RendererTextureDesc(void)
{
	format       = RendererTexture::NUM_FORMATS;
	filter       = RendererTexture::FILTER_LINEAR;
	addressingU  = RendererTexture::ADDRESSING_WRAP;
	addressingV  = RendererTexture::ADDRESSING_WRAP;
	addressingW  = RendererTexture::ADDRESSING_WRAP;
	width        = 0;
	height       = 0;
	depth        = 1;
	numLevels    = 0;
	renderTarget = false;
	data         = NULL;
}


bool RendererTextureDesc::isValid(void) const
{
	bool ok = true;
	if(format      >= RendererTexture2D::NUM_FORMATS)    ok = false;
	if(filter      >= RendererTexture2D::NUM_FILTERS)    ok = false;
	if(addressingU >= RendererTexture2D::NUM_ADDRESSING) ok = false;
	if(addressingV >= RendererTexture2D::NUM_ADDRESSING) ok = false;
	if(width <= 0 || height <= 0 || depth <= 0) ok = false; // TODO: check for power of two.
	if(numLevels <= 0) ok = false;
	if(renderTarget)
	{
		if(depth > 1) ok = false;
		if(format == RendererTexture2D::FORMAT_DXT1) ok = false;
		if(format == RendererTexture2D::FORMAT_DXT3) ok = false;
		if(format == RendererTexture2D::FORMAT_DXT5) ok = false;
	}
	return ok;
}
