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

#if defined(RENDERER_ENABLE_DIRECT3D9)

#include "D3D9RendererSpotLight.h"
#include "D3D9RendererTexture2D.h"

using namespace SampleRenderer;

D3D9RendererSpotLight::D3D9RendererSpotLight(D3D9Renderer &renderer, const RendererSpotLightDesc &desc) :
	RendererSpotLight(desc),
m_renderer(renderer)
{

}

D3D9RendererSpotLight::~D3D9RendererSpotLight(void)
{

}

void D3D9RendererSpotLight::bind(void) const
{
	D3D9Renderer::ShaderEnvironment &shaderEnv = m_renderer.getShaderEnvironment();
	convertToD3D9(shaderEnv.lightColor, m_color);
	shaderEnv.lightIntensity = m_intensity;
	convertToD3D9(shaderEnv.lightPosition,  m_position);
	convertToD3D9(shaderEnv.lightDirection, m_direction);
	shaderEnv.lightInnerRadius = m_innerRadius;
	shaderEnv.lightOuterRadius = m_outerRadius;
	shaderEnv.lightInnerCone   = m_innerCone;
	shaderEnv.lightOuterCone   = m_outerCone;
	shaderEnv.lightShadowMap   = m_shadowMap ? static_cast<D3D9RendererTexture2D*>(m_shadowMap)->m_d3dTexture : 0;
	buildProjectMatrix(shaderEnv.lightShadowMatrix, m_shadowProjection, m_shadowTransform);
}

#endif // #if defined(RENDERER_ENABLE_DIRECT3D9)
