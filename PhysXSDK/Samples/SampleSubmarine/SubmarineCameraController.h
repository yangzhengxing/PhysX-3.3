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


#ifndef SUBMARINE_CAMERA_CONTROLLER_H
#define SUBMARINE_CAMERA_CONTROLLER_H

#include "SampleCameraController.h"

class SubmarineCameraController: public DefaultCameraController
{
public:
	SubmarineCameraController(): mFollowingMode(true) {}
	~SubmarineCameraController(){}

	virtual void update(Camera& camera, PxReal dtime)
	{
		if(!mFollowingMode)
			DefaultCameraController::update(camera, dtime);
	}

	void updateFollowingMode(Camera& camera, PxReal dtime, const PxVec3& targetPos)
	{
		PX_ASSERT(mFollowingMode);
		// default update (orientation)
		DefaultCameraController::update(camera, dtime);

		// put camera behind submarine/crab
		camera.setPos(targetPos - camera.getViewDir()*15.0f);
	}

	void setFollowingMode(bool follow) { mFollowingMode = follow;}

private:
	bool	mFollowingMode;
};

#endif
