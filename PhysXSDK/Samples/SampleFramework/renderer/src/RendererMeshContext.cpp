/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererMeshContext.h>

using namespace SampleRenderer;

RendererMeshContext::RendererMeshContext(void)
{
	mesh             = 0;
	material         = 0;
	materialInstance = 0;
	transform        = 0;
	shaderData       = 0;
	boneMatrices     = 0;
	numBones         = 0;
	cullMode         = CLOCKWISE;
	screenSpace      = false;
	fillMode         = SOLID;
}

RendererMeshContext::~RendererMeshContext(void)
{
}

bool RendererMeshContext::isValid(void) const
{
	bool ok = true;
	if(!mesh)     ok = false;
	if(!material) ok = false;
	return ok;
}
