/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef NULL_RENDERER_MESH_H
#define NULL_RENDERER_MESH_H

#include <RendererConfig.h>
#include <RendererMesh.h>
#include "NULLRenderer.h"

namespace SampleRenderer
{

	class NullRendererMesh : public RendererMesh
	{
	public:
		NullRendererMesh(NullRenderer &renderer, const RendererMeshDesc &desc);
		virtual ~NullRendererMesh(void);

		virtual bool willRender() const;

	public:
		virtual void renderIndices(PxU32 numVertices, PxU32 firstIndex, PxU32 numIndices, RendererIndexBuffer::Format indexFormat, RendererMaterial *material) const;
		virtual void renderVertices(PxU32 numVertices, RendererMaterial *material) const;

		virtual void renderIndicesInstanced(PxU32 numVertices, PxU32 firstIndex, PxU32 numIndices, RendererIndexBuffer::Format indexFormat,RendererMaterial *material) const;
		virtual void renderVerticesInstanced(PxU32 numVertices,RendererMaterial *material) const;

	protected:
		void operator=(const NullRendererMesh &){}
		Renderer& renderer() { return mRenderer; }

	private:
		NullRenderer&		mRenderer;
	};

} // namespace SampleRenderer

#endif
