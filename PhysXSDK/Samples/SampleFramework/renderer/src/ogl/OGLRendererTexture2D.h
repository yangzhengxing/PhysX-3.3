/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef OGL_RENDERER_TEXTURE_2D_H
#define OGL_RENDERER_TEXTURE_2D_H

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_OPENGL)

#include <RendererTexture2D.h>
#include "OGLRenderer.h"

namespace SampleRenderer
{

	class OGLRendererTexture2D : public RendererTexture2D
	{
	public:
		OGLRendererTexture2D(const RendererTexture2DDesc &desc);
		virtual ~OGLRendererTexture2D(void);

	public:
		virtual void *lockLevel(PxU32 level, PxU32 &pitch);
		virtual void  unlockLevel(PxU32 level);

		void bind(PxU32 textureUnit);

		virtual	void	select(PxU32 stageIndex)
		{
			bind(stageIndex);
		}

	private:

		GLuint m_textureid;
		GLuint m_glformat;
		GLuint m_glinternalformat;
		GLuint m_gltype;

		PxU32  m_width;
		PxU32  m_height;

		PxU32  m_numLevels;

		PxU8 **m_data;
	};

} // namespace SampleRenderer

#endif // #if defined(RENDERER_ENABLE_OPENGL)
#endif
