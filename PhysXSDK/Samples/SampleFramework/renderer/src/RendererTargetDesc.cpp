/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererTargetDesc.h>
#include <RendererTexture2D.h>

using namespace SampleRenderer;

RendererTargetDesc::RendererTargetDesc(void)
{
	textures            = 0;
	numTextures         = 0;
	depthStencilSurface = 0;
}

bool RendererTargetDesc::isValid(void) const
{
	bool ok = true;
	PxU32 width  = 0;
	PxU32 height = 0;
	if(numTextures != 1) ok = false; // for now we only support single render targets at the moment.
	if(textures)
	{
		if(textures[0])
		{
			width  = textures[0]->getWidth();
			height = textures[0]->getHeight();
		}
		for(PxU32 i=0; i<numTextures; i++)
		{
			if(!textures[i]) ok = false;
			else
			{
				if(width  != textures[i]->getWidth())  ok = false;
				if(height != textures[i]->getHeight()) ok = false;
				const RendererTexture2D::Format format = textures[i]->getFormat();
				if(     format == RendererTexture2D::FORMAT_DXT1) ok = false;
				else if(format == RendererTexture2D::FORMAT_DXT3) ok = false;
				else if(format == RendererTexture2D::FORMAT_DXT5) ok = false;
			}
		}
	}
	else
	{
		ok = false;
	}
	if(depthStencilSurface)
	{
		if(width  != depthStencilSurface->getWidth())  ok = false;
		if(height != depthStencilSurface->getHeight()) ok = false;
		if(!RendererTexture2D::isDepthStencilFormat(depthStencilSurface->getFormat())) ok = false;
	}
	else
	{
		ok = false;
	}
	return ok;
}
