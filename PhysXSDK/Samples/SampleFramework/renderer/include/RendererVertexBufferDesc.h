/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_VERTEXBUFFER_DESC_H
#define RENDERER_VERTEXBUFFER_DESC_H

#include <RendererVertexBuffer.h>

namespace SampleRenderer
{

	class RendererVertexBufferDesc
	{
	public:
		RendererVertexBuffer::Hint         hint;
		RendererVertexBuffer::Format       semanticFormats[RendererVertexBuffer::NUM_SEMANTICS];

		PxU32								maxVertices;

		///mark this buffer can be read back by lock, lock flag should not be discard
		bool								canReadBack;
		
		bool								registerInCUDA;
		physx::PxCudaContextManager *interopContext;

	public:
		RendererVertexBufferDesc(void);

		bool isValid(void) const;
	};

} // namespace SampleRenderer

#endif
