/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_OPENGL)

#include "OGLRendererSpotLight.h"

using namespace SampleRenderer;

OGLRendererSpotLight::OGLRendererSpotLight(const RendererSpotLightDesc &desc, OGLRenderer &renderer) 
:	RendererSpotLight(desc)
#if defined(RENDERER_ENABLE_CG)
,	m_cgenv(renderer.getCGEnvironment())
#endif
{

}

OGLRendererSpotLight::~OGLRendererSpotLight(void)
{

}

void OGLRendererSpotLight::bind(void) const
{
#if defined(RENDERER_ENABLE_CG)
	setColorParameter(m_cgenv.lightColor,        m_color);
	cgSetParameter1f( m_cgenv.lightIntensity,    m_intensity);
	cgSetParameter3fv(m_cgenv.lightDirection,   &m_direction.x);
	cgSetParameter3fv(m_cgenv.lightPosition,    &m_position.x);
	cgSetParameter1f( m_cgenv.lightInnerRadius,  m_innerRadius);
	cgSetParameter1f( m_cgenv.lightOuterRadius,  m_outerRadius);
	cgSetParameter1f( m_cgenv.lightInnerCone,    m_innerCone);
	cgSetParameter1f( m_cgenv.lightOuterCone,    m_outerCone);
#endif
}

#endif
