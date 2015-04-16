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

#ifndef SAMPLE_CHARACTER_CAMERA_CONTROLLER_H
#define SAMPLE_CHARACTER_CAMERA_CONTROLLER_H

#include "SampleCameraController.h"

#include "characterkinematic/PxController.h"

class SampleCharacterCloth;

class SampleCharacterClothCameraController : public CameraController
{
public:
						SampleCharacterClothCameraController(PxController& controlled, SampleCharacterCloth& sample);

	// Implements CameraController
	virtual void		onDigitalInputEvent(const SampleFramework::InputEvent& , bool val);
	virtual void		onAnalogInputEvent(const SampleFramework::InputEvent& , float val);
	virtual void		onPointerInputEvent(const SampleFramework::InputEvent&, physx::PxU32, physx::PxU32, physx::PxReal, physx::PxReal, bool);
	virtual void		collectInputEvents(std::vector<const SampleFramework::InputEvent*>& inputEvents);

	virtual	void		update(Camera& camera, PxReal dtime);

			void        updateFromCCT(PxReal dtime);
			void		setView(PxReal pitch, PxReal yaw);

protected:
	
	Camera*                 mCamera;
	PxController&			mController;
	SampleCharacterCloth&	mSample;

	PxReal					mTargetYaw, mTargetPitch;
	PxReal					mPitchMin,	mPitchMax;

	PxReal					mGamepadPitchInc, mGamepadYawInc;
	PxReal					mGamepadForwardInc, mGamepadLateralInc;
	PxReal					mSensibility;

	bool					mFwd,mBwd,mLeft,mRight,mKeyShiftDown;

	PxReal					mRunningSpeed;
	PxReal					mWalkingSpeed;

private:
	SampleCharacterClothCameraController& operator=(const SampleCharacterClothCameraController&);

};

#endif
