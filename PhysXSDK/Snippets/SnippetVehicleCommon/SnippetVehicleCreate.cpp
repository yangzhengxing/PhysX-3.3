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

#include <new>
#include "SnippetVehicleCreate.h"
#include "SnippetVehicleRaycast.h"
#include "SnippetVehicleFilterShader.h"
#include "SnippetVehicleTireFriction.h"
#include "PxPhysicsAPI.h"

using namespace physx;

PxRigidStatic* createDrivablePlane(physx::PxMaterial* material, PxPhysics* physics)
{
	//Add a plane to the scene.
	PxRigidStatic* groundPlane = PxCreatePlane(*physics, PxPlane(0,1,0,0), *material);

	//Get the plane shape so we can set query and simulation filter data.
	PxShape* shapes[1];
	groundPlane->getShapes(shapes, 1);

	//Set the query filter data of the ground plane so that the vehicle raycasts can hit the ground.
	physx::PxFilterData qryFilterData;
	setupDrivableSurface(qryFilterData);
	shapes[0]->setQueryFilterData(qryFilterData);

	//Set the simulation filter data of the ground plane so that it collides with the chassis of a vehicle but not the wheels.
	PxFilterData simFilterData;
	simFilterData.word0 = COLLISION_FLAG_GROUND;
	simFilterData.word1 = COLLISION_FLAG_GROUND_AGAINST;
	shapes[0]->setSimulationFilterData(simFilterData);

	return groundPlane;
}

static PxConvexMesh* createConvexMesh(const PxVec3* verts, const PxU32 numVerts, PxPhysics& physics, PxCooking& cooking)
{
	// Create descriptor for convex mesh
	PxConvexMeshDesc convexDesc;
	convexDesc.points.count			= numVerts;
	convexDesc.points.stride		= sizeof(PxVec3);
	convexDesc.points.data			= verts;
	convexDesc.flags				= PxConvexFlag::eCOMPUTE_CONVEX | PxConvexFlag::eINFLATE_CONVEX;

	PxConvexMesh* convexMesh = NULL;
	PxDefaultMemoryOutputStream buf;
	if(cooking.cookConvexMesh(convexDesc, buf))
	{
		PxDefaultMemoryInputData id(buf.getData(), buf.getSize());
		convexMesh = physics.createConvexMesh(id);
	}

	return convexMesh;
}

PxConvexMesh* createChassisMesh(const PxVec3 dims, PxPhysics& physics, PxCooking& cooking)
{
	const PxF32 x = dims.x*0.5f;
	const PxF32 y = dims.y*0.5f;
	const PxF32 z = dims.z*0.5f;
	PxVec3 verts[8] =
	{
		PxVec3(x,y,-z), 
		PxVec3(x,y,z),
		PxVec3(x,-y,z),
		PxVec3(x,-y,-z),
		PxVec3(-x,y,-z), 
		PxVec3(-x,y,z),
		PxVec3(-x,-y,z),
		PxVec3(-x,-y,-z)
	};

	return createConvexMesh(verts,8,physics,cooking);
}

PxConvexMesh* createWheelMesh(const PxF32 width, const PxF32 radius, PxPhysics& physics, PxCooking& cooking)
{
	PxVec3 points[2*16];
	for(PxU32 i = 0; i < 16; i++)
	{
		const PxF32 cosTheta = PxCos(i*PxPi*2.0f/16.0f);
		const PxF32 sinTheta = PxSin(i*PxPi*2.0f/16.0f);
		const PxF32 y = radius*cosTheta;
		const PxF32 z = radius*sinTheta;
		points[2*i+0] = PxVec3(-width/2.0f, y, z);
		points[2*i+1] = PxVec3(+width/2.0f, y, z);
	}

	return createConvexMesh(points,32,physics,cooking);
}

PxRigidDynamic* createVehicleActor
(const PxVehicleChassisData& chassisData,
 PxMaterial** wheelMaterials, PxConvexMesh** wheelConvexMeshes, const PxU32 numWheels, 
 PxMaterial** chassisMaterials, PxConvexMesh** chassisConvexMeshes, const PxU32 numChassisMeshes, 
 PxPhysics& physics)
{
	//We need a rigid body actor for the vehicle.
	//Don't forget to add the actor to the scene after setting up the associated vehicle.
	PxRigidDynamic* vehActor = physics.createRigidDynamic(PxTransform(PxIdentity));

	//Wheel and chassis simulation filter data.
	PxFilterData wheelSimFilterData;
	wheelSimFilterData.word0 = COLLISION_FLAG_WHEEL;
	wheelSimFilterData.word1 = COLLISION_FLAG_WHEEL_AGAINST;
	PxFilterData chassisSimFilterData;
	chassisSimFilterData.word0 = COLLISION_FLAG_CHASSIS;
	chassisSimFilterData.word1 = COLLISION_FLAG_CHASSIS_AGAINST;

	//Wheel and chassis query filter data.
	//Optional: cars don't drive on other cars.
	PxFilterData wheelQryFilterData;
	setupNonDrivableSurface(wheelQryFilterData);
	PxFilterData chassisQryFilterData;
	setupNonDrivableSurface(chassisQryFilterData);

	//Add all the wheel shapes to the actor.
	for(PxU32 i = 0; i < numWheels; i++)
	{
		PxConvexMeshGeometry geom(wheelConvexMeshes[i]);
		PxShape* wheelShape=vehActor->createShape(geom, *wheelMaterials[i]);
		wheelShape->setQueryFilterData(wheelQryFilterData);
		wheelShape->setSimulationFilterData(wheelSimFilterData);
		wheelShape->setLocalPose(PxTransform(PxIdentity));
	}

	//Add the chassis shapes to the actor.
	for(PxU32 i = 0; i < numChassisMeshes; i++)
	{
		PxShape* chassisShape=vehActor->createShape
			(PxConvexMeshGeometry(chassisConvexMeshes[i]),*chassisMaterials[i]);
		chassisShape->setQueryFilterData(chassisQryFilterData);
		chassisShape->setSimulationFilterData(chassisSimFilterData);
		chassisShape->setLocalPose(PxTransform(PxIdentity));
	}

	vehActor->setMass(chassisData.mMass);
	vehActor->setMassSpaceInertiaTensor(chassisData.mMOI);
	vehActor->setCMassLocalPose(PxTransform(chassisData.mCMOffset,PxQuat(PxIdentity)));

	return vehActor;
}

void customizeVehicleToLengthScale(const PxReal lengthScale, PxRigidDynamic* rigidDynamic, PxVehicleWheelsSimData* wheelsSimData, PxVehicleDriveSimData* driveSimData)
{
	//Rigid body center of mass and moment of inertia.
	{
		PxTransform t = rigidDynamic->getCMassLocalPose();
		t.p *= lengthScale;
		rigidDynamic->setCMassLocalPose(t);

		PxVec3 moi = rigidDynamic->getMassSpaceInertiaTensor();
		moi *= (lengthScale*lengthScale);
		rigidDynamic->setMassSpaceInertiaTensor(moi);
	}

	//Wheels, suspensions, wheel centers, tire/susp force application points.
	{
		for(PxU32 i = 0; i < wheelsSimData->getNbWheels(); i++)
		{
			PxVehicleWheelData wheelData = wheelsSimData->getWheelData(i);
			wheelData.mRadius *= lengthScale;
			wheelData.mWidth *= lengthScale;
			wheelData.mDampingRate *= lengthScale*lengthScale;
			wheelData.mMaxBrakeTorque *= lengthScale*lengthScale;
			wheelData.mMaxHandBrakeTorque *= lengthScale*lengthScale;
			wheelData.mMOI *= lengthScale*lengthScale;
			wheelsSimData->setWheelData(i, wheelData);

			PxVehicleSuspensionData suspData = wheelsSimData->getSuspensionData(i);
			suspData.mMaxCompression *= lengthScale;
			suspData.mMaxDroop *= lengthScale;
			wheelsSimData->setSuspensionData(i, suspData);

			PxVec3 v = wheelsSimData->getWheelCentreOffset(i);
			v *= lengthScale;
			wheelsSimData->setWheelCentreOffset(i,v);

			v = wheelsSimData->getSuspForceAppPointOffset(i);
			v *= lengthScale;
			wheelsSimData->setSuspForceAppPointOffset(i,v);

			v = wheelsSimData->getTireForceAppPointOffset(i);
			v *= lengthScale;
			wheelsSimData->setTireForceAppPointOffset(i,v);
		}
	}

	//Slow forward speed correction.
	{
		wheelsSimData->setSubStepCount(5.0f*lengthScale, 3, 1);
		wheelsSimData->setMinLongSlipDenominator(4.0f*lengthScale);
	}

	//Engine
	if(driveSimData)
	{
		PxVehicleEngineData engineData = driveSimData->getEngineData();
		engineData.mMOI *= lengthScale*lengthScale;
		engineData.mPeakTorque *= lengthScale*lengthScale;
		engineData.mDampingRateFullThrottle *= lengthScale*lengthScale;
		engineData.mDampingRateZeroThrottleClutchEngaged *= lengthScale*lengthScale;
		engineData.mDampingRateZeroThrottleClutchDisengaged *= lengthScale*lengthScale;
		driveSimData->setEngineData(engineData);
	}

	//Clutch.
	if(driveSimData)
	{
		PxVehicleClutchData clutchData = driveSimData->getClutchData();
		clutchData.mStrength *= lengthScale*lengthScale;
		driveSimData->setClutchData(clutchData);
	}	

	//Scale the collision meshes too.
	{
		PxShape* shapes[16];
		const PxU32 nbShapes = rigidDynamic->getShapes(shapes, 16);
		for(PxU32 i = 0; i < nbShapes; i++)
		{
			switch(shapes[i]->getGeometryType())
			{
			case PxGeometryType::eSPHERE:
				{
					PxSphereGeometry sphere;
					shapes[i]->getSphereGeometry(sphere);
					sphere.radius *= lengthScale;
					shapes[i]->setGeometry(sphere);
				}
				break;
			case PxGeometryType::ePLANE:
				PX_ASSERT(false);
				break;
			case PxGeometryType::eCAPSULE:
				{
					PxCapsuleGeometry capsule;
					shapes[i]->getCapsuleGeometry(capsule);
					capsule.radius *= lengthScale;
					capsule.halfHeight*= lengthScale;
					shapes[i]->setGeometry(capsule);
				}
				break;
			case PxGeometryType::eBOX:
				{
					PxBoxGeometry box;
					shapes[i]->getBoxGeometry(box);
					box.halfExtents *= lengthScale;
					shapes[i]->setGeometry(box);
				}
				break;
			case PxGeometryType::eCONVEXMESH:
				{
					PxConvexMeshGeometry convexMesh;
					shapes[i]->getConvexMeshGeometry(convexMesh);
					convexMesh.scale.scale *= lengthScale;
					shapes[i]->setGeometry(convexMesh);
				}
				break;
			case PxGeometryType::eTRIANGLEMESH:
				{
					PxTriangleMeshGeometry triMesh;
					shapes[i]->getTriangleMeshGeometry(triMesh);
					triMesh.scale.scale *= lengthScale;
					shapes[i]->setGeometry(triMesh);
				}
				break;
			case PxGeometryType::eHEIGHTFIELD:
				{
					PxHeightFieldGeometry hf;
					shapes[i]->getHeightFieldGeometry(hf);
					hf.columnScale *= lengthScale;
					hf.heightScale *= lengthScale;
					hf.rowScale *= lengthScale;
					shapes[i]->setGeometry(hf);
				}
				break;
			case PxGeometryType::eINVALID:
			case PxGeometryType::eGEOMETRY_COUNT:
				break;
			}
		}
	}
}

void customizeVehicleToLengthScale(const PxReal lengthScale, PxRigidDynamic* rigidDynamic, PxVehicleWheelsSimData* wheelsSimData, PxVehicleDriveSimData4W* driveSimData)
{
	customizeVehicleToLengthScale(lengthScale, rigidDynamic, wheelsSimData, (PxVehicleDriveSimData*)driveSimData);

	//Ackermann geometry.
	if(driveSimData)
	{
		PxVehicleAckermannGeometryData ackermannData = driveSimData->getAckermannGeometryData();
		ackermannData.mAxleSeparation *= lengthScale;
		ackermannData.mFrontWidth *= lengthScale;
		ackermannData.mRearWidth *= lengthScale;
		driveSimData->setAckermannGeometryData(ackermannData);
	}
}


