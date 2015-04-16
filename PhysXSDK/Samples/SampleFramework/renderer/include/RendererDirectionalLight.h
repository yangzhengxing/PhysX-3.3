/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_DIRECTIONAL_LIGHT_H
#define RENDERER_DIRECTIONAL_LIGHT_H

#include <RendererLight.h>

namespace SampleRenderer
{

	class RendererDirectionalLightDesc;

	class RendererDirectionalLight : public RendererLight
	{
	protected:
		RendererDirectionalLight(const RendererDirectionalLightDesc &desc);
		virtual ~RendererDirectionalLight(void);

	public:
		const PxVec3 &getDirection(void) const;
		void          setDirection(const PxVec3 &dir);

	protected:
		PxVec3 m_direction;
	};

} // namespace SampleRenderer

#endif
