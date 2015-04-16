/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef D3D9_RENDERER_MESH_H
#define D3D9_RENDERER_MESH_H

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_DIRECT3D9)

#include <RendererMesh.h>
#include "D3D9Renderer.h"

namespace SampleRenderer
{

	class D3D9RendererMesh : public RendererMesh
	{
	public:
		D3D9RendererMesh(D3D9Renderer &renderer, const RendererMeshDesc &desc);
		virtual ~D3D9RendererMesh(void);

	public:
		virtual void renderIndices(PxU32 numVertices, PxU32 firstIndex, PxU32 numIndices, RendererIndexBuffer::Format indexFormat,RendererMaterial *material) const;
		virtual void renderVertices(PxU32 numVertices,RendererMaterial *material) const;

		virtual void renderIndicesInstanced(PxU32 numVertices, PxU32 firstIndex, PxU32 numIndices, RendererIndexBuffer::Format indexFormat,RendererMaterial *material) const;
		virtual void renderVerticesInstanced(PxU32 numVertices,RendererMaterial *material) const;

	protected:
		D3D9RendererMesh &operator=(const D3D9RendererMesh &) { return *this; }

		Renderer& renderer() { return m_renderer; }

	private:
		D3D9Renderer                &m_renderer;
		IDirect3DVertexDeclaration9 *m_d3dVertexDecl;
	};

} // namespace SampleRenderer

#endif // #if defined(RENDERER_ENABLE_DIRECT3D9)
#endif
