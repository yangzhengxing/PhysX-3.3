/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


#ifndef RENDERER_LIGHT_H
#define RENDERER_LIGHT_H

#include <RendererConfig.h>
#include <RendererColor.h>
#include <RendererMaterial.h>
#include <RendererProjection.h>

namespace SampleRenderer
{

	class RendererLightDesc;
	class Renderer;
	class RendererLight
	{
		friend class Renderer;
	public:
		enum Type
		{
			TYPE_POINT = 0,
			TYPE_DIRECTIONAL,
			TYPE_SPOT,

			NUM_TYPES
		}_Type;

	protected:
		RendererLight(const RendererLightDesc &desc);
		virtual ~RendererLight(void);

	public:
		void                      release(void);

		Type                      getType(void) const;

		RendererMaterial::Pass    getPass(void) const;

		const RendererColor      &getColor(void) const;
		void                      setColor(const RendererColor &color);

		float                     getIntensity(void) const;
		void                      setIntensity(float intensity);

		bool                      isLocked(void) const;

		RendererTexture2D        *getShadowMap(void) const;
		void                      setShadowMap(RendererTexture2D *shadowMap);

		const physx::PxTransform &getShadowTransform(void) const	{ return m_shadowTransform; }
		void                      setShadowTransform(const physx::PxTransform &shadowTransform) { m_shadowTransform = shadowTransform; }

		const RendererProjection &getShadowProjection(void) const;
		void                      setShadowProjection(const RendererProjection &shadowProjection);

	private:
		RendererLight &operator=(const RendererLight &) { return *this; }

		virtual void bind(void) const = 0;

	protected:
		const Type         m_type;

		RendererColor      m_color;
		float              m_intensity;

		RendererTexture2D *m_shadowMap;
		physx::PxTransform m_shadowTransform;
		RendererProjection m_shadowProjection;

	private:
		Renderer          *m_renderer;
	};

} // namespace SampleRenderer

#endif
