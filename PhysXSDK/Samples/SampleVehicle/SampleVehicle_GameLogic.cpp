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

#include "SampleVehicle_GameLogic.h"

void SampleVehicleWayPoints::getNextWayPointsAndLineDirs(PxU32& numPoints, PxVec3& v0, PxVec3& v1, PxVec3& v2, PxVec3& w0, PxVec3& w1, PxVec3& w2) const
{
	numPoints=0;
	if((mProgress+1) < mNumWayPoints)
	{
		v0=mWayPoints[mProgress+1].p;
		w0=mWayPoints[mProgress+1].q.getBasisVector0();
		numPoints++;

		if((mProgress+2) < mNumWayPoints)
		{
			v1=mWayPoints[mProgress+2].p;
			w1=mWayPoints[mProgress+2].q.getBasisVector0();
			numPoints++;

			if((mProgress+3) < mNumWayPoints)
			{
				v2=mWayPoints[mProgress+3].p;
				w2=mWayPoints[mProgress+3].q.getBasisVector0();
				numPoints++;
			}
		}
	}
}

#define LINEWIDTH 8
#define LINEDISTANCE2 3*3
void SampleVehicleWayPoints::update(const PxTransform& playerTransform, const PxF32 timestep)
{
	//Increment the elapsed time
	mTimeElapsed+=timestep;

	//Work out the point on the crossing line of the next way-point that is closest to the player.
	const PxTransform& nextWayPoint=mWayPoints[mProgress+1];
	const PxVec3 v=nextWayPoint.p;
	const PxVec3 w=nextWayPoint.q.getBasisVector0();
	const PxVec3 p=playerTransform.p;
	const PxVec3 pv=p-v;
	const PxF32 t=pv.dot(w);

	//Test if the player's position is inside the width of the line crossing the next way-point.
	if(PxAbs(t) < LINEWIDTH)
	{
		//Now test if the shortest distance to the next crossing line is smaller than a threshold.
		const PxVec3 linePos=v+w*t;
		const PxVec3 diff=p-linePos;
		const PxF32 dist2=diff.magnitudeSquared();
		if(dist2<LINEDISTANCE2)
		{
			mProgress++;
		}
	}

	if(mProgress == mNumWayPoints-1)
	{
		mMinTimeElapsed=PxMin(mTimeElapsed, mMinTimeElapsed);
		mTimeElapsed=0;
		mProgress=0;
	}
}
