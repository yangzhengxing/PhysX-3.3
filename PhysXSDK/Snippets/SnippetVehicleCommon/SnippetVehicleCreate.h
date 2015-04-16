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

#ifndef SNIPPET_VEHICLE_COMMON_H
#define SNIPPET_VEHICLE_COMMON_H

#include "PxPhysicsAPI.h"
#include "vehicle/PxVehicleDriveTank.h"
#include "vehicle/PxVehicleNoDrive.h"

using namespace physx;

////////////////////////////////////////////////

PxRigidStatic* createDrivablePlane(physx::PxMaterial* material, PxPhysics* physics);

////////////////////////////////////////////////

PxConvexMesh* createChassisMesh(const PxVec3 dims, PxPhysics& physics, PxCooking& cooking);

PxConvexMesh* createWheelMesh(const PxF32 width, const PxF32 radius, PxPhysics& physics, PxCooking& cooking);

////////////////////////////////////////////////

PxRigidDynamic* createVehicleActor
(const PxVehicleChassisData& chassisData,
 PxMaterial** wheelMaterials, PxConvexMesh** wheelConvexMeshes, const PxU32 numWheels, 
 PxMaterial** chassisMaterials, PxConvexMesh** chassisConvexMeshes, const PxU32 numChassisMeshes, 
 PxPhysics& physics);

////////////////////////////////////////////////

struct VehicleDesc
{
	PxF32 chassisMass;
	PxVec3 chassisDims;
	PxVec3 chassisMOI;
	PxVec3 chassisCMOffset;
	PxMaterial* chassisMaterial;
	PxF32 wheelMass;
	PxF32 wheelWidth;
	PxF32 wheelRadius;
	PxF32 wheelMOI;
	PxMaterial* wheelMaterial;
	PxU32 numWheels;
};

PxVehicleDrive4W* createVehicle4W(const VehicleDesc& vehDesc, PxPhysics* physics, PxCooking* cooking);

PxVehicleDriveTank* createVehicleTank(const VehicleDesc& vehDesc, PxPhysics* physics, PxCooking* cooking);

PxVehicleNoDrive* createVehicleNoDrive(const VehicleDesc& vehDesc, PxPhysics* physics, PxCooking* cooking);

void customizeVehicleToLengthScale(const PxReal lengthScale, PxRigidDynamic* rigidDynamic, PxVehicleWheelsSimData* wheelsSimData, PxVehicleDriveSimData* driveSimData);

void customizeVehicleToLengthScale(const PxReal lengthScale, PxRigidDynamic* rigidDynamic, PxVehicleWheelsSimData* wheelsSimData, PxVehicleDriveSimData4W* driveSimData);


////////////////////////////////////////////////

#endif //SNIPPET_VEHICLE_COMMON_H
