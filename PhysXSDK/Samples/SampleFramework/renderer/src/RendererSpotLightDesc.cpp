/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererSpotLightDesc.h>

using namespace SampleRenderer;

RendererSpotLightDesc::RendererSpotLightDesc(void) :
	RendererLightDesc(RendererLight::TYPE_SPOT)
{
	position = PxVec3(0,0,0);
	direction = PxVec3(0,0,0);
	innerRadius = 0;
	outerRadius = 0;
	innerCone   = 0;
	outerCone   = 0;
}

bool RendererSpotLightDesc::isValid(void) const
{
	bool ok = RendererLightDesc::isValid();
	if(direction.magnitudeSquared() < 0.1f) ok = false;
	if(innerRadius < 0)                     ok = false;
	if(outerRadius < innerRadius)           ok = false;
	if(innerCone > 1)                       ok = false;
	if(outerCone > innerCone)               ok = false;
	return ok;
}
