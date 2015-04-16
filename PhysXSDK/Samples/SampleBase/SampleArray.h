/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef SAMPLE_ARRAY
#define SAMPLE_ARRAY

#include "PsArray.h"
#include "PsInlineArray.h"
#include "PsHashMap.h"
#include "PsAllocator.h"
#include "Test.h"


template<typename T>
class SampleArray : public Ps::Array<T, Ps::RawAllocator>
{
public:
	PX_INLINE explicit SampleArray() : Ps::Array<T, Ps::RawAllocator>() {}		
	PX_INLINE explicit SampleArray(PxU32 size, const T& a = T()) : Ps::Array<T, Ps::RawAllocator>(size, a) {}		
};


template<typename T, PxU32 N>
class SampleInlineArray : public Ps::InlineArray<T, N, Ps::RawAllocator> {};


#endif
