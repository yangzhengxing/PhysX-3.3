/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef NULL_RENDERER_INDEXBUFFER_H
#define NULL_RENDERER_INDEXBUFFER_H

#include <RendererConfig.h>

#include <RendererIndexBuffer.h>

namespace SampleRenderer
{

	class NullRendererIndexBuffer : public RendererIndexBuffer
	{
	public:
		NullRendererIndexBuffer(const RendererIndexBufferDesc &desc);
		virtual ~NullRendererIndexBuffer(void);

	public:
		virtual void *lock(void);
		virtual void  unlock(void);

	private:
		virtual void bind(void) const;
		virtual void unbind(void) const;

	private:
		PxU8*			m_Buffer;
	};

} // namespace SampleRenderer

#endif
