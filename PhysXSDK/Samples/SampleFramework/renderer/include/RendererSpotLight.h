/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_SPOT_LIGHT_H
#define RENDERER_SPOT_LIGHT_H

#include <RendererLight.h>

namespace SampleRenderer
{

	class RendererSpotLightDesc;

	class RendererSpotLight : public RendererLight
	{
	protected:
		RendererSpotLight(const RendererSpotLightDesc &desc);
		virtual ~RendererSpotLight(void);

	public:
		const PxVec3 &getPosition(void) const;
		void          setPosition(const PxVec3 &pos);

		const PxVec3 &getDirection(void) const;
		void          setDirection(const PxVec3 &dir);

		PxF32         getInnerRadius(void) const;
		PxF32         getOuterRadius(void) const;
		void          setRadius(PxF32 innerRadius, PxF32 outerRadius);

		PxF32         getInnerCone(void) const;
		PxF32         getOuterCone(void) const;
		void          setCone(PxF32 innerCone, PxF32 outerCone);

	protected:
		PxVec3        m_position;
		PxVec3        m_direction;
		PxF32         m_innerRadius;
		PxF32         m_outerRadius;
		PxF32         m_innerCone;
		PxF32         m_outerCone;
	};

} // namespace SampleRenderer

#endif
