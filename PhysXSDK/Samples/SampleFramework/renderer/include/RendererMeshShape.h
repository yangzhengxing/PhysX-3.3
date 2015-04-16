/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_MESH_SHAPE_H
#define RENDERER_MESH_SHAPE_H

#include <RendererShape.h>

namespace SampleRenderer
{

	class RendererVertexBuffer;
	class RendererIndexBuffer;

	class RendererMeshShape : public RendererShape
	{
	public:
		RendererMeshShape(Renderer& renderer, 
			const PxVec3* verts, PxU32 numVerts,
			const PxVec3* normals,
			const PxReal* uvs,
			const PxU16* faces16, const PxU32* faces32, PxU32 numFaces, bool flipWinding=false);
		virtual ~RendererMeshShape();

	private:
		RendererVertexBuffer*	m_vertexBuffer;
		RendererIndexBuffer*	m_indexBuffer;
	};

} // namespace SampleRenderer

#endif
