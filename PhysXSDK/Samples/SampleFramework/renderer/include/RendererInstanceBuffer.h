/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_INSTANCEBUFFER_H
#define RENDERER_INSTANCEBUFFER_H

#include <RendererConfig.h>
#include "RendererInteropableBuffer.h"

namespace SampleRenderer
{

	class RendererInstanceBufferDesc;

	class RendererInstanceBuffer: public RendererInteropableBuffer
	{
		friend class RendererMesh;
	public:
		enum Semantic
		{
			SEMANTIC_POSITION = 0,
			SEMANTIC_NORMALX,
			SEMANTIC_NORMALY,
			SEMANTIC_NORMALZ,
			SEMANTIC_VELOCITY_LIFE,// life remain (0-1] is packed into w
			SEMANTIC_DENSITY,
			SEMANTIC_UV_OFFSET,
			SEMANTIC_LOCAL_OFFSET,

			NUM_SEMANTICS
		}_Semantic;

		enum Format
		{
			FORMAT_FLOAT1 = 0,
			FORMAT_FLOAT2,
			FORMAT_FLOAT3,
			FORMAT_FLOAT4,

			NUM_FORMATS,
		}_Format;

		enum Hint
		{
			HINT_STATIC = 0,
			HINT_DYNAMIC,
		}_Hint;

	public:
		static PxU32 getFormatByteSize(Format format);

	protected:
		RendererInstanceBuffer(const RendererInstanceBufferDesc &desc);
		virtual ~RendererInstanceBuffer(void);

	public:
		void release(void) { delete this; }

		Hint   getHint(void) const;
		Format getFormatForSemantic(Semantic semantic) const;
		PxU32  getMaxInstances(void) const;
		PxU32  getOffsetForSemantic(Semantic semantic) const;

		void *lockSemantic(Semantic semantic, PxU32 &stride);
		void  unlockSemantic(Semantic semantic);

		virtual void *lock(void) = 0;
		virtual void  unlock(void) = 0;
		virtual PxU32 getStride(void) const { return m_stride; }
	private:

		virtual void  bind(PxU32 streamID, PxU32 firstInstance) const = 0;
		virtual void  unbind(PxU32 streamID) const = 0;

		RendererInstanceBuffer &operator=(const RendererInstanceBuffer &) { return *this; }

	protected:
		class SemanticDesc
		{
		public:
			Format format;
			PxU32  offset;
			bool   locked;
		public:
			SemanticDesc(void)
			{
				format = NUM_FORMATS;
				offset = 0;
				locked = false;
			}
		};

	protected:
		const Hint   m_hint;
		PxU32        m_maxInstances;
		PxU32        m_stride;
		SemanticDesc m_semanticDescs[NUM_SEMANTICS];

	private:
		void        *m_lockedBuffer;
		PxU32        m_numSemanticLocks;
	};

} // namespace SampleRenderer

#endif
