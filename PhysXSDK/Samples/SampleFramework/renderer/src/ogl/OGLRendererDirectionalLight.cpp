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

#include "OGLRendererDirectionalLight.h"

using namespace SampleRenderer;

OGLRendererDirectionalLight::OGLRendererDirectionalLight(const RendererDirectionalLightDesc &desc, OGLRenderer &renderer) 
:	RendererDirectionalLight(desc)
#if defined(RENDERER_ENABLE_CG)
,	m_cgenv(renderer.getCGEnvironment())
#endif

{
}

OGLRendererDirectionalLight::~OGLRendererDirectionalLight(void)
{
}

void OGLRendererDirectionalLight::bind(void) const
{
#if defined(RENDERER_ENABLE_CG)
	setColorParameter(m_cgenv.lightColor,      m_color);
	cgSetParameter1f( m_cgenv.lightIntensity,  m_intensity);
	cgSetParameter3fv(m_cgenv.lightDirection, &m_direction.x);
#endif
}

#endif // #if defined(RENDERER_ENABLE_OPENGL)
