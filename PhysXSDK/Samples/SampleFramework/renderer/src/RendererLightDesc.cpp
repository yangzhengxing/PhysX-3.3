/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererLightDesc.h>

using namespace SampleRenderer;

RendererLightDesc::RendererLightDesc(RendererLight::Type _type) :
type(_type),
shadowProjection(45, 1, 0.1f, 100.0f)
{
	color       = RendererColor(0,0,0,0);
	intensity   = 0;
	shadowMap   = 0;
	shadowTransform = physx::PxTransform(PxIdentity);
}

bool RendererLightDesc::isValid(void) const
{
	bool ok = true;
	if(intensity < 0) ok = false;
	return ok;
}
