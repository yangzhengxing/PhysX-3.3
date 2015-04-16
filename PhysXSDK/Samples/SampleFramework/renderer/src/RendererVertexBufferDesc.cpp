/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererVertexBufferDesc.h>

using namespace SampleRenderer;

RendererVertexBufferDesc::RendererVertexBufferDesc(void)
{
	hint = RendererVertexBuffer::HINT_STATIC;
	for(PxU32 i=0; i<RendererVertexBuffer::NUM_SEMANTICS; i++)
	{
		semanticFormats[i] = RendererVertexBuffer::NUM_FORMATS;
	}
	maxVertices = 0;
	canReadBack = false;
	registerInCUDA = false;
	interopContext = 0;
}

bool RendererVertexBufferDesc::isValid(void) const
{
	bool ok = true;
	// TODO: make sure at least "some" of the semanticFormats are set.
	if(!maxVertices) ok = false;
	if(registerInCUDA && !interopContext)
		ok = false;
	return ok;
}
