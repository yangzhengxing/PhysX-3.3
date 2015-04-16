/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef OGL_RENDERER_DIRECTIONAL_LIGHT_H
#define OGL_RENDERER_DIRECTIONAL_LIGHT_H

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_OPENGL)

#include <RendererDirectionalLight.h>

#include "OGLRenderer.h"

namespace SampleRenderer
{

	class RendererDirectionalLightDesc;

	class OGLRendererDirectionalLight : public RendererDirectionalLight
	{
	public:
		OGLRendererDirectionalLight(const RendererDirectionalLightDesc &desc, OGLRenderer &renderer);
		virtual ~OGLRendererDirectionalLight(void);

		virtual void bind(void) const;

	private:
#if defined(RENDERER_ENABLE_CG)
		const OGLRenderer::CGEnvironment &m_cgenv;
#endif
	};

} // namespace SampleRenderer

#endif // #if defined(RENDERER_ENABLE_OPENGL)
#endif
