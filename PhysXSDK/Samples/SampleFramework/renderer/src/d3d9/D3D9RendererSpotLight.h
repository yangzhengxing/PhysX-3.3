/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef D3D9_RENDERER_SPOT_LIGHT_H
#define D3D9_RENDERER_SPOT_LIGHT_H

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_DIRECT3D9)

#include <RendererSpotLight.h>

#include "D3D9Renderer.h"

namespace SampleRenderer
{

	class D3D9RendererSpotLight : public RendererSpotLight
	{
	public:
		D3D9RendererSpotLight(D3D9Renderer &renderer, const RendererSpotLightDesc &desc);
		virtual ~D3D9RendererSpotLight(void);

		virtual void bind(void) const;

	private:
		D3D9Renderer &m_renderer;
	};

} // namespace SampleRenderer

#endif // #if defined(RENDERER_ENABLE_DIRECT3D9)
#endif
