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

#if defined(RENDERER_ENABLE_DIRECT3D11)

#include "D3D11RendererSpotLight.h"
#include "D3D11RendererTexture2D.h"

using namespace SampleRenderer;

D3D11RendererSpotLight::D3D11RendererSpotLight(D3D11Renderer& renderer, const RendererSpotLightDesc& desc) :
	RendererSpotLight(desc),
	m_renderer(renderer)
{

}

D3D11RendererSpotLight::~D3D11RendererSpotLight(void)
{

}

void D3D11RendererSpotLight::bind(PxU32 lightIndex) const
{
	if (lightIndex < RENDERER_MAX_LIGHTS)
	{
		D3D11Renderer::D3D11ShaderEnvironment& shaderEnv = m_renderer.getShaderEnvironment();
		convertToD3D11(shaderEnv.lightColor[lightIndex], m_color);
		shaderEnv.lightPosition[lightIndex] = m_position;
		shaderEnv.lightDirection[lightIndex] = m_direction;
		shaderEnv.lightIntensity[lightIndex] = m_intensity;
		shaderEnv.lightInnerRadius[lightIndex] = m_innerRadius;
		shaderEnv.lightOuterRadius[lightIndex] = m_outerRadius;
		shaderEnv.lightInnerCone[lightIndex]   = m_innerCone;
		shaderEnv.lightOuterCone[lightIndex]   = m_outerCone;
		shaderEnv.lightType[lightIndex]        = RendererMaterial::PASS_SPOT_LIGHT;
		shaderEnv.lightShadowMap   = m_shadowMap ? static_cast<D3D11RendererTexture2D*>(m_shadowMap) : NULL;
		buildProjectMatrix(&shaderEnv.lightShadowMatrix.column0.x, m_shadowProjection, m_shadowTransform);
		shaderEnv.bindLight(lightIndex);
	}
}

#endif // #if defined(RENDERER_ENABLE_DIRECT3D11)
