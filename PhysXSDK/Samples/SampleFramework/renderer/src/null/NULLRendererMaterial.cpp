/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#include "RendererConfig.h"

#include "NULLRendererMaterial.h"

#include <RendererMaterialDesc.h>

#include <SamplePlatform.h>

// for PsString.h
namespace physx
{
	namespace string
	{}
}
#include <PsString.h>
#include <PsFile.h>

using namespace SampleRenderer;

NullRendererMaterial::NullRendererMaterial(NullRenderer &renderer, const RendererMaterialDesc &desc) :
	RendererMaterial(desc, renderer.getEnableMaterialCaching()),
	m_renderer(renderer)
{
}

NullRendererMaterial::~NullRendererMaterial(void)
{
}


void NullRendererMaterial::bind(RendererMaterial::Pass pass, RendererMaterialInstance *materialInstance, bool instanced) const
{
	RendererMaterial::bind(pass, materialInstance, instanced);
}

void NullRendererMaterial::bindMeshState(bool instanced) const
{

}

void NullRendererMaterial::unbind(void) const
{

}


void NullRendererMaterial::bindVariable(Pass pass, const Variable &variable, const void *data) const
{
}


