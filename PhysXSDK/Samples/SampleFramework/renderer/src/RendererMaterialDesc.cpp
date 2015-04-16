/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererMaterialDesc.h>

using namespace SampleRenderer;

RendererMaterialDesc::RendererMaterialDesc(void)
{
	type               = RendererMaterial::TYPE_UNLIT;
	alphaTestFunc      = RendererMaterial::ALPHA_TEST_ALWAYS;
	alphaTestRef       = 0;
	blending           = false;
	instanced		   = false;
	srcBlendFunc       = RendererMaterial::BLEND_ZERO;
	dstBlendFunc       = RendererMaterial::BLEND_ZERO;
	geometryShaderPath = 0;
	hullShaderPath     = 0;
	domainShaderPath   = 0;
	vertexShaderPath   = 0;
	fragmentShaderPath = 0;
}

bool RendererMaterialDesc::isValid(void) const
{
	bool ok = true;
	if(type >= RendererMaterial::NUM_TYPES) ok = false;
	if(alphaTestRef < 0 || alphaTestRef > 1) ok = false;
	// Note: Lighting and blending may not be properly supported, but that 
	//    shouldn't crash the system, so this check is disabled for now
	// if(blending && type != RendererMaterial::TYPE_UNLIT) ok = false;
	if(geometryShaderPath || domainShaderPath || fragmentShaderPath)
	{
		// Note: These should be completely optional! Disabling for now.
		//RENDERER_ASSERT(0, "Not implemented!");
		//ok = false;
	}
	if(!vertexShaderPath)   ok = false;
	if(!fragmentShaderPath) ok = false;
	return ok;
}
