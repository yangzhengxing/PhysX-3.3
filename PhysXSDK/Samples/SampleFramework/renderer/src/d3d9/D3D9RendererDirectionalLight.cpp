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

#include "D3D9RendererDirectionalLight.h"

using namespace SampleRenderer;

D3D9RendererDirectionalLight::D3D9RendererDirectionalLight(D3D9Renderer &renderer, const RendererDirectionalLightDesc &desc) :
	RendererDirectionalLight(desc),
	m_renderer(renderer)
{

}

D3D9RendererDirectionalLight::~D3D9RendererDirectionalLight(void)
{

}

void D3D9RendererDirectionalLight::bind(void) const
{
	D3D9Renderer::ShaderEnvironment &shaderEnv = m_renderer.getShaderEnvironment();
	convertToD3D9(shaderEnv.lightColor, m_color);
	shaderEnv.lightIntensity = m_intensity;
	convertToD3D9(shaderEnv.lightDirection, m_direction);
}

#endif // #if defined(RENDERER_ENABLE_DIRECT3D9)
