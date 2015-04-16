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

#ifndef SAMPLE_CCT_ACTOR_H
#define SAMPLE_CCT_ACTOR_H

#include "characterkinematic/PxExtended.h"
#include "characterkinematic/PxController.h"
#include "SamplePreprocessor.h"
#include "SampleCCTJump.h"

namespace physx
{
	class PxController;
	class PxUserControllerHitReport;
	class PxControllerBehaviorCallback;
	class PxControllerManager;
	class PxPhysics;
	class PxScene;
}

using namespace physx;

namespace SampleRenderer
{
	class Renderer;
}

class RenderBaseActor;
class PhysXSample;

	struct ControlledActorDesc
	{
										ControlledActorDesc();

		PxControllerShapeType::Enum		mType;
		PxExtendedVec3					mPosition;
		float							mSlopeLimit;
		float							mContactOffset;
		float							mStepOffset;
		float							mInvisibleWallHeight;
		float							mMaxJumpHeight;
		float							mRadius;
		float							mHeight;
		float							mCrouchHeight;
		float							mProxyDensity;
		float							mProxyScale;
		float							mVolumeGrowth;
		PxUserControllerHitReport*		mReportCallback;
		PxControllerBehaviorCallback*	mBehaviorCallback;
	};

	class ControlledActor : public SampleAllocateable
	{
		public:
													ControlledActor(PhysXSample& owner);
		virtual										~ControlledActor();

						PxController*				init(const ControlledActorDesc& desc, PxControllerManager* manager);
						PxExtendedVec3				getFootPosition()	const;
						void						reset();
						void						teleport(const PxVec3& pos);
						void						sync();
						void						tryStandup();
						void						resizeController(PxReal height);
						void						resizeStanding()			{ resizeController(mStandingSize);	}
						void						resizeCrouching()			{ resizeController(mCrouchingSize);	}
						void						jump(float force)			{ mJump.startJump(force);			}

		PX_FORCE_INLINE	RenderBaseActor*			getRenderActorStanding()	{ return mRenderActorStanding;		}
		PX_FORCE_INLINE	RenderBaseActor*			getRenderActorCrouching()	{ return mRenderActorCrouching;		}
		PX_FORCE_INLINE	PxController*				getController()				{ return mController;				}

						const Jump&                 getJump() const { return mJump; }

		protected:
						PhysXSample&				mOwner;
						PxControllerShapeType::Enum	mType;
						Jump						mJump;

						PxExtendedVec3				mInitialPosition;
						PxVec3						mDelta;
						bool						mTransferMomentum;

						PxController*				mController;
						RenderBaseActor*			mRenderActorStanding;
						RenderBaseActor*			mRenderActorCrouching;
						PxReal						mStandingSize;
						PxReal						mCrouchingSize;
						PxReal						mControllerRadius;
						bool						mDoStandup;
						bool						mIsCrouching;
		friend class SampleCCTCameraController;

	private:
		ControlledActor& operator=(const ControlledActor&);
	};

	void defaultCCTInteraction(const PxControllerShapeHit& hit);

#endif
