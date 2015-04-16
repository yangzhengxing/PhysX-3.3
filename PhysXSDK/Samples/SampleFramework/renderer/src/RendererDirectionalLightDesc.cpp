/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererDirectionalLightDesc.h>

using namespace SampleRenderer;

RendererDirectionalLightDesc::RendererDirectionalLightDesc(void) :
RendererLightDesc(RendererLight::TYPE_DIRECTIONAL)
{
	direction = PxVec3(0,0,0);
}

bool RendererDirectionalLightDesc::isValid(void) const
{
	bool ok = RendererLightDesc::isValid();
	if(direction.magnitudeSquared() < 0.1f) ok = false;
	return ok;
}
