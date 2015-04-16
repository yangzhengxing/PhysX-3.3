/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_SPOT_LIGHT_DESC_H
#define RENDERER_SPOT_LIGHT_DESC_H

#include <RendererLightDesc.h>

namespace SampleRenderer
{

	class RendererSpotLightDesc : public RendererLightDesc
	{
	public:
		PxVec3	   position;
		PxVec3	   direction;

		PxF32      innerRadius;
		PxF32      outerRadius;

		// cone = dot(direction, directionToFragment);
		// so cone value of 0 is completely open and value of 1 is completely closed.
		PxF32      innerCone;
		PxF32      outerCone;

	public:
		RendererSpotLightDesc(void);

		virtual bool isValid(void) const;
	};

} // namespace SampleRenderer

#endif
