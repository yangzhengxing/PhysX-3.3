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

#ifndef SNIPPET_VEHICLE_WHEELQUERYRESULT_H
#define SNIPPET_VEHICLE_WHEELQUERYRESULT_H

#include "PxPhysicsAPI.h"
#include <new>

using namespace physx;

//Data structure for quick setup of wheel query data structures.
class VehicleWheelQueryResults
{
public:

	VehicleWheelQueryResults()
		: mVehicleWheelQueryResults(NULL)
	{
	}

	~VehicleWheelQueryResults()
	{
	}

	//Allocate wheel results for up to maxNumVehicles with up to maxNumWheelsPerVehicle.
	static VehicleWheelQueryResults* allocate(const PxU32 maxNumVehicles, const PxU32 maxNumWheelsPerVehicle, PxAllocatorCallback& allocator)
	{
		const PxU32 byteSize = sizeof(VehicleWheelQueryResults) + sizeof(PxVehicleWheelQueryResult)*maxNumVehicles + sizeof(PxWheelQueryResult)*maxNumWheelsPerVehicle*maxNumVehicles;

		PxU8* buffer = (PxU8*)allocator.allocate(byteSize, NULL, NULL, 0);

		VehicleWheelQueryResults* vwqr = (VehicleWheelQueryResults*)buffer;
		buffer += sizeof(VehicleWheelQueryResults);

		vwqr->mVehicleWheelQueryResults = (PxVehicleWheelQueryResult*)buffer;
		buffer+=sizeof(PxVehicleWheelQueryResult)*maxNumVehicles;

		for(PxU32 i=0;i<maxNumVehicles;i++)
		{
			new(buffer) PxWheelQueryResult();
			vwqr->mVehicleWheelQueryResults[i].wheelQueryResults = (PxWheelQueryResult*)buffer;
			vwqr->mVehicleWheelQueryResults[i].nbWheelQueryResults = maxNumWheelsPerVehicle;
			buffer += sizeof(PxWheelQueryResult)*maxNumWheelsPerVehicle;
		}

		return vwqr;
	}

	//Free allocated buffer for scene queries of suspension raycasts.
	void free(PxAllocatorCallback& allocator)
	{
		allocator.deallocate(this);
	}

	//Return the PxVehicleWheelQueryResult for a vehicle specified by an index.
	PxVehicleWheelQueryResult* getVehicleWheelQueryResults(const PxU32 id)
	{
		return (mVehicleWheelQueryResults + id);
	}

private:

	PxVehicleWheelQueryResult* mVehicleWheelQueryResults;
};


#endif //SNIPPET_VEHICLE_WHEELQUERYRESULT_H
