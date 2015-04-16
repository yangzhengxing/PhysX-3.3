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

#ifndef VEHICLE_COOKING_H
#define VEHICLE_COOKING_H

#include "PxPhysicsAPI.h"

using namespace physx;


PxConvexMesh* createConvexMesh(const PxVec3* verts, const PxU32 numVerts, PxPhysics& physics, PxCooking& cooking);
PxConvexMesh* createCuboidConvexMesh(const PxVec3& halfExtents, PxPhysics& physics, PxCooking& cooking);
PxConvexMesh* createWedgeConvexMesh(const PxVec3& halfExtents, PxPhysics& physics, PxCooking& cooking);
PxConvexMesh* createCylinderConvexMesh(const PxF32 width, const PxF32 radius, const PxU32 numCirclePoints, PxPhysics& physics, PxCooking& cooking);
PxConvexMesh* createSquashedCuboidMesh(const PxF32 baseLength, const PxF32 baseDepth, const PxF32 height1, const PxF32 height2, PxPhysics& physics, PxCooking& cooking);
PxConvexMesh* createPrismConvexMesh(const PxF32 baseLength, const PxF32 baseDepth, const PxF32 height, PxPhysics& physics, PxCooking& cooking);
PxConvexMesh* createWheelConvexMesh(const PxVec3* verts, const PxU32 numVerts, PxPhysics& physics, PxCooking& cooking);
PxConvexMesh* createChassisConvexMesh(const PxVec3* verts, const PxU32 numVerts, PxPhysics& physics, PxCooking& cooking);


#endif //VEHICLE_COOKING_H
