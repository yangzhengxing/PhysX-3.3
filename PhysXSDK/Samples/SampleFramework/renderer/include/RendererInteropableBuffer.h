/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_INTEROPABLE_BUFFER_H
#define RENDERER_INTEROPABLE_BUFFER_H

#include <RendererConfig.h>

typedef struct CUgraphicsResource_st *CUgraphicsResource;

namespace SampleRenderer
{

	class RendererInteropableBuffer
	{
	public:
		RendererInteropableBuffer(bool mustBeRegistered, physx::PxCudaContextManager *interopContext)
			: m_mustBeRegisteredInCUDA(mustBeRegistered)
			, m_registeredInCUDA(false)
			, m_interopContext(interopContext)			
			, m_InteropHandle(NULL)
			
		{
		}

		bool getInteropResourceHandle(CUgraphicsResource &handle)
		{
			if(m_registeredInCUDA && m_InteropHandle)
			{
				handle = m_InteropHandle;

				return true;
			}

			return false;
		}

	protected:

		bool		 m_mustBeRegisteredInCUDA;
		bool		 m_registeredInCUDA;
		physx::PxCudaContextManager *m_interopContext;
		CUgraphicsResource	m_InteropHandle;
	};

} // namespace SampleRenderer

#endif
