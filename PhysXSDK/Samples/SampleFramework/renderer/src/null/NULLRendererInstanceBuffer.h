/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef NULL_RENDERER_INSTANCEBUFFER_H
#define NULL_RENDERER_INSTANCEBUFFER_H

#include <RendererConfig.h>

#include <RendererInstanceBuffer.h>

namespace SampleRenderer
{

	class NullRendererInstanceBuffer : public RendererInstanceBuffer
	{
	public:
		NullRendererInstanceBuffer(const RendererInstanceBufferDesc &desc);
		virtual ~NullRendererInstanceBuffer(void);

	public:

		virtual void *lock(void);
		virtual void  unlock(void);

		virtual void  bind(PxU32 streamID, PxU32 firstInstance) const;
		virtual void  unbind(PxU32 streamID) const;

	private:
		PxU8    *m_buffer;
		PxU32    m_bufferSize;
	};

} // namespace SampleRenderer

#endif
