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

#if defined(RENDERER_ENABLE_OPENGL) 

#include "OGLRendererInstanceBuffer.h"
#include <RendererInstanceBufferDesc.h>

using namespace SampleRenderer;

OGLRendererInstanceBuffer::OGLRendererInstanceBuffer(const RendererInstanceBufferDesc &desc) :
	RendererInstanceBuffer(desc)
{
	m_bufferSize   = (PxU32)(desc.maxInstances * m_stride);
	m_buffer       = malloc(m_bufferSize);//PX_ALLOC(m_bufferSize);
	m_maxInstances = desc.maxInstances;
}

OGLRendererInstanceBuffer::~OGLRendererInstanceBuffer(void)
{
	if(m_buffer) free(m_buffer);//PX_FREE(m_buffer);
}

physx::PxMat44 OGLRendererInstanceBuffer::getModelMatrix(PxU32 index) const
{
	physx::PxMat44 model = PxMat44(PxIdentity);
	if(index < m_maxInstances)
	{
		const void *instance = ((PxU8*)m_buffer)+(m_stride*index);
		PxVec3 column0 = getInstanceColumn(instance, m_semanticDescs[SEMANTIC_NORMALX]);
		PxVec3 column1 = getInstanceColumn(instance, m_semanticDescs[SEMANTIC_NORMALY]);
		PxVec3 column2 = getInstanceColumn(instance, m_semanticDescs[SEMANTIC_NORMALZ]);
		PxVec3 column3 = getInstanceColumn(instance, m_semanticDescs[SEMANTIC_POSITION]);

		model = PxMat44(column0, column1, column2, column3);
	}
	return model;
}

PxVec3 OGLRendererInstanceBuffer::getInstanceColumn(const void *instance, const OGLRendererInstanceBuffer::SemanticDesc &sd) const
{
	PxVec3 col = *(PxVec3*)(((PxU8*)instance)+sd.offset);
	return col;
}

void *OGLRendererInstanceBuffer::lock(void)
{
	return m_buffer;
}

void OGLRendererInstanceBuffer::unlock(void)
{

}

void OGLRendererInstanceBuffer::bind(PxU32 streamID, PxU32 firstInstance) const
{

}

void OGLRendererInstanceBuffer::unbind(PxU32 streamID) const
{

}

#endif // #if defined(RENDERER_ENABLE_OPENGL) 
