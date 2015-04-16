/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  

#ifndef RENDER_MESH_ACTOR_H
#define RENDER_MESH_ACTOR_H

#include "RenderBaseActor.h"
#include "foundation/PxVec3.h"

namespace SampleRenderer
{
	class Renderer;
}

	class RenderMeshActor : public RenderBaseActor
	{
		public:
					RenderMeshActor(SampleRenderer::Renderer& renderer,
								const PxVec3* verts, PxU32 numVerts,
								const PxVec3* vertexNormals,
								const PxReal* uvs,
								const PxU16* faces16, const PxU32* faces32, PxU32 numFaces, bool flipWinding=false
								);
					RenderMeshActor(const RenderMeshActor&);
		virtual		~RenderMeshActor();
	};

#endif
