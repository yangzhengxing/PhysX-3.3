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

#ifndef SNIPPET_VEHICLE_CONCURRENCY_H
#define SNIPPET_VEHICLE_CONCURRENCY_H

#include "PxPhysicsAPI.h"
#include <new>

using namespace physx;

//Data structure for quick setup of wheel query data structures.
class VehicleConcurrency
{
public:

	VehicleConcurrency()
		: mMaxNumVehicles(0),
		  mMaxNumWheelsPerVehicle(0),
		  mVehicleConcurrentUpdates(NULL)
	{
	}

	~VehicleConcurrency()
	{
	}

	static VehicleConcurrency* allocate(const PxU32 maxNumVehicles, const PxU32 maxNumWheelsPerVehicle, PxAllocatorCallback& allocator)
	{
		const PxU32 byteSize = 
			sizeof(VehicleConcurrency) + 
			sizeof(PxVehicleConcurrentUpdateData)*maxNumVehicles + 
			sizeof(PxVehicleWheelConcurrentUpdateData)*maxNumWheelsPerVehicle*maxNumVehicles;

		PxU8* buffer = (PxU8*)allocator.allocate(byteSize, NULL, NULL, 0);

		VehicleConcurrency* vc = (VehicleConcurrency*)buffer;
		new(vc) VehicleConcurrency();
		buffer += sizeof(VehicleConcurrency);

		vc->mMaxNumVehicles = maxNumVehicles;
		vc->mMaxNumWheelsPerVehicle = maxNumWheelsPerVehicle;

		vc->mVehicleConcurrentUpdates = (PxVehicleConcurrentUpdateData*)buffer;
		buffer += sizeof(PxVehicleConcurrentUpdateData)*maxNumVehicles;

		for(PxU32 i=0;i<maxNumVehicles;i++)
		{
			new(vc->mVehicleConcurrentUpdates + i) PxVehicleConcurrentUpdateData();
			
			vc->mVehicleConcurrentUpdates[i].nbConcurrentWheelUpdates = maxNumWheelsPerVehicle;
			
			vc->mVehicleConcurrentUpdates[i].concurrentWheelUpdates = (PxVehicleWheelConcurrentUpdateData*)buffer;
			buffer += sizeof(PxVehicleWheelConcurrentUpdateData)*maxNumWheelsPerVehicle;

			for(PxU32 j = 0; j < maxNumWheelsPerVehicle; j++)
			{
				new(vc->mVehicleConcurrentUpdates[i].concurrentWheelUpdates + j) PxVehicleWheelConcurrentUpdateData();
			}

		}


		return vc;
	}

	//Free allocated buffer for scene queries of suspension raycasts.
	void free(PxAllocatorCallback& allocator)
	{
		allocator.deallocate(this);
	}

	//Return the PxVehicleConcurrentUpdate for a vehicle specified by an index.
	PxVehicleConcurrentUpdateData* getVehicleConcurrentUpdate(const PxU32 id)
	{
		return (mVehicleConcurrentUpdates + id);
	}

	//Return the entire array of PxVehicleConcurrentUpdates
	PxVehicleConcurrentUpdateData* getVehicleConcurrentUpdateBuffer()
	{
		return mVehicleConcurrentUpdates;
	}

private:

	PxU32 mMaxNumVehicles;
	PxU32 mMaxNumWheelsPerVehicle;
	PxVehicleConcurrentUpdateData* mVehicleConcurrentUpdates;
};


#endif //SNIPPET_VEHICLE_CONCURRENCY_H
