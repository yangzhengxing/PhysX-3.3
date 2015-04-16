/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef NULL_RENDERER_MATERIAL_H
#define NULL_RENDERER_MATERIAL_H

#include <RendererConfig.h>

#include <RendererMaterial.h>

#include "NULLRenderer.h"

namespace SampleRenderer
{

	class NullRendererMaterial : public RendererMaterial
	{		
	public:
		NullRendererMaterial(NullRenderer &renderer, const RendererMaterialDesc &desc);
		virtual ~NullRendererMaterial(void);
		virtual void setModelMatrix(const float *matrix) 
		{
			PX_UNUSED(matrix);
			PX_ALWAYS_ASSERT();
		}

	private:
		virtual const Renderer& getRenderer() const { return m_renderer; }
		virtual void bind(RendererMaterial::Pass pass, RendererMaterialInstance *materialInstance, bool instanced) const;
		virtual void bindMeshState(bool instanced) const;
		virtual void unbind(void) const;
		virtual void bindVariable(Pass pass, const Variable &variable, const void *data) const;

	private:
		NullRendererMaterial &operator=(const NullRendererMaterial&) { return *this; }

	private:
		NullRenderer &			m_renderer;
	};

} // namespace SampleRenderer

#endif
