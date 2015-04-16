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

#include "SampleVehicle_WheelQueryResults.h"
#include "vehicle/PxVehicleSDK.h"
#include "PsFoundation.h"
#include "PsUtilities.h"


//#define CHECK_MSG(exp, msg) (!!(exp) || (physx::shdfnd::getFoundation().error(physx::PxErrorCode::eINVALID_PARAMETER, __FILE__, __LINE__, msg), 0) )


SampleVehicleWheelQueryResults* SampleVehicleWheelQueryResults::allocate(const PxU32 maxNumWheels)
{
	const PxU32 size = sizeof(SampleVehicleWheelQueryResults) + sizeof(PxWheelQueryResult)*maxNumWheels;
	SampleVehicleWheelQueryResults* resData = (SampleVehicleWheelQueryResults*)PX_ALLOC(size, PX_DEBUG_EXP("SampleVehicleWheelQueryResults"));
	resData->init();
	PxU8* ptr = (PxU8*) resData;
	ptr += sizeof(SampleVehicleWheelQueryResults);
	resData->mWheelQueryResults = (PxWheelQueryResult*)ptr;
	ptr +=  sizeof(PxWheelQueryResult)*maxNumWheels;
	resData->mMaxNumWheels=maxNumWheels;
	for(PxU32 i=0;i<maxNumWheels;i++)
	{
		new(&resData->mWheelQueryResults[i]) PxWheelQueryResult();
	}
	return resData;
}

void SampleVehicleWheelQueryResults::free()
{
	PX_FREE(this);
}

PxWheelQueryResult* SampleVehicleWheelQueryResults::addVehicle(const PxU32 numWheels)
{
	PX_ASSERT((mNumWheels + numWheels) <= mMaxNumWheels);
	PxWheelQueryResult* r = &mWheelQueryResults[mNumWheels];
	mNumWheels += numWheels;
	return r;
}






