/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef NULL_RENDERER_VERTEXBUFFER_H
#define NULL_RENDERER_VERTEXBUFFER_H

#include <RendererConfig.h>

#include <RendererVertexBuffer.h>

namespace SampleRenderer
{

	class NullRendererVertexBuffer : public RendererVertexBuffer
	{
	public:
		NullRendererVertexBuffer(const RendererVertexBufferDesc &desc);
		virtual ~NullRendererVertexBuffer(void);

	protected:
		virtual void  swizzleColor(void *colors, PxU32 stride, PxU32 numColors, RendererVertexBuffer::Format inFormat);

		virtual void *lock(void);
		virtual void  unlock(void);

		virtual void  bind(PxU32 streamID, PxU32 firstVertex);
		virtual void  unbind(PxU32 streamID);

	private:
		PxU8*		m_buffer;
	};

} // namespace SampleRenderer

#endif
