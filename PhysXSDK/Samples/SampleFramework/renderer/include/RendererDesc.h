/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_DESC_H
#define RENDERER_DESC_H

#include <RendererConfig.h>
#include <Renderer.h>

namespace SampleRenderer
{

	class RendererWindow;

	class RendererDesc
	{
	public:
		Renderer::DriverType	driver;

		/* optional error callback */
		PxErrorCallback*		errorCallback;
		physx::PxU64	        windowHandle;

		bool					vsync;

		/* enable depth bias for multipass rendering */
		bool					multipassDepthBias;
	public:
		RendererDesc(void);

		bool isValid(void) const;
	};

} // namespace SampleRenderer

#endif
