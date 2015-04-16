/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


#ifndef SAMPLE_TRIANGLE_DEBUG_RENDER_H
#define SAMPLE_TRIANGLE_DEBUG_RENDER_H

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

	class SampleTriangleDebugRender
	{
	public:
		void addTriangle(const PxVec3 &p0, const PxVec3 &p1, const PxVec3 &p2, const SampleRenderer::RendererColor &color);
		void addTriangle(const PxVec3 &p0, const PxVec3 &p1, const PxVec3 &p2, const PxVec3& n0, const PxVec3& n1, const PxVec3& n2, const SampleRenderer::RendererColor &color);

		void queueForRenderTriangle(void);

	protected:
		SampleTriangleDebugRender(SampleRenderer::Renderer &renderer, SampleAssetManager &assetmanager);
		virtual ~SampleTriangleDebugRender(void);

		void checkResizeTriangle(PxU32 maxVerts);
		void clearTriangle(void);

	private:
		void checkLock(void);
		void checkUnlock(void);
		void addVert(const PxVec3 &p, const PxVec3 &n, const SampleRenderer::RendererColor &color);

	private:
		SampleTriangleDebugRender &operator=(const SampleTriangleDebugRender&) { return *this; }

	private:
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

		void                                 *m_lockedNormals;
		PxU32                                 m_normalStride;

		void                                 *m_lockedColors;
		PxU32                                 m_colorStride;
	};

} // namespace SampleFramework

#endif
