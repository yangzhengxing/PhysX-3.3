/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
//
// RendererTerrainShape : convenience class for generating a box mesh.
//
#include <RendererTerrainShape.h>

#include <Renderer.h>

#include <RendererVertexBuffer.h>
#include <RendererVertexBufferDesc.h>

#include <RendererIndexBuffer.h>
#include <RendererIndexBufferDesc.h>

#include <RendererMesh.h>
#include <RendererMeshDesc.h>

#include <RendererMemoryMacros.h>

using namespace SampleRenderer;

RendererTerrainShape::RendererTerrainShape(Renderer &renderer, 
	PxVec3 *verts, PxU32 numVerts, 
	PxVec3 *normals, PxU32 numNorms,
	PxU16 *faces, PxU32 numFaces,
	PxF32 uvScale) :
RendererShape(renderer)
{
	RendererVertexBufferDesc vbdesc;
	vbdesc.hint = RendererVertexBuffer::HINT_STATIC;
	vbdesc.semanticFormats[RendererVertexBuffer::SEMANTIC_POSITION]  = RendererVertexBuffer::FORMAT_FLOAT3;
	vbdesc.semanticFormats[RendererVertexBuffer::SEMANTIC_NORMAL]    = RendererVertexBuffer::FORMAT_FLOAT3;
	vbdesc.semanticFormats[RendererVertexBuffer::SEMANTIC_TEXCOORD0] = RendererVertexBuffer::FORMAT_FLOAT2;
	vbdesc.maxVertices = numVerts;
	m_vertexBuffer = m_renderer.createVertexBuffer(vbdesc);
	RENDERER_ASSERT(m_vertexBuffer, "Failed to create Vertex Buffer.");
	if(m_vertexBuffer)
	{
		PxU32 positionStride = 0;
		void *vertPositions = m_vertexBuffer->lockSemantic(RendererVertexBuffer::SEMANTIC_POSITION, positionStride);
		PxU32 normalStride = 0;
		void *vertNormals = m_vertexBuffer->lockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL, normalStride);
		PxU32 uvStride = 0;
		void *vertUVs = m_vertexBuffer->lockSemantic(RendererVertexBuffer::SEMANTIC_TEXCOORD0, uvStride);
		if(vertPositions && vertNormals)
		{
			for(PxU32 i=0; i<numVerts; i++)
			{
				memcpy(vertPositions, verts+i, sizeof(PxVec3));
				memcpy(vertNormals, normals+i, sizeof(PxVec3));
				((PxF32*)vertUVs)[0] = verts[i].x * uvScale;
				((PxF32*)vertUVs)[1] = verts[i].z * uvScale;

				vertPositions = (void*)(((PxU8*)vertPositions) + positionStride);
				vertNormals   = (void*)(((PxU8*)vertNormals)   + normalStride);
				vertUVs       = (void*)(((PxU8*)vertUVs)       + uvStride);
			}
		}
		m_vertexBuffer->unlockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL);
		m_vertexBuffer->unlockSemantic(RendererVertexBuffer::SEMANTIC_POSITION);
		m_vertexBuffer->unlockSemantic(RendererVertexBuffer::SEMANTIC_TEXCOORD0);
	}

	PxU32 numIndices = numFaces*3;

	RendererIndexBufferDesc ibdesc;
	ibdesc.hint       = RendererIndexBuffer::HINT_STATIC;
	ibdesc.format     = RendererIndexBuffer::FORMAT_UINT16;
	ibdesc.maxIndices = numIndices;
	m_indexBuffer = m_renderer.createIndexBuffer(ibdesc);
	RENDERER_ASSERT(m_indexBuffer, "Failed to create Index Buffer.");
	if(m_indexBuffer)
	{
		PxU16 *indices = (PxU16*)m_indexBuffer->lock();
		if(indices)
		{
			memcpy(indices, faces, sizeof(*faces)*numFaces*3);
		}
		m_indexBuffer->unlock();
	}

	if(m_vertexBuffer && m_indexBuffer)
	{
		RendererMeshDesc meshdesc;
		meshdesc.primitives       = RendererMesh::PRIMITIVE_TRIANGLES;
		meshdesc.vertexBuffers    = &m_vertexBuffer;
		meshdesc.numVertexBuffers = 1;
		meshdesc.firstVertex      = 0;
		meshdesc.numVertices      = numVerts;
		meshdesc.indexBuffer      = m_indexBuffer;
		meshdesc.firstIndex       = 0;
		meshdesc.numIndices       = numIndices;
		m_mesh = m_renderer.createMesh(meshdesc);
		RENDERER_ASSERT(m_mesh, "Failed to create Mesh.");
	}
}

RendererTerrainShape::~RendererTerrainShape(void)
{
	SAFE_RELEASE(m_vertexBuffer);
	SAFE_RELEASE(m_indexBuffer);
	SAFE_RELEASE(m_mesh);
}
