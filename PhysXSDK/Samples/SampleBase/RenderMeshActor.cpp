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

#include "RenderMeshActor.h"
#include "RendererMeshShape.h"
#include "RendererMemoryMacros.h"
#include "extensions/PxSmoothNormals.h"
#include "SampleAllocatorSDKClasses.h"

using namespace physx;
using namespace SampleRenderer;

RenderMeshActor::RenderMeshActor(	Renderer& renderer,
									const PxVec3* verts, PxU32 numVerts,
									const PxVec3* vertexNormals,
									const PxReal* uvs,
									const PxU16* faces16, const PxU32* faces32, PxU32 numFaces, bool flipWinding
								 )
{
	PxVec3Alloc* normals = NULL;
	if(!vertexNormals)
	{
		normals = SAMPLE_NEW(PxVec3Alloc)[numVerts];
		PxBuildSmoothNormals(numFaces, numVerts, verts, faces32, faces16, normals, flipWinding);
		vertexNormals = normals;
	}

	RendererShape* rs = new RendererMeshShape(renderer, verts, numVerts, vertexNormals, uvs, faces16, faces32, numFaces, flipWinding);
	setRenderShape(rs);

	DELETEARRAY(normals);
}

RenderMeshActor::RenderMeshActor(const RenderMeshActor& src) : RenderBaseActor(src)
{
}

RenderMeshActor::~RenderMeshActor()
{
}
