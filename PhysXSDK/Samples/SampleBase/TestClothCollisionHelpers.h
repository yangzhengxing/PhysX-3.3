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

#ifndef WRAP_CLOTH_H
#define WRAP_CLOTH_H

//----------------------------------------------------------------------------//
#include "PxPhysicsAPI.h"
#include "TestArray.h"
#include "TestMotionGenerator.h"

#include "cloth/PxCloth.h"

#include "PhysXSample.h"

//----------------------------------------------------------------------------//

namespace physx
{
	class PxClothMeshDesc;
	class PxClothFabric;
}

namespace Test
{
    // wrapper for collision data for cloth
    class ClothCollision 
    {
    public:
		friend class ::RenderClothActor;
        ClothCollision();

        // Test::ClothCollision
        virtual PxU32 addSphere(const PxVec3& position, PxReal radius);
        virtual PxU32 addCapsuleIndex(PxU32 i0, PxU32 i1);
		virtual PxU32 addCapsule(const PxVec3& position1, PxReal radius1, const PxVec3& position2, PxReal radius2);
		virtual PxU32 getNbSpheres() const;
		virtual PxU32 getNbCapsules() const;

		virtual PxBounds3 getWorldBounds() const; 
		virtual const PxClothCollisionSphere* getSpheres() const;
		virtual const PxU32* getCapsules() const;

		virtual void setClothPose(const PxTransform &clothPose);
        virtual void setCapsuleMotion(PxU32 id, const PxVec3 &linear, const PxVec3 &angular);
		virtual void setSphereMotion(PxU32 id, const PxVec3 &linear);
        virtual void updateMotion(PxReal time, PxReal timestep);

		virtual void release();

        
		virtual ~ClothCollision();
    protected:
        // convert sphere positions to local pose of cloth
        void applyLocalTransform();

    protected:
		PxTransform mClothPose;
		Test::Array<PxVec3> mOrigPositions;
		Test::Array<PxVec3> mWorldPositions;
		Test::Array<PxClothCollisionSphere> mSpheres;
		Test::Array<MotionGenerator> mSphereMotion;
		Test::Array<MotionGenerator> mCapsuleMotion;
		Test::Array<PxU32> mCapsuleIndices;
	};
}


//----------------------------------------------------------------------------//

#endif // WRAP_CLOTH_H

