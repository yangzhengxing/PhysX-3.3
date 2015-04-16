/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererDesc.h>

using namespace SampleRenderer;

RendererDesc::RendererDesc(void)
{
#if defined(RENDERER_ENABLE_OPENGL)
	driver = Renderer::DRIVER_OPENGL;
#elif defined(RENDERER_ENABLE_GLES2)
	driver = Renderer::DRIVER_GLES2;
#elif defined(RENDERER_ENABLE_DIRECT3D9)
	driver = Renderer::DRIVER_DIRECT3D9;
#elif defined(RENDERER_ENABLE_DIRECT3D11)
	driver = Renderer::DRIVER_DIRECT3D11;
#elif defined(RENDERER_ENABLE_LIBGCM)
	driver = Renderer::DRIVER_LIBGCM;
#elif defined(RENDERER_ENABLE_LIBGNM)
	driver = Renderer::DRIVER_LIBGNM;
#elif defined(RENDERER_ENABLE_LIBGXM)
	driver = Renderer::DRIVER_LIBGXM;
#elif defined(RENDERER_ENABLE_GX2)
	driver = Renderer::DRIVER_NULL;
#else
#error "No Renderer Drivers support!"
#endif
	windowHandle   = 0;

	errorCallback = 0;

	vsync = false;

	multipassDepthBias = false;
}

bool RendererDesc::isValid(void) const
{
	bool ok = true;
#if defined(RENDERER_WINDOWS)
	if(!windowHandle) ok = false;
#endif
	return ok;
}
