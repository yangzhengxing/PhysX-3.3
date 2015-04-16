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

#ifndef SAMPLE_UTILS_H
#define SAMPLE_UTILS_H

#include "common/PxPhysXCommonConfig.h"
#include "foundation/PxVec3.h"
#include "PsMathUtils.h"

	//Integer representation of a floating-point value.
	#define PX_IR(x)			((PxU32&)(x))

	// PT: TODO: move those helpers to a shared place, this is also used in the SDK

	PX_INLINE PxReal degtorad(PxReal d)
	{
		return d * PxPi / 180.0f;
	}

#endif
