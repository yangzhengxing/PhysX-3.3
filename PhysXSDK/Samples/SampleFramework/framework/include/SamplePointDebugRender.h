/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


#ifndef SAMPLE_POINT_DEBUG_RENDER_H
#define SAMPLE_POINT_DEBUG_RENDER_H

#include <RendererMeshContext.h>
#include <FrameworkFoundation.h>

namespace SampleRenderer
{
	class Renderer;
	class RendererColor;
	class RendererVertexBuffer;
}

namespace SampleFramework
{
	class SampleAssetManager;
	class SampleMaterialAsset;

	class SamplePointDebugRender
	{
	public:
		void addPoint(const PxVec3 &p0, const SampleRenderer::RendererColor &color);

		void queueForRenderPoint(void);

	protected:
		SamplePointDebugRender(SampleRenderer::Renderer &renderer, SampleAssetManager &assetmanager);
		virtual ~SamplePointDebugRender(void);

		void checkResizePoint(PxU32 maxVerts);
		void clearPoint(void);

	private:
		void checkLock(void);
		void checkUnlock(void);
		void addVert(const PxVec3 &p, const SampleRenderer::RendererColor &color);

		SamplePointDebugRender &operator=(const SamplePointDebugRender&) { return *this; }

		SampleRenderer::Renderer             &m_renderer;
		SampleAssetManager                   &m_assetmanager;

		SampleMaterialAsset                  *m_material;

		PxU32                                 m_maxVerts;
		PxU32                                 m_numVerts;
		SampleRenderer::RendererVertexBuffer *m_vertexbuffer;
		SampleRenderer::RendererMesh         *m_mesh;
		SampleRenderer::RendererMeshContext   m_meshContext;

		void                                 *m_lockedPositions;
		PxU32                                 m_positionStride;

		void                                 *m_lockedColors;
		PxU32                                 m_colorStride;
	};

} // namespace SampleFramework

#endif
