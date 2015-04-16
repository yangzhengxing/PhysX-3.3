/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_DIRECTIONAL_LIGHT_DESC_H
#define RENDERER_DIRECTIONAL_LIGHT_DESC_H

#include <RendererLightDesc.h>

namespace SampleRenderer
{

	class RendererDirectionalLightDesc : public RendererLightDesc
	{
	public:
		PxVec3 direction;

	public:
		RendererDirectionalLightDesc(void);

		virtual bool isValid(void) const;
	};

} // namespace SampleRenderer

#endif
