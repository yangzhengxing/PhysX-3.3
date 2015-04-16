/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererMesh.h>
#include <RendererMeshDesc.h>

#include <Renderer.h>
#include <RendererVertexBuffer.h>
#include <RendererIndexBuffer.h>
#include <RendererInstanceBuffer.h>


using namespace SampleRenderer;

RendererMesh::RendererMesh(const RendererMeshDesc &desc)
{
	m_primitives = desc.primitives;

	m_numVertexBuffers = desc.numVertexBuffers;
	m_vertexBuffers = new RendererVertexBuffer*[m_numVertexBuffers];
	for(PxU32 i=0; i<m_numVertexBuffers; i++)
	{
		m_vertexBuffers[i] = desc.vertexBuffers[i];
	}
	m_firstVertex    = desc.firstVertex;
	m_numVertices    = desc.numVertices;

	m_indexBuffer    = desc.indexBuffer;
	m_firstIndex     = desc.firstIndex;
	m_numIndices     = desc.numIndices;

	m_instanceBuffer = desc.instanceBuffer;
	m_firstInstance  = desc.firstInstance;
	m_numInstances   = desc.numInstances;
}

RendererMesh::~RendererMesh(void)
{
	delete [] m_vertexBuffers;
}

void SampleRenderer::RendererMesh::release(void)
{
	renderer().removeMeshFromRenderQueue(*this);
	delete this;
}

RendererMesh::Primitive RendererMesh::getPrimitives(void) const
{
	return m_primitives;
}

PxU32 RendererMesh::getNumVertices(void) const
{
	return m_numVertices;
}

PxU32 RendererMesh::getNumIndices(void) const
{
	return m_numIndices;
}

PxU32 RendererMesh::getNumInstances(void) const
{
	return m_numInstances;
}

void RendererMesh::setVertexBufferRange(PxU32 firstVertex, PxU32 numVertices)
{
	// TODO: Check for valid range...
	m_firstVertex = firstVertex;
	m_numVertices = numVertices;
}

void RendererMesh::setIndexBufferRange(PxU32 firstIndex, PxU32 numIndices)
{
	// TODO: Check for valid range...
	m_firstIndex = firstIndex;
	m_numIndices = numIndices;
}

void RendererMesh::setInstanceBufferRange(PxU32 firstInstance, PxU32 numInstances)
{
	// TODO: Check for valid range...
	m_firstInstance = firstInstance;
	m_numInstances  = numInstances;
}

PxU32 RendererMesh::getNumVertexBuffers(void) const
{
	return m_numVertexBuffers;
}

const RendererVertexBuffer *const*RendererMesh::getVertexBuffers(void) const
{
	return m_vertexBuffers;
}

const RendererIndexBuffer *RendererMesh::getIndexBuffer(void) const
{
	return m_indexBuffer;
}

const RendererInstanceBuffer *RendererMesh::getInstanceBuffer(void) const
{
	return m_instanceBuffer;
}

void RendererMesh::bind(void) const
{
	for(PxU32 i=0; i<m_numVertexBuffers; i++)
	{
		//RENDERER_ASSERT(m_vertexBuffers[i]->checkBufferWritten(), "Vertex buffer is empty!");
		if (m_vertexBuffers[i]->checkBufferWritten())
		{
			m_vertexBuffers[i]->bind(i, m_firstVertex);
		}
	}
	if(m_instanceBuffer)
	{
		m_instanceBuffer->bind(m_numVertexBuffers, m_firstInstance);
	}
	if(m_indexBuffer)
	{
		m_indexBuffer->bind();
	}
}

void RendererMesh::render(RendererMaterial *material) const
{
	if(m_instanceBuffer)
	{
		if(m_indexBuffer)
		{
			renderIndicesInstanced(m_numVertices, m_firstIndex, m_numIndices, m_indexBuffer->getFormat(), material);
		}
		else if(m_numVertices)
		{
			renderVerticesInstanced(m_numVertices, material);
		}
	}
	else
	{
		if(m_indexBuffer)
		{
			renderIndices(m_numVertices, m_firstIndex, m_numIndices, m_indexBuffer->getFormat(), material);
		}
		else if(m_numVertices)
		{
			renderVertices(m_numVertices, material);
		}
	}
}

void RendererMesh::unbind(void) const
{
	if(m_indexBuffer)
	{
		m_indexBuffer->unbind();
	}
	if(m_instanceBuffer)
	{
		m_instanceBuffer->unbind(m_numVertexBuffers);
	}
	for(PxU32 i=0; i<m_numVertexBuffers; i++)
	{
		m_vertexBuffers[i]->unbind(i);
	}
}

