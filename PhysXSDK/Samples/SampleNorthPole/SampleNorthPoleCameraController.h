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

#include "PhysXSample.h"
#include "SampleCameraController.h"
#include "characterkinematic/PxController.h"

class SampleNorthPoleCameraController : public CameraController
{
	public:
		SampleNorthPoleCameraController(PxCapsuleController& controlled, SampleNorthPole& base);

		virtual void			onDigitalInputEvent(const SampleFramework::InputEvent& , bool val);
		virtual void			onAnalogInputEvent(const SampleFramework::InputEvent& , float val);
		virtual void			onPointerInputEvent(const SampleFramework::InputEvent&, PxU32 x, PxU32 y, PxReal dx, PxReal dy, bool val);

		virtual void			collectInputEvents(std::vector<const SampleFramework::InputEvent*>& inputEvents);

		virtual	void			update(Camera& camera, PxReal dtime);

				void			setView(PxReal pitch, PxReal yaw);

	private:
		SampleNorthPoleCameraController& operator=(const SampleNorthPoleCameraController&);
				PxExtendedVec3	computeCameraTarget();

		PxCapsuleController&	mCCT;
		SampleNorthPole&		mBase;	// PT: TODO: find a way to decouple us from PhysXSampleApplication. Only needed for "recenterCursor". Maybe the app could inherit from the cam...

				PxReal			mTargetYaw, mTargetPitch;
				PxReal			mPitchMin,	mPitchMax;

				PxReal			mGamepadPitchInc, mGamepadYawInc;
				PxReal			mGamepadForwardInc, mGamepadLateralInc;
				PxReal			mSensibility;

				bool			mFwd,mBwd,mLeft,mRight,mKeyShiftDown;

				PxReal			mRunningSpeed;
				PxReal			mWalkingSpeed;

				PxF32			mFilterMemory;
};
