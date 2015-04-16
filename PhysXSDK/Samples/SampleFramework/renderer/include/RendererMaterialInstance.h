/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_MATERIAL_INSTANCE_H
#define RENDERER_MATERIAL_INSTANCE_H

#include <RendererConfig.h>

#include <RendererMaterial.h>

namespace SampleRenderer
{

	class RendererMaterialInstance
	{
		friend class RendererMaterial;
	public:
		RendererMaterialInstance(RendererMaterial &material);
		RendererMaterialInstance(const RendererMaterialInstance& other);
		~RendererMaterialInstance(void);

		PX_FORCE_INLINE RendererMaterial &getMaterial(void) { return m_material; }

		PX_FORCE_INLINE const RendererMaterial::Variable *findVariable(const char *name, RendererMaterial::VariableType varType)
		{
			return m_material.findVariable(name, varType);
		}

		void writeData(const RendererMaterial::Variable &var, const void *data);

		RendererMaterialInstance &operator=(const RendererMaterialInstance&);

	private:
		RendererMaterial &m_material;
		PxU8             *m_data;

	};

} // namespace SampleRenderer

#endif
