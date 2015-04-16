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

#include "PhysXSampleApplication.h"
#include "SampleCameraController.h"
#include "characterkinematic/PxController.h"

#define POS_HISTORY_LIMIT	1024

class SampleCustomGravityCameraController : public CameraController
{
	public:
										SampleCustomGravityCameraController(PxController& controlled, SampleCustomGravity& base);

		virtual void					onDigitalInputEvent(const SampleFramework::InputEvent& , bool val);
		virtual void					onAnalogInputEvent(const SampleFramework::InputEvent& , float val);
		virtual void					onPointerInputEvent(const SampleFramework::InputEvent&, physx::PxU32, physx::PxU32, physx::PxReal dx, physx::PxReal dy, bool val);
		virtual void					collectInputEvents(std::vector<const SampleFramework::InputEvent*>& inputEvents);

		virtual	void					update(Camera& camera, PxReal dtime);

				void					setView(PxReal pitch, PxReal yaw);

//	private:
				PxController&			mCCT;
				SampleCustomGravity&	mBase;

				PxVec3					mTarget;

PxMat33	mTest;
				PxVec3					mForward, mRightV;
				PxU32					mNbRecords;
				PxVec3					mHistory[POS_HISTORY_LIMIT];

				PxReal					mTargetYaw, mTargetPitch;
				PxReal					mPitchMin,	mPitchMax;

				PxReal					mGamepadPitchInc, mGamepadYawInc;
				PxReal					mGamepadForwardInc, mGamepadLateralInc;
				PxReal					mSensibility;

				bool					mFwd,mBwd,mLeft,mRight,mKeyShiftDown;

				PxReal					mRunningSpeed;
				PxReal					mWalkingSpeed;
	private:
				SampleCustomGravityCameraController& operator=(const SampleCustomGravityCameraController&);

};
