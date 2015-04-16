/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_INDEXBUFFER_H
#define RENDERER_INDEXBUFFER_H

#include <RendererConfig.h>
#include "RendererInteropableBuffer.h"

namespace SampleRenderer
{

	class RendererIndexBufferDesc;

	class RendererIndexBuffer: public RendererInteropableBuffer
	{
		friend class RendererMesh;
		friend class GLES2Renderer;
	public:
		enum Format
		{
			FORMAT_UINT16 = 0,
			FORMAT_UINT32,

			NUM_FORMATS
		}_Format;

		enum Hint
		{
			HINT_STATIC = 0,
			HINT_DYNAMIC,
		}_Hint;

	public:
		static PxU32 getFormatByteSize(Format format);

	protected:
		RendererIndexBuffer(const RendererIndexBufferDesc &desc);
		virtual ~RendererIndexBuffer(void);

	public:
		void release(void) { delete this; }

		Hint   getHint(void) const;
		Format getFormat(void) const;
		PxU32  getMaxIndices(void) const;

	public:
		virtual void *lock(void) = 0;
		virtual void  unlock(void) = 0;

	private:
		virtual void bind(void) const = 0;
		virtual void unbind(void) const = 0;

		RendererIndexBuffer &operator=(const RendererIndexBuffer &) { return *this; }

	protected:
		const Hint   m_hint;
		const Format m_format;
		PxU32        m_maxIndices;
	};

} // namespace SampleRenderer

#endif
