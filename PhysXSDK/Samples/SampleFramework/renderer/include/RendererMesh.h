/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_MESH_H
#define RENDERER_MESH_H

#include <RendererConfig.h>
#include <RendererIndexBuffer.h>

namespace SampleRenderer
{
	class Renderer;
	class RendererMeshDesc;
	class RendererVertexBuffer;
	class RendererIndexBuffer;
	class RendererInstanceBuffer;
	class RendererMaterial;

	class RendererMesh
	{
		friend class Renderer;
		friend class GLES2Renderer;
	public:
		enum Primitive
		{
			PRIMITIVE_POINTS = 0,
			PRIMITIVE_LINES,
			PRIMITIVE_LINE_STRIP,
			PRIMITIVE_TRIANGLES,
			PRIMITIVE_TRIANGLE_STRIP,
			PRIMITIVE_POINT_SPRITES,

			NUM_PRIMITIVES
		}_Primitive;

	protected:
		RendererMesh(const RendererMeshDesc &desc);
		virtual ~RendererMesh(void);

	public:
		void release(void);

		Primitive getPrimitives(void) const;

		PxU32 getNumVertices(void) const;
		PxU32 getNumIndices(void) const;
		PxU32 getNumInstances(void) const;

		void setVertexBufferRange(PxU32 firstVertex, PxU32 numVertices);
		void setIndexBufferRange(PxU32 firstIndex, PxU32 numIndices);
		void setInstanceBufferRange(PxU32 firstInstance, PxU32 numInstances);

		PxU32                             getNumVertexBuffers(void) const;
		const RendererVertexBuffer *const*getVertexBuffers(void) const;

		const RendererIndexBuffer        *getIndexBuffer(void) const;

		const RendererInstanceBuffer     *getInstanceBuffer(void) const;

		virtual bool willRender() const { return true; }

	protected:
		void         bind(void) const;
		void         render(RendererMaterial *material) const;
		void         unbind(void) const;

		virtual void renderIndices(PxU32 numVertices, PxU32 firstIndex, PxU32 numIndices, RendererIndexBuffer::Format indexFormat, RendererMaterial *material) const = 0;
		virtual void renderVertices(PxU32 numVertices, RendererMaterial *material) const = 0;

		virtual void renderIndicesInstanced(PxU32 numVertices, PxU32 firstIndex, PxU32 numIndices, RendererIndexBuffer::Format indexFormat,RendererMaterial *material) const = 0;
		virtual void renderVerticesInstanced(PxU32 numVertices,RendererMaterial *material) const = 0;

		virtual Renderer& renderer() = 0;

	protected:
		Primitive               m_primitives;

		RendererVertexBuffer  **m_vertexBuffers;
		PxU32                   m_numVertexBuffers;
		PxU32                   m_firstVertex;
		PxU32                   m_numVertices;

		RendererIndexBuffer    *m_indexBuffer;
		PxU32                   m_firstIndex;
		PxU32                   m_numIndices;

		RendererInstanceBuffer *m_instanceBuffer;
		PxU32                   m_firstInstance;
		PxU32                   m_numInstances;
	};

} // namespace SampleRenderer

#endif
