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

#include "NULLRendererInstanceBuffer.h"
#include <RendererInstanceBufferDesc.h>

using namespace SampleRenderer;

NullRendererInstanceBuffer::NullRendererInstanceBuffer(const RendererInstanceBufferDesc &desc) :
	RendererInstanceBuffer(desc)
{	
	m_bufferSize   = (PxU32)(desc.maxInstances * m_stride);
	m_buffer       = new PxU8[m_bufferSize];

	RENDERER_ASSERT(m_buffer, "Failed to create Vertex Buffer Object.");
		
	m_maxInstances = desc.maxInstances;
}

NullRendererInstanceBuffer::~NullRendererInstanceBuffer(void)
{
	if(m_buffer)
	{
		delete [] m_buffer;
		m_buffer = NULL;
	}
}


void *NullRendererInstanceBuffer::lock(void)
{
	return m_buffer;
}

void NullRendererInstanceBuffer::unlock(void)
{

}

void NullRendererInstanceBuffer::bind(PxU32 streamID, PxU32 firstInstance) const
{
}

void NullRendererInstanceBuffer::unbind(PxU32 streamID) const
{

}

