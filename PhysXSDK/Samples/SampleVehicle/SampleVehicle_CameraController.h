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


#ifndef SAMPLE_VEHICLE_CAMERA_CONTROLLER_H
#define SAMPLE_VEHICLE_CAMERA_CONTROLLER_H

#include "common/PxPhysXCommonConfig.h"
#include "foundation/PxVec3.h"
#include "foundation/PxTransform.h"

using namespace physx;

namespace physx
{
	class PxScene;
	class PxVehicleWheels;
	class PxRigidDynamic;
}

class Camera;

class SampleVehicle_CameraController 
{
public:

	SampleVehicle_CameraController();
	~SampleVehicle_CameraController();

	void setInputs(const PxF32 rotateInputY, const PxF32 rotateInputZ)
	{
		mRotateInputY=rotateInputY;
		mRotateInputZ=rotateInputZ;
	}

	void update(const PxF32 dtime, const PxVehicleWheels& focusVehicle, PxScene& scene);

	void restart() {}

	bool getIsLockedOnVehicleTransform() const {return mLockOnFocusVehTransform;}
	void toggleLockOnVehTransform() {mLockOnFocusVehTransform = !mLockOnFocusVehTransform;}
	
	const PxVec3& getCameraPos() const {return mCameraPos;}
	const PxVec3& getCameraTar() const {return mCameraTargetPos;}

private:

	PxF32			mRotateInputY;
	PxF32			mRotateInputZ;

	PxF32			mMaxCameraRotateSpeed;
	PxF32			mCameraRotateAngleY;
	PxF32			mCameraRotateAngleZ;
	PxVec3			mCameraPos;
	PxVec3			mCameraTargetPos;
	PxVec3			mLastCarPos;
	PxVec3			mLastCarVelocity;
	bool			mCameraInit;

	bool			mLockOnFocusVehTransform;
	PxTransform		mLastFocusVehTransform;

	void update(const PxReal dtime, const PxRigidDynamic* actor, PxScene& scene);
};

#endif //SAMPLE_VEHICLE_CAMERA_CONTROLLER_H