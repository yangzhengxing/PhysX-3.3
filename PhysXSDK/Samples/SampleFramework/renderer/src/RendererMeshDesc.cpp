/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererMeshDesc.h>

using namespace SampleRenderer;

RendererMeshDesc::RendererMeshDesc(void)
{
	primitives = RendererMesh::PRIMITIVE_POINTS;

	vertexBuffers    = 0;
	numVertexBuffers = 0;
	firstVertex      = 0;
	numVertices      = 0;

	indexBuffer = 0;
	firstIndex  = 0;
	numIndices  = 0;

	instanceBuffer = 0;
	firstInstance  = 0;
	numInstances   = 0;
}

bool RendererMeshDesc::isValid(void) const
{
	bool ok = true;
	// remove vertexBuffer check for sprites
	/* if(!vertexBuffers || !numVertexBuffers) ok = false; */
	if(numIndices     && !indexBuffer)      ok = false;
	if(numInstances   && !instanceBuffer)   ok = false;
	return ok;
}
