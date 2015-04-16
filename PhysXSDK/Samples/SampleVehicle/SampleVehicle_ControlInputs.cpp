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

#include "SampleVehicle_ControlInputs.h"
#include "PhysXSampleApplication.h"

using namespace SampleRenderer;
using namespace SampleFramework;

///////////////////////////////////////////////////////////////////////////////

SampleVehicle_ControlInputs::SampleVehicle_ControlInputs()
:	mCameraRotateInputY			(0.0f),
	mCameraRotateInputZ			(0.0f),
	mAccelKeyPressed			(false),
	mGearUpKeyPressed			(false),
	mGearDownKeyPressed			(false),
	mBrakeKeyPressed			(false),
	mHandbrakeKeyPressed		(false),
	mSteerLeftKeyPressed		(false),
	mSteerRightKeyPressed		(false),
	mBrakeLeftKeyPressed		(false),
	mBrakeRightKeyPressed		(false),
	mThrustLeftKeyPressed		(false),
	mThrustRightKeyPressed		(false),
	mAccel						(0.0f),
	mGearup						(false),
	mGeardown					(false),
	mBrake						(0.0f),
	mSteer						(0.0f),
	mHandbrake					(false),
	mThrustLeft					(0.0f),
	mThrustRight				(0.0f),
	mBrakeLeft					(0.0f),
	mBrakeRight					(0.0f)
{
}

SampleVehicle_ControlInputs::~SampleVehicle_ControlInputs()
{
}

