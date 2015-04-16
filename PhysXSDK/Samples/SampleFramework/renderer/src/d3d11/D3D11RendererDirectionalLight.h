/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef D3D11_RENDERER_DIRECTIONAL_LIGHT_H
#define D3D11_RENDERER_DIRECTIONAL_LIGHT_H

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_DIRECT3D11)

#include <RendererDirectionalLight.h>

#include "D3D11Renderer.h"

namespace SampleRenderer
{

class D3D11RendererDirectionalLight : public RendererDirectionalLight
{
public:
	D3D11RendererDirectionalLight(D3D11Renderer& renderer, const RendererDirectionalLightDesc& desc);
	virtual ~D3D11RendererDirectionalLight(void);

	virtual void bind(void) const { bind(0); }
	virtual void bind(PxU32) const;

private:
	D3D11Renderer& m_renderer;
};

} // namespace SampleRenderer

#endif // #if defined(RENDERER_ENABLE_DIRECT3D11)
#endif
