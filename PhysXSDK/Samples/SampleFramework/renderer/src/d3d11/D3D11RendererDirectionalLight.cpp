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

#include "D3D11RendererDirectionalLight.h"

using namespace SampleRenderer;

D3D11RendererDirectionalLight::D3D11RendererDirectionalLight(D3D11Renderer& renderer, const RendererDirectionalLightDesc& desc) :
	RendererDirectionalLight(desc),
	m_renderer(renderer)
{

}

D3D11RendererDirectionalLight::~D3D11RendererDirectionalLight(void)
{

}

void D3D11RendererDirectionalLight::bind(PxU32 lightIndex) const
{
	D3D11Renderer::D3D11ShaderEnvironment& shaderEnv = m_renderer.getShaderEnvironment();
	if (lightIndex < RENDERER_MAX_LIGHTS)
	{
		convertToD3D11(shaderEnv.lightColor[lightIndex], m_color);
		shaderEnv.lightDirection[lightIndex] = m_direction;
		shaderEnv.lightIntensity[lightIndex] = m_intensity;
		shaderEnv.lightType[lightIndex]      = RendererMaterial::PASS_DIRECTIONAL_LIGHT;
		shaderEnv.bindLight(lightIndex);
	}
}

#endif // #if defined(RENDERER_ENABLE_DIRECT3D11)
