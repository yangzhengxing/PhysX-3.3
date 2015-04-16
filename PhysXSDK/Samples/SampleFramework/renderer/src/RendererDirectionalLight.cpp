/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererDirectionalLight.h>
#include <RendererDirectionalLightDesc.h>

using namespace SampleRenderer;

RendererDirectionalLight::RendererDirectionalLight(const RendererDirectionalLightDesc &desc) :
RendererLight(desc)
{
	setDirection(desc.direction);
}

RendererDirectionalLight::~RendererDirectionalLight(void)
{

}

const PxVec3 &RendererDirectionalLight::getDirection(void) const
{
	return m_direction;
}

void RendererDirectionalLight::setDirection(const PxVec3 &dir)
{
	RENDERER_ASSERT(dir.magnitudeSquared() >= 0.1f, "Trying to give Direction Light invalid Direction value.");
	if(dir.magnitudeSquared() >= 0.1f)
	{
		m_direction = dir;
		m_direction.normalize();
	}
}
