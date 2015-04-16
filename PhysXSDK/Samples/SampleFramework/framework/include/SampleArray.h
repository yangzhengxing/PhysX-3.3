/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef SAMPLEFRAMEWORK_ARRAY
#define SAMPLEFRAMEWORK_ARRAY

#include "PsArray.h"
#include "PsInlineArray.h"
#include "PsHashMap.h"
#include "PsAllocator.h"

namespace SampleFramework
{
	template<typename T>
	class Array : public physx::shdfnd::Array<T, physx::shdfnd::RawAllocator>
	{
	public:
		PX_INLINE explicit Array() : physx::shdfnd::Array<T, physx::shdfnd::RawAllocator>() {}		
		PX_INLINE explicit Array(physx::PxU32 size, const T& a = T()) : physx::shdfnd::Array<T, physx::shdfnd::RawAllocator>(size, a) {}		
	};
}


#endif
