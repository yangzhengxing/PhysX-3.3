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

#ifndef SNIPPET_VEHICLE_RAYCAST_H
#define SNIPPET_VEHICLE_RAYCAST_H

#include "PxPhysicsAPI.h"

using namespace physx;

enum
{
	DRIVABLE_SURFACE = 0xffff0000,
	UNDRIVABLE_SURFACE = 0x0000ffff
};

void setupDrivableSurface(PxFilterData& filterData);

void setupNonDrivableSurface(PxFilterData& filterData);

PxQueryHitType::Enum WheelRaycastPreFilter
(PxFilterData filterData0, PxFilterData filterData1,
 const void* constantBlock, PxU32 constantBlockSize,
 PxHitFlags& queryFlags);

//Data structure for quick setup of scene queries for suspension raycasts.
class VehicleSceneQueryData
{
public:
	VehicleSceneQueryData();
	~VehicleSceneQueryData();

	//Allocate scene query data for up to maxNumVehicles and up to maxNumWheelsPerVehicle with numVehiclesInBatch per batch query.
	static VehicleSceneQueryData* allocate(const PxU32 maxNumVehicles, const PxU32 maxNumWheelsPerVehicle, const PxU32 numVehiclesInBatch, PxAllocatorCallback& allocator);

	//Free allocated buffers.
	void free(PxAllocatorCallback& allocator);

	//Create a PxBatchQuery instance that will be used for a single specified batch.
	static PxBatchQuery* setUpBatchedSceneQuery(const PxU32 batchId, const VehicleSceneQueryData& vehicleSceneQueryData, PxScene* scene);

	//Return an array of scene query results for a single specified batch.
	PxRaycastQueryResult* getRaycastQueryResultBuffer(const PxU32 batchId); 

	//Get the number of scene query results that have been allocated for a single batch.
	PxU32 getRaycastQueryResultBufferSize() const; 

private:

	//Number of raycasts per batch
	PxU32 mNumRaycastsPerBatch;

	//One result for each wheel.
	PxRaycastQueryResult* mSqResults;

	//One hit for each wheel.
	PxRaycastHit* mSqHitBuffer;

	//Filter shader used to filter drivable and non-drivable surfaces
	PxBatchQueryPreFilterShader mPreFilterShader;
};


#endif //SNIPPET_VEHICLE_RAYCAST_H
