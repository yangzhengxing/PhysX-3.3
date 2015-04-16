/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererInstanceBufferDesc.h>
#include "foundation/PxAssert.h"

using namespace SampleRenderer;

RendererInstanceBufferDesc::RendererInstanceBufferDesc(void)
{
	hint = RendererInstanceBuffer::HINT_STATIC;
	for(PxU32 i=0; i<RendererInstanceBuffer::NUM_SEMANTICS; i++)
	{
		semanticFormats[i] = RendererInstanceBuffer::NUM_FORMATS;
	}
	maxInstances = 0;
	canReadBack = false;
	registerInCUDA = false;
	interopContext = 0;
}

bool RendererInstanceBufferDesc::isValid(void) const
{
	bool ok = true;
	if(!maxInstances) ok = false;

	bool bValidTurbulence = ok;
	if(semanticFormats[RendererInstanceBuffer::SEMANTIC_POSITION] != RendererInstanceBuffer::FORMAT_FLOAT3) ok = false;
	if(semanticFormats[RendererInstanceBuffer::SEMANTIC_NORMALX]  != RendererInstanceBuffer::FORMAT_FLOAT3) ok = false;
	if(semanticFormats[RendererInstanceBuffer::SEMANTIC_NORMALY]  != RendererInstanceBuffer::FORMAT_FLOAT3) ok = false;
	if(semanticFormats[RendererInstanceBuffer::SEMANTIC_NORMALZ]  != RendererInstanceBuffer::FORMAT_FLOAT3) ok = false;

	if(semanticFormats[RendererInstanceBuffer::SEMANTIC_POSITION] != RendererInstanceBuffer::FORMAT_FLOAT3) bValidTurbulence = false;
	if(semanticFormats[RendererInstanceBuffer::SEMANTIC_VELOCITY_LIFE] != RendererInstanceBuffer::FORMAT_FLOAT4) bValidTurbulence = false;

	if((semanticFormats[RendererInstanceBuffer::SEMANTIC_UV_OFFSET]    != RendererInstanceBuffer::FORMAT_FLOAT2) &&
	   (semanticFormats[RendererInstanceBuffer::SEMANTIC_UV_OFFSET]    != RendererInstanceBuffer::NUM_FORMATS)) ok = false;
	if((semanticFormats[RendererInstanceBuffer::SEMANTIC_LOCAL_OFFSET] != RendererInstanceBuffer::FORMAT_FLOAT3) &&
	   (semanticFormats[RendererInstanceBuffer::SEMANTIC_LOCAL_OFFSET] != RendererInstanceBuffer::NUM_FORMATS)) ok = false;

	if(registerInCUDA && !interopContext)
		ok = false;

	PX_ASSERT(bValidTurbulence || ok);
	return bValidTurbulence || ok;
}
