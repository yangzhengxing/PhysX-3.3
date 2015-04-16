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

#include "SamplePreprocessor.h"
#include "RendererMemoryMacros.h"
#include "RenderTexture.h"
#include "Renderer.h"
#include "RendererTexture2DDesc.h"

using namespace physx;
using namespace SampleRenderer;

RenderTexture::RenderTexture(Renderer& renderer, PxU32 id, PxU32 width, PxU32 height, const void* data) :
	mID				(id),
	mTexture		(NULL),
	mOwnsTexture	(true)
{
	RendererTexture2DDesc tdesc;

#if !defined(RENDERER_PS3)
	tdesc.format	= RendererTexture2D::FORMAT_B8G8R8A8;
#else
	tdesc.format	= RendererTexture2D::FORMAT_R8G8B8A8;
#endif

	tdesc.width		= width;
	tdesc.height	= height;
	tdesc.numLevels	= 1;
/*
	tdesc.filter;
	tdesc.addressingU;
	tdesc.addressingV;
	tdesc.renderTarget;
*/
	PX_ASSERT(tdesc.isValid());
	mTexture		= renderer.createTexture2D(tdesc);
	PX_ASSERT(mTexture);

	const PxU32 componentCount = 4;

	if(mTexture)
	{
		PxU32 pitch = 0;
		void* buffer = mTexture->lockLevel(0, pitch);
		PX_ASSERT(buffer);
		if(buffer)
		{
			PxU8* levelDst			= (PxU8*)buffer;
			const PxU8* levelSrc	= (PxU8*)data;
			const PxU32 levelWidth	= mTexture->getWidthInBlocks();
			const PxU32 levelHeight	= mTexture->getHeightInBlocks();
			const PxU32 rowSrcSize	= levelWidth * mTexture->getBlockSize();
			PX_UNUSED(rowSrcSize);
			PX_ASSERT(rowSrcSize <= pitch); // the pitch can't be less than the source row size.
			for(PxU32 row=0; row<levelHeight; row++)
			{ 
				// copy per pixel to handle RBG case, based on component count
				for(PxU32 col=0; col<levelWidth; col++)
				{
					*levelDst++ = levelSrc[0];
					*levelDst++ = levelSrc[1];
					*levelDst++ = levelSrc[2];
					*levelDst++ = 0xFF; //alpha
					levelSrc += componentCount;
				}
			}
		}
		mTexture->unlockLevel(0);
	}
}

RenderTexture::RenderTexture(Renderer& renderer, PxU32 id, RendererTexture2D* texture) :
	mID				(id),
	mTexture		(texture),
	mOwnsTexture	(false)
{
}

RenderTexture::~RenderTexture()
{
	if(mOwnsTexture)
		SAFE_RELEASE(mTexture);
}
