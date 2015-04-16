/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef OGL_RENDERER_INDEXBUFFER_H
#define OGL_RENDERER_INDEXBUFFER_H

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_OPENGL)

#include <RendererIndexBuffer.h>
#include "OGLRenderer.h"

namespace SampleRenderer
{

	class OGLRendererIndexBuffer : public RendererIndexBuffer
	{
	public:
		OGLRendererIndexBuffer(const RendererIndexBufferDesc &desc);
		virtual ~OGLRendererIndexBuffer(void);

	public:
		virtual void *lock(void);
		virtual void  unlock(void);

	private:
		virtual void bind(void) const;
		virtual void unbind(void) const;

	private:
		GLuint m_ibo;
		PxU32  m_indexSize;
	};

} // namespace SampleRenderer

#endif // #if defined(RENDERER_ENABLE_OPENGL)
#endif
