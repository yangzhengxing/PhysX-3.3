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


#include "NULLRendererIndexBuffer.h"
#include <RendererIndexBufferDesc.h>

using namespace SampleRenderer;

NullRendererIndexBuffer::NullRendererIndexBuffer(const RendererIndexBufferDesc &desc) :
	RendererIndexBuffer(desc), m_Buffer(0)
{
	PxU32 indexSize  = getFormatByteSize(getFormat());
	
	RENDERER_ASSERT(desc.maxIndices > 0 && desc.maxIndices > 0, "Cannot create zero size Index Buffer.");
	if(indexSize && desc.maxIndices > 0)
	{
		m_Buffer = new PxU8[indexSize*desc.maxIndices];
		m_maxIndices = desc.maxIndices;
	}

}

NullRendererIndexBuffer::~NullRendererIndexBuffer(void)
{
	if(m_Buffer)
	{
		delete [] m_Buffer;
		m_Buffer = NULL;
	}
}

void *NullRendererIndexBuffer::lock(void)
{	
	return m_Buffer;
}

void NullRendererIndexBuffer::unlock(void)
{
}

void NullRendererIndexBuffer::bind(void) const
{
}

void NullRendererIndexBuffer::unbind(void) const
{
}
