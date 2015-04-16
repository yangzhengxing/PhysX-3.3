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


#ifndef KINEMATIC_PLATFORM_H
#define KINEMATIC_PLATFORM_H

#include "common/PxPhysXCommonConfig.h"
#include "foundation/PxTransform.h"
#include "SampleAllocator.h"
#include "SampleAllocatorSDKClasses.h"
#include "characterkinematic/PxControllerObstacles.h"
#include <vector>

namespace physx
{
	class PxRigidDynamic;
}

	// PT: Captures the state of the platform. We decouple this data from the platform itself so that the
	// same platform path (const data) can be used by several platform instances.
	struct PlatformState
	{
					PlatformState();

		PxTransform	mPrevPose;
		PxReal		mCurrentTime;
		PxReal		mCurrentRotationTime;
		bool		mFlip;
	};

	enum LoopMode
	{
		LOOP_FLIP,
		LOOP_WRAP,
	};

	class KinematicPlatform : public SampleAllocateable
	{
		public:
												KinematicPlatform();
												~KinematicPlatform();

						void					release();
						void					init(PxU32 nbPts, const PxVec3* pts, const PxTransform& globalPose, const PxQuat& localRot, PxRigidDynamic* actor, PxReal travelTime, PxReal rotationSpeed, LoopMode mode=LOOP_FLIP);
						void					setBoxObstacle(ObstacleHandle handle, const PxBoxObstacle* boxObstacle);
						PxU32					getNbSegments()								const;
						PxReal					computeLength()								const;
						bool					getPoint(PxVec3& p, PxU32 seg, PxReal t)	const;
						bool					getPoint(PxVec3& p, PxReal t)				const;
						void					resync();

		PX_FORCE_INLINE	void					updatePhysics(PxReal dtime)										{ updateState(mPhysicsState, NULL, dtime, true);			}
		PX_FORCE_INLINE	void					updateRender(PxReal dtime, PxObstacleContext* obstacleContext)	{ updateState(mRenderState, obstacleContext, dtime, false);	}

		PX_FORCE_INLINE	PxReal					getTravelTime()			const	{ return mTravelTime;						}
		PX_FORCE_INLINE	void					setTravelTime(PxReal t)			{ mTravelTime = t;							}
						void					setT(PxF32 t);

		PX_FORCE_INLINE	const PxTransform&		getPhysicsPose()		const	{ return mPhysicsState.mPrevPose;			}
		PX_FORCE_INLINE	const PxTransform&		getRenderPose()			const	{ return mRenderState.mPrevPose;			}

		PX_FORCE_INLINE	PxRigidDynamic*			getPhysicsActor()				{ return mActor;							}

		PX_FORCE_INLINE	PxReal					getRotationSpeed()		const	{ return mRotationSpeed;					}
		PX_FORCE_INLINE	void					setRotationSpeed(PxReal s)		{ mRotationSpeed = s;						}

		protected:
						PxQuat					mLocalRot;		// Local rotation (const data)
						PxU32					mNbPts;
						PxVec3Alloc*			mPts;
						PxRigidDynamic*			mActor;			// Physics
						const PxBoxObstacle*	mBoxObstacle;
						ObstacleHandle			mObstacle;		// Render
						PxReal					mTravelTime;
						PxReal					mRotationSpeed;
						LoopMode				mMode;

						PlatformState			mPhysicsState;
						PlatformState			mRenderState;
						void					updateState(PlatformState& state, PxObstacleContext* obstacleContext, PxReal dtime, bool updateActor)	const;
	};

	class KinematicPlatformManager : public SampleAllocateable
	{
		public:
															KinematicPlatformManager();
															~KinematicPlatformManager();

						void								release();
						KinematicPlatform*					createPlatform(PxU32 nbPts, const PxVec3* pts, const PxTransform& pose, const PxQuat& localRot, PxRigidDynamic* actor, PxReal platformSpeed, PxReal rotationSpeed, LoopMode mode=LOOP_FLIP);

		PX_FORCE_INLINE	PxU32								getNbPlatforms()			{ return (PxU32)mPlatforms.size();	}
		PX_FORCE_INLINE	KinematicPlatform**					getPlatforms()				{ return &mPlatforms[0];			}
		PX_FORCE_INLINE	PxF32								getElapsedTime()			{ return mElapsedPlatformTime;		}
		PX_FORCE_INLINE	void								syncElapsedTime(float time)	{ mElapsedPlatformTime = time;		}

						void								updatePhysicsPlatforms(float dtime);

		protected:
						std::vector<KinematicPlatform*>		mPlatforms;
						PxF32								mElapsedPlatformTime;
	};


#endif
