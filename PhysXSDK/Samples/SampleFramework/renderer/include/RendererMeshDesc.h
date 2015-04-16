/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_MESH_DESC_H
#define RENDERER_MESH_DESC_H

#include <RendererMesh.h>

namespace SampleRenderer
{

	class RendererVertexBuffer;
	class RendererIndexBuffer;
	class RendererInstanceBuffer;

	class RendererMeshDesc
	{
	public:
		RendererMesh::Primitive primitives;

		RendererVertexBuffer  **vertexBuffers;
		PxU32                   numVertexBuffers;
		PxU32                   firstVertex;
		PxU32                   numVertices;

		RendererIndexBuffer    *indexBuffer;
		PxU32                   firstIndex;
		PxU32                   numIndices;

		RendererInstanceBuffer *instanceBuffer;
		PxU32                   firstInstance;
		PxU32                   numInstances;

	public:
		RendererMeshDesc(void);

		bool isValid(void) const;
	};

} // namespace SampleRenderer

#endif
