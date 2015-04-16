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

#if defined(RENDERER_ENABLE_GLES2) 

#include "GLES2RendererInstanceBuffer.h"
#include <RendererInstanceBufferDesc.h>

using namespace SampleRenderer;

GLES2RendererInstanceBuffer::GLES2RendererInstanceBuffer(const RendererInstanceBufferDesc &desc) :
	RendererInstanceBuffer(desc)
{
	m_bufferSize   = (PxU32)(desc.maxInstances * m_stride);
	m_buffer       = malloc(m_bufferSize);//PX_ALLOC(m_bufferSize);
	m_maxInstances = desc.maxInstances;
}

GLES2RendererInstanceBuffer::~GLES2RendererInstanceBuffer(void)
{
	if(m_buffer) free(m_buffer);//PX_FREE(m_buffer);
}

physx::PxMat44 GLES2RendererInstanceBuffer::getModelMatrix(PxU32 index) const
{
	physx::PxMat44 model = PxMat44::createIdentity();
	if(index < m_maxInstances)
	{
		const void *instance = ((PxU8*)m_buffer)+(m_stride*index);
		model = PxMat44(getInstanceColumn(instance, m_semanticDescs[SEMANTIC_NORMALX]),
						getInstanceColumn(instance, m_semanticDescs[SEMANTIC_NORMALY]),
						getInstanceColumn(instance, m_semanticDescs[SEMANTIC_NORMALZ]),
						getInstanceColumn(instance, m_semanticDescs[SEMANTIC_POSITION]));
	}
	return model;
}

PxVec3 GLES2RendererInstanceBuffer::getInstanceColumn(const void *instance, const GLES2RendererInstanceBuffer::SemanticDesc &sd) const
{
	PxVec3 col = *(PxVec3*)(((PxU8*)instance)+sd.offset);
	return col;
}

void *GLES2RendererInstanceBuffer::lock(void)
{
	return m_buffer;
}

void GLES2RendererInstanceBuffer::unlock(void)
{

}

void GLES2RendererInstanceBuffer::bind(PxU32 streamID, PxU32 firstInstance) const
{

}

void GLES2RendererInstanceBuffer::unbind(PxU32 streamID) const
{

}

#endif // #if defined(RENDERER_ENABLE_GLES2) 
