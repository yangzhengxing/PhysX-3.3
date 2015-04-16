/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#include "RendererConfig.h"
#include <SamplePlatform.h>

#include "NULLRendererVertexBuffer.h"

#include <RendererVertexBufferDesc.h>


using namespace SampleRenderer;

NullRendererVertexBuffer::NullRendererVertexBuffer(const RendererVertexBufferDesc &desc) 
	:RendererVertexBuffer(desc),m_buffer(0)
{			
	RENDERER_ASSERT(m_stride && desc.maxVertices, "Unable to create Vertex Buffer of zero size.");
	if(m_stride && desc.maxVertices)
	{		
		m_buffer = new PxU8[m_stride * desc.maxVertices];
		
		RENDERER_ASSERT(m_buffer, "Failed to create Vertex Buffer Object.");

		m_maxVertices = desc.maxVertices;
	}
}

NullRendererVertexBuffer::~NullRendererVertexBuffer(void)
{
	if(m_buffer)
	{
		delete [] m_buffer;
		m_buffer = NULL;
	}
}

void NullRendererVertexBuffer::swizzleColor(void *colors, PxU32 stride, PxU32 numColors, RendererVertexBuffer::Format inFormat)
{
}

void *NullRendererVertexBuffer::lock(void)
{	
	return m_buffer;
}

void NullRendererVertexBuffer::unlock(void)
{
}


void NullRendererVertexBuffer::bind(PxU32 streamID, PxU32 firstVertex)
{
}

void NullRendererVertexBuffer::unbind(PxU32 streamID)
{
}

