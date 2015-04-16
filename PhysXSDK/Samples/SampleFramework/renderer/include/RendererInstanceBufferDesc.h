/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_INSTANCEBUFFER_DESC_H
#define RENDERER_INSTANCEBUFFER_DESC_H

#include <RendererInstanceBuffer.h>

namespace SampleRenderer
{

	class RendererInstanceBufferDesc
	{
	public:
		RendererInstanceBuffer::Hint   hint;
		RendererInstanceBuffer::Format semanticFormats[RendererInstanceBuffer::NUM_SEMANTICS];

		PxU32								maxInstances;

		///mark this buffer can be read back by lock, lock flag should not be discard
		bool								canReadBack;

		bool								registerInCUDA;
		physx::PxCudaContextManager *interopContext;

	public:
		RendererInstanceBufferDesc(void);

		bool isValid(void) const;
	};

} // namespace SampleRenderer

#endif
