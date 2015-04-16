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
// RendererTerrainShape : convenience class for generating a terrain mesh.
//
#ifndef RENDERER_TERRAIN_SHAPE_H
#define RENDERER_TERRAIN_SHAPE_H

#include <RendererShape.h>

namespace SampleRenderer
{

	class RendererVertexBuffer;
	class RendererIndexBuffer;

	class RendererTerrainShape : public RendererShape
	{
	public:
		RendererTerrainShape(Renderer &renderer, 
			PxVec3 *verts, PxU32 numVerts,
			PxVec3 *normals, PxU32 numNorms,
			PxU16 *faces, PxU32 numFaces,
			PxF32 uvScale);
		virtual ~RendererTerrainShape(void);

	private:
		RendererVertexBuffer *m_vertexBuffer;
		RendererIndexBuffer  *m_indexBuffer;
	};

} // namespace SampleRenderer

#endif
