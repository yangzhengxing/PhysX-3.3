/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#include <RendererConfig.h>



#include "NULLRendererDirectionalLight.h"

using namespace SampleRenderer;

NullRendererDirectionalLight::NullRendererDirectionalLight(const RendererDirectionalLightDesc &desc) :
	RendererDirectionalLight(desc)
{
}

NullRendererDirectionalLight::~NullRendererDirectionalLight(void)
{
}

void NullRendererDirectionalLight::bind(void) const
{
}

