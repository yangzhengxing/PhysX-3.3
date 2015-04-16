/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#include <RendererConfig.h>

#include "NULLRendererTexture2D.h"
#include <RendererTexture2DDesc.h>

using namespace SampleRenderer;

NullRendererTexture2D::NullRendererTexture2D(const RendererTexture2DDesc &desc) :
RendererTexture2D(desc)
{	
	PxU32 width     = desc.width;
	PxU32 height    = desc.height;
	
	m_numLevels = desc.numLevels;
	m_data = new PxU8*[m_numLevels];
	m_width = new PxU32[m_numLevels];
	memset(m_data, 0, sizeof(PxU8*)*m_numLevels);
	
	for(PxU32 i=0; i<desc.numLevels; i++)
	{
		PxU32 w = getLevelDimension(width,  i);
		m_width[i] = w;
		PxU32 h = getLevelDimension(height, i);
		PxU32 levelSize = computeImageByteSize(w, h, 1, desc.format);		

		// allocate memory
		m_data[i] = new PxU8[levelSize];

		memset(m_data[i], 0, levelSize);
	}
}

NullRendererTexture2D::~NullRendererTexture2D(void)
{
	for(PxU32 i=0; i<m_numLevels; i++)
	{
		delete [] m_data[i];
	}

	if(m_data)
	{
		delete [] m_data;
	}

	if(m_width)
	{
		delete [] m_width;
	}
}

void *NullRendererTexture2D::lockLevel(PxU32 level, PxU32 &pitch)
{
	void *buffer = 0;
	pitch = 0;
	RENDERER_ASSERT(level < m_numLevels, "Level out of range!");
	if(level < m_numLevels)
	{
		buffer = m_data[level];
		PxU32 w = SampleRenderer::RendererTexture2D::getFormatNumBlocks(m_width[level],  getFormat());
		pitch = w * getBlockSize();
	}	
	return buffer;
}

void NullRendererTexture2D::unlockLevel(PxU32 level)
{
	RENDERER_ASSERT(level < m_numLevels, "Level out of range!");
}

void NullRendererTexture2D::bind(PxU32 textureUnit)
{
}

