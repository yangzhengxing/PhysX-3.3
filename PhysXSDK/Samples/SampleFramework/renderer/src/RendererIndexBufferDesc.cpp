/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererIndexBufferDesc.h>

using namespace SampleRenderer;

RendererIndexBufferDesc::RendererIndexBufferDesc(void)
{
	hint       = RendererIndexBuffer::HINT_STATIC;
	format     = RendererIndexBuffer::NUM_FORMATS;
	maxIndices = 0;
	canReadBack = false;
	registerInCUDA = false;
	interopContext = 0;
}

bool RendererIndexBufferDesc::isValid(void) const
{
	bool ok = true;
	if(format >= RendererIndexBuffer::NUM_FORMATS) ok = false;
	if(maxIndices == 0) ok = false;
	if(registerInCUDA && !interopContext)
		ok = false;
	return ok;
}
