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

#ifndef SAMPLEVEHICLE_WHEELQUERYRESULTS_H
#define SAMPLEVEHICLE_WHEELQUERYRESULTS_H

#include "vehicle/PxVehicleSDK.h"
#include "vehicle/PxVehicleUpdate.h"

using namespace physx;

//Data structure to store reports for each wheel. 
class SampleVehicleWheelQueryResults
{
public:

	//Allocate a buffer of wheel query results for up to maxNumWheels.
	static SampleVehicleWheelQueryResults* allocate(const PxU32 maxNumWheels);

	//Free allocated buffer.
	void free();

	PxWheelQueryResult* addVehicle(const PxU32 numWheels);

private:

	//One result for each wheel.
	PxWheelQueryResult* mWheelQueryResults;

	//Maximum number of wheels.
	PxU32 mMaxNumWheels;

	//Number of wheels 
	PxU32 mNumWheels;


	SampleVehicleWheelQueryResults()
		: mWheelQueryResults(NULL),mMaxNumWheels(0), mNumWheels(0)
	{
		init();
	}

	~SampleVehicleWheelQueryResults()
	{
	}

	void init()
	{
		mWheelQueryResults=NULL;
		mMaxNumWheels=0;
		mNumWheels=0;
	}
};


#endif //SAMPLEVEHICLE_WHEELQUERYRESULTS_H
