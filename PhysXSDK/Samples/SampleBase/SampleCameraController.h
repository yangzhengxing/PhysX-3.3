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

#ifndef SAMPLE_CAMERA_CONTROLLER_H
#define SAMPLE_CAMERA_CONTROLLER_H

#include "SampleAllocator.h"
#include "RendererWindow.h"
#include <SampleUserInput.h>
#include "foundation/PxVec3.h"

namespace SampleFramework {
	class SamplePlatform;
}

class Camera;

class CameraController : public SampleAllocateable
{
	public:
	virtual ~CameraController() {}

	virtual void		onPointerInputEvent(const SampleFramework::InputEvent& ie, physx::PxU32 x, physx::PxU32 y, physx::PxReal dx, physx::PxReal dy, bool val) {}

	virtual void		onAnalogInputEvent(const SampleFramework::InputEvent& , float val) {}
	virtual void		onDigitalInputEvent(const SampleFramework::InputEvent& , bool val) {}

	virtual	void		update(Camera& camera, PxReal dtime)												{}
	virtual void		collectInputEvents(std::vector<const SampleFramework::InputEvent*>& inputEvents)	{}
	virtual PxReal		getCameraSpeed() { return 0; }
};

class DefaultCameraController : public CameraController
{
	public:
						DefaultCameraController();
	virtual				~DefaultCameraController();

			void		init(const PxVec3& pos, const PxVec3& rot);
			void		init(const PxTransform& pose);
			void		setCameraSpeed(const PxReal speed) { mCameraSpeed = speed; }
			PxReal		getCameraSpeed() { return mCameraSpeed; }
			void		setMouseLookOnMouseButton(bool mouseLookOnMB) { mMouseLookOnMB = mouseLookOnMB; }
			void		setMouseSensitivity(PxReal mouseSensitivity) { mMouseSensitivity = mouseSensitivity; }

	// Implements CameraController
			void		onMouseDelta(PxI32 dx, PxI32 dy);

	virtual void		onAnalogInputEvent(const SampleFramework::InputEvent& , float val);
	virtual void		onDigitalInputEvent(const SampleFramework::InputEvent& , bool val);
	virtual void		onPointerInputEvent(const SampleFramework::InputEvent& ie, physx::PxU32 x, physx::PxU32 y, physx::PxReal dx, physx::PxReal dy, bool val);

	virtual void		collectInputEvents(std::vector<const SampleFramework::InputEvent*>& inputEvents);

	virtual	void		update(Camera& camera, PxReal dtime);

	protected:
			PxVec3								mTargetEyePos;
			PxVec3								mTargetEyeRot;
			PxVec3								mEyePos;
			PxVec3								mEyeRot;

			bool								mMouseButtonDown;
			bool								mKeyFWDown;
			bool								mKeyBKDown;
			bool								mKeyRTDown;
			bool								mKeyLTDown;
			bool								mKeyUpDown;
			bool								mKeyDownDown;
			bool								mKeyShiftDown;
			PxReal								mCameraSpeed;
			PxReal								mCameraSpeedMultiplier;
			bool								mMouseLookOnMB;
			PxReal								mMouseSensitivity;
	};

#endif
