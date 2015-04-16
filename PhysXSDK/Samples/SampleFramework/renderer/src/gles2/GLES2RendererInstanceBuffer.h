/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef GLES2_RENDERER_INSTANCEBUFFER_H
#define GLES2_RENDERER_INSTANCEBUFFER_H

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_GLES2)

#include <RendererInstanceBuffer.h>
#include "GLES2Renderer.h"

namespace SampleRenderer
{

	class GLES2RendererInstanceBuffer : public RendererInstanceBuffer
	{
	public:
		GLES2RendererInstanceBuffer(const RendererInstanceBufferDesc &desc);
		virtual ~GLES2RendererInstanceBuffer(void);

		physx::PxMat44 getModelMatrix(PxU32 index) const;

	private:
		PxVec3 getInstanceColumn(const void *instance, const GLES2RendererInstanceBuffer::SemanticDesc &sd) const;

	public:

		virtual void *lock(void);
		virtual void  unlock(void);

		virtual void  bind(PxU32 streamID, PxU32 firstInstance) const;
		virtual void  unbind(PxU32 streamID) const;

	private:
		PxU32    m_bufferSize;
		void    *m_buffer;
	};

} // namespace SampleRenderer

#endif // #if defined(RENDERER_ENABLE_GLES2)
#endif
