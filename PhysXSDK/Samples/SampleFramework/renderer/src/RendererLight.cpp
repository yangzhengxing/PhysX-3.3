/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererLight.h>
#include <RendererLightDesc.h>

#include <Renderer.h>

using namespace SampleRenderer;

RendererLight::RendererLight(const RendererLightDesc &desc) :
m_type(desc.type),
m_shadowProjection(45, 1, 0.1f, 100.0f)
{
	m_renderer = 0;
	setColor(desc.color);
	setIntensity(desc.intensity);
	setShadowMap(desc.shadowMap);
	setShadowTransform(desc.shadowTransform);
	setShadowProjection(desc.shadowProjection);
}

RendererLight::~RendererLight(void)
{
	RENDERER_ASSERT(!isLocked(), "Light is locked by a Renderer during release.");
}

void SampleRenderer::RendererLight::release(void)
{
	if (m_renderer) m_renderer->removeLightFromRenderQueue(*this);
	delete this;
}

RendererLight::Type RendererLight::getType(void) const
{
	return m_type;
}

RendererMaterial::Pass RendererLight::getPass(void) const
{
	RendererMaterial::Pass pass = RendererMaterial::NUM_PASSES;
	switch(m_type)
	{
	case TYPE_POINT:       pass = RendererMaterial::PASS_POINT_LIGHT;       break;
	case TYPE_DIRECTIONAL: pass = RendererMaterial::PASS_DIRECTIONAL_LIGHT; break;
	case TYPE_SPOT:        pass = m_shadowMap != NULL ? RendererMaterial::PASS_SPOT_LIGHT : RendererMaterial::PASS_SPOT_LIGHT_NO_SHADOW;        break;
	default: break;
	}
	RENDERER_ASSERT(pass < RendererMaterial::NUM_PASSES, "Unable to compute the Pass for the Light.");
	return pass;
}

const RendererColor &RendererLight::getColor(void) const
{
	return m_color;
}

void RendererLight::setColor(const RendererColor &color)
{
	m_color = color;
}

float RendererLight::getIntensity(void) const
{
	return m_intensity;
}

void RendererLight::setIntensity(float intensity)
{
	RENDERER_ASSERT(intensity >= 0, "Light intensity is negative.");
	if(intensity >= 0)
	{
		m_intensity = intensity;
	}
}

bool RendererLight::isLocked(void) const
{
	return m_renderer ? true : false;
}

RendererTexture2D *RendererLight::getShadowMap(void) const
{
	return m_shadowMap;
}

void RendererLight::setShadowMap(RendererTexture2D *shadowMap)
{
	m_shadowMap = shadowMap;
}

const RendererProjection &RendererLight::getShadowProjection(void) const
{
	return m_shadowProjection;
}

void RendererLight::setShadowProjection(const RendererProjection &shadowProjection)
{
	m_shadowProjection = shadowProjection;
}

