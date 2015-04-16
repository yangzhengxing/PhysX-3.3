/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


#include "GLES2RendererDirectionalLight.h"
#include "GLES2RendererMaterial.h"
#include "GLES2Renderer.h"
#include "RendererMaterialInstance.h"

#if defined(RENDERER_ENABLE_GLES2)
namespace SampleRenderer
{

GLES2RendererDirectionalLight::GLES2RendererDirectionalLight(const RendererDirectionalLightDesc &desc, 
															GLES2Renderer &renderer, GLfloat (&_lightColor)[3], 
															GLfloat& _lightIntensity, GLfloat (&_lightDirection)[3]) :
	RendererDirectionalLight(desc), m_lightColor(_lightColor), m_lightIntensity(_lightIntensity), m_lightDirection(_lightDirection)
{
}

GLES2RendererDirectionalLight::~GLES2RendererDirectionalLight(void)
{
}

extern GLES2RendererMaterial* g_hackCurrentMat;
extern RendererMaterialInstance* g_hackCurrentMatInstance;

void GLES2RendererDirectionalLight::bind(void) const
{
	m_lightColor[0] = m_color.r/255.0f;
	m_lightColor[1] = m_color.g/255.0f;
	m_lightColor[2] = m_color.b/255.0f;
	m_lightIntensity = m_intensity;
	m_lightDirection[0] = m_direction.x;
	m_lightDirection[1] = m_direction.y;
	m_lightDirection[2] = m_direction.z;
}

}

#endif // #if defined(RENDERER_ENABLE_GLES2)
