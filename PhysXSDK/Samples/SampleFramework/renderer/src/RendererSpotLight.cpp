/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererSpotLight.h>
#include <RendererSpotLightDesc.h>

using namespace SampleRenderer;

RendererSpotLight::RendererSpotLight(const RendererSpotLightDesc &desc) :
	RendererLight(desc)
{
	setPosition(desc.position);
	setDirection(desc.direction);
	setRadius(desc.innerRadius, desc.outerRadius);
	setCone(desc.innerCone, desc.outerCone);
}

RendererSpotLight::~RendererSpotLight(void)
{

}

const PxVec3 &RendererSpotLight::getPosition(void) const
{
	return m_position;
}

void RendererSpotLight::setPosition(const PxVec3 &pos)
{
	m_position = pos;
}

const PxVec3 &RendererSpotLight::getDirection(void) const
{
	return m_direction;
}

void RendererSpotLight::setDirection(const PxVec3 &dir)
{
	RENDERER_ASSERT(dir.magnitudeSquared() >= 0.1f, "Trying to give Direction Light invalid Direction value.");
	if(dir.magnitudeSquared() >= 0.1f)
	{
		m_direction = dir;
		m_direction.normalize();
	}
}

PxF32 RendererSpotLight::getInnerRadius(void) const
{
	return m_innerRadius;
}

PxF32 RendererSpotLight::getOuterRadius(void) const
{
	return m_outerRadius;
}

void RendererSpotLight::setRadius(PxF32 innerRadius, PxF32 outerRadius)
{
	RENDERER_ASSERT(innerRadius>=0 && innerRadius<=outerRadius, "Invalid Spot Light radius values.");
	if(innerRadius>=0 && innerRadius<=outerRadius)
	{
		m_innerRadius = innerRadius;
		m_outerRadius = outerRadius;
	}
}

PxF32 RendererSpotLight::getInnerCone(void) const
{
	return m_innerCone;
}

PxF32 RendererSpotLight::getOuterCone(void) const
{
	return m_outerCone;
}

void RendererSpotLight::setCone(PxF32 innerCone, PxF32 outerCone)
{
	RENDERER_ASSERT(innerCone<=1 && innerCone>=outerCone, "Invalid Spot Light cone values.");
	if(innerCone<=1 && innerCone>=outerCone)
	{
		m_innerCone = innerCone;
		m_outerCone = outerCone;
	}
}
