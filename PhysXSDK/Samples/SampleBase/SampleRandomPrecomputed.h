/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  

#ifndef SAMPLE_RANDOM_PRECOMPUTED_H
#define SAMPLE_RANDOM_PRECOMPUTED_H

#include "common/PxPhysXCommonConfig.h"
#include "foundation/PxAssert.h"

using namespace physx;

class PhysXSample;

class SampleRandomPrecomputed
{
public:

	SampleRandomPrecomputed(PhysXSample& app);
	~SampleRandomPrecomputed();

	PxF32 getRandom() const {return mPrecomputedRandomSequence[(mPrecomputedRandomSequenceCount++) % PRECOMPUTED_RANDOM_SEQUENCE_SIZE];}
	PxF32 getRandomInRange(const PxF32 a, const PxF32 b)
	{
		PX_ASSERT(b>a);
		return a + (b-a)*getRandom();
	}

private:

	enum
	{
		PRECOMPUTED_RANDOM_SEQUENCE_SIZE=65536
	};
	PxF32* mPrecomputedRandomSequence;
	mutable PxU32 mPrecomputedRandomSequenceCount;
};

#endif //SAMPLE_RANDOM_PRECOMPUTED_H
