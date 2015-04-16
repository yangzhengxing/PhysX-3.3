/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_INDEXBUFFER_DESC_H
#define RENDERER_INDEXBUFFER_DESC_H

#include <RendererIndexBuffer.h>

namespace SampleRenderer
{

	class RendererIndexBufferDesc
	{
	public:
		RendererIndexBuffer::Hint          hint;
		RendererIndexBuffer::Format        format;

		PxU32                              maxIndices;

		///mark this buffer can be read back by lock, lock flag should not be discard
		bool								canReadBack;
		///choose if the resource must be registered in CUDA upon creation
		bool                               registerInCUDA;
		///This context must be used to register and unregister the resource everytime the device is lost and recreated
		physx::PxCudaContextManager *interopContext;  

	public:
		RendererIndexBufferDesc(void);

		bool isValid(void) const;
	};

} // namespace SampleRenderer

#endif
