/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_LIGHT_DESC_H
#define RENDERER_LIGHT_DESC_H

#include <RendererLight.h>
#include <RendererProjection.h>

namespace SampleRenderer
{

	class RendererLightDesc
	{
	public:
		const RendererLight::Type type;

		RendererColor             color;
		float                     intensity;

		RendererTexture2D *shadowMap;
		physx::PxTransform shadowTransform;
		RendererProjection shadowProjection;

	protected:
		RendererLightDesc(RendererLight::Type _type);
		virtual ~RendererLightDesc() {}

	public:
		virtual bool isValid(void) const;

	private:
		RendererLightDesc &operator=(const RendererLightDesc&) { return *this; }
	};

} // namespace SampleRenderer

#endif
