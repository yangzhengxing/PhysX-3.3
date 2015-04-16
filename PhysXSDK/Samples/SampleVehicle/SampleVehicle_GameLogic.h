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


#ifndef SAMPLE_VEHICLE_GAME_LOGIC_H
#define SAMPLE_VEHICLE_GAME_LOGIC_H

#include "common/PxPhysXCommonConfig.h"
#include "foundation/PxTransform.h"

using namespace physx;

class SampleVehicleWayPoints
{
public:

	SampleVehicleWayPoints()
		: mWayPoints(NULL),
		mNumWayPoints(0),
		mProgress(0),
		mTimeElapsed(0),
		mMinTimeElapsed(100000)
	{
	}

	~SampleVehicleWayPoints()
	{
	}

	//Setup.
	void setWayPoints(const PxTransform* wayPoints, const PxU32 numWayPoints) 
	{
		mWayPoints=wayPoints; 
		mNumWayPoints=numWayPoints;
	}

	//Update.
	void update(const PxTransform& playerTransform, const PxF32 timestep);

	//Imagine we are starting the lap again.
	PxTransform setBackAtStart()
	{
		mTimeElapsed=0;
		mProgress=0;
		return mWayPoints[0];
	}

	//Get the next three points and the crossing line of each way-point.
	void getNextWayPointsAndLineDirs(PxU32& numPoints, PxVec3& v0, PxVec3& v1, PxVec3& v2, PxVec3& w0, PxVec3& w1, PxVec3& w2) const;

	//Get lap time and best lap time.
	PxF32 getTimeElapsed() const {return mTimeElapsed;}
	PxF32 getMinTimeElapsed() const {return mMinTimeElapsed;}

	//Get the transform to reset the car at the last passed way-point.
	PxTransform getResetTransform() const {return mWayPoints[mProgress];}

private:

	//Array of way points.
	const PxTransform* mWayPoints;
	PxU32 mNumWayPoints;

	//Progress and time elapsed.
	PxU32 mProgress;
	PxF32 mTimeElapsed;
	PxF32 mMinTimeElapsed;
};


#endif //SAMPLE_VEHICLE_GAME_LOGIC_H