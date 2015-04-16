/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererIndexBuffer.h>
#include <RendererIndexBufferDesc.h>

using namespace SampleRenderer;

PxU32 RendererIndexBuffer::getFormatByteSize(Format format)
{
	PxU32 size = 0;
	switch(format)
	{
	case FORMAT_UINT16: size = sizeof(PxU16); break;
	case FORMAT_UINT32: size = sizeof(PxU32); break;
	default: break;
	}
	RENDERER_ASSERT(size, "Unable to determine size of format.");
	return size;
}

RendererIndexBuffer::RendererIndexBuffer(const RendererIndexBufferDesc &desc) :
RendererInteropableBuffer(desc.registerInCUDA, desc.interopContext),
	m_hint(desc.hint),
	m_format(desc.format)
{
	m_maxIndices = 0;
}

RendererIndexBuffer::~RendererIndexBuffer(void)
{

}

RendererIndexBuffer::Hint RendererIndexBuffer::getHint(void) const
{
	return m_hint;
}

RendererIndexBuffer::Format RendererIndexBuffer::getFormat(void) const
{
	return m_format;
}

PxU32 RendererIndexBuffer::getMaxIndices(void) const
{
	return m_maxIndices;
}
