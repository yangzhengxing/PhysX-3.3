/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#include <RendererConfig.h>

#include "NULLRendererMesh.h"

using namespace SampleRenderer;


NullRendererMesh::NullRendererMesh(NullRenderer &renderer, const RendererMeshDesc &desc) :	
RendererMesh(desc),
mRenderer(renderer)
{
}

NullRendererMesh::~NullRendererMesh(void)
{

	

}

void NullRendererMesh::renderIndices(PxU32 numVertices, PxU32 firstIndex, PxU32 numIndices, RendererIndexBuffer::Format indexFormat, RendererMaterial *material) const
{

}

bool NullRendererMesh::willRender() const
{
	return true;

}

void NullRendererMesh::renderVertices(PxU32 numVertices, RendererMaterial *material) const
{

}

void NullRendererMesh::renderIndicesInstanced(PxU32 numVertices, PxU32 firstIndex, PxU32 numIndices, RendererIndexBuffer::Format indexFormat,RendererMaterial *material) const
{
}

void NullRendererMesh::renderVerticesInstanced(PxU32 numVertices,RendererMaterial *material) const
{
}

		
