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

#ifndef SAMPLE_CCT_JUMP_H
#define SAMPLE_CCT_JUMP_H

#include "common/PxPhysXCommonConfig.h"
#include "SampleAllocator.h"

using namespace physx;

	class Jump : public SampleAllocateable
	{
		public:
					Jump();

		PxF32		mV0;
		PxF32		mJumpTime;
		bool		mJump;

		void		startJump(PxF32 v0);
		void		stopJump();
		PxF32		getHeight(PxF32 elapsedTime);
	};

#endif
