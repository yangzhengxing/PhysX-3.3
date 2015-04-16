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

#include "SampleStepper.h"
#include "PhysXSample.h"
#include "PxScene.h"


bool DebugStepper::advance(PxScene* scene, PxReal dt, void* scratchBlock, PxU32 scratchBlockSize)
{
	mTimer.getElapsedSeconds();
	
	{
		PxSceneWriteLock writeLock(*scene);
		scene->simulate(mStepSize, NULL, scratchBlock, scratchBlockSize);
	}

	return true;
}

void DebugStepper::wait(PxScene* scene)
{
	mSample->onSubstepPreFetchResult();
	{
		PxSceneWriteLock writeLock(*scene);
		scene->fetchResults(true, NULL);
	}
	mSimulationTime = (PxReal)mTimer.getElapsedSeconds();
	mSample->onSubstep(mStepSize);
}

void StepperTask::run()
{
	mStepper->substepDone(this);
	release();
}

void StepperTaskCollide::run()
{
	getStepper()->collisionStep(mCont);
}

void StepperTaskSolve::run()
{
	mStepper->solveStep(mCont);

	// start any parallel sample tasks when call to solve (and collide) is finished
	// solve & collide acquire the scene write lock.
	mStepper->getSample().onSubstepStart(mStepper->getSubStepSize());
}

void MultiThreadStepper::solveStep(physx::PxBaseTask* ownerTask)
{
	PxSceneWriteLock writeLock(*mScene);

#if PX_ENABLE_INVERTED_STEPPER_FEATURE
	mScene->solve(mSubStepSize, ownerTask, mScratchBlock, mScratchBlockSize);
#else
	mScene->simulate(mSubStepSize, ownerTask, mScratchBlock, mScratchBlockSize);
#endif
}

void MultiThreadStepper::collisionStep(physx::PxBaseTask* ownerTask)
{
#if PX_ENABLE_INVERTED_STEPPER_FEATURE
	PxSceneWriteLock writeLock(*mScene);
 	mScene->collide(mSubStepSize, ownerTask);
#endif
}

void MultiThreadStepper::renderDone()
{
	if(mFirstCompletionPending)
	{
		mCompletion0.removeReference();
		mFirstCompletionPending = false;
	}
}

bool MultiThreadStepper::advance(PxScene* scene, PxReal dt, void* scratchBlock, PxU32 scratchBlockSize)
{
	mScratchBlock = scratchBlock;
	mScratchBlockSize = scratchBlockSize;

	if(!mSync)
		mSync = SAMPLE_NEW(PsSyncAlloc);

	substepStrategy(dt, mNbSubSteps, mSubStepSize);
	
	if(mNbSubSteps == 0) return false;

	mScene = scene;

	mSync->reset();

	mCurrentSubStep = 1;

	mCompletion0.setContinuation(*mScene->getTaskManager(), NULL);

	mSimulationTime = 0.0f;
	mTimer.getElapsedSeconds();

	// take first substep
	substep(mCompletion0);	
	mFirstCompletionPending = true;

	return true;
}

void MultiThreadStepper::substepDone(StepperTask* ownerTask)
{
	mSample->onSubstepPreFetchResult();

	{
#ifndef PX_PROFILE
		PxSceneWriteLock writeLock(*mScene);
#endif
		mScene->fetchResults(true);
	}

	PxReal delta = (PxReal)mTimer.getElapsedSeconds();
	mSimulationTime += delta;

	mSample->onSubstep(mSubStepSize);

	if(mCurrentSubStep>=mNbSubSteps)
	{
		mSync->set();
	}
	else
	{
		StepperTask &s = ownerTask == &mCompletion0 ? mCompletion1 : mCompletion0;
		s.setContinuation(*mScene->getTaskManager(), NULL);
		mCurrentSubStep++;

		mTimer.getElapsedSeconds();

		substep(s);

		// after the first substep, completions run freely
		s.removeReference();
	}
}


void MultiThreadStepper::substep(StepperTask& completionTask)
{
	// setup any tasks that should run in parallel to simulate()
	mSample->onSubstepSetup(mSubStepSize, &completionTask);

	// step
	{
		mSolveTask.setContinuation(&completionTask);
		mCollideTask.setContinuation(&mSolveTask);
		
		mCollideTask.removeReference();
		mSolveTask.removeReference();
	}
	// parallel sample tasks are started in mSolveTask (after solve was called which acquires a write lock).
}

void FixedStepper::substepStrategy(const PxReal stepSize, PxU32& substepCount, PxReal& substepSize)
{
	if(mAccumulator > mFixedSubStepSize)
		mAccumulator = 0.0f;

	// don't step less than the step size, just accumulate
	mAccumulator  += stepSize;
	if(mAccumulator < mFixedSubStepSize)
	{
		substepCount = 0;
		return;
	}

	substepSize = mFixedSubStepSize;
	substepCount = PxMin(PxU32(mAccumulator/mFixedSubStepSize), mMaxSubSteps);

	mAccumulator -= PxReal(substepCount)*substepSize;
}

void VariableStepper::substepStrategy(const PxReal stepSize, PxU32& substepCount, PxReal& substepSize)
{
	if(mAccumulator > mMaxSubStepSize)
		mAccumulator = 0.0f;

	// don't step less than the min step size, just accumulate
	mAccumulator  += stepSize;
	if(mAccumulator < mMinSubStepSize)
	{
		substepCount = 0;
		return;
	}

	substepCount = PxMin(PxU32(PxCeil(mAccumulator/mMaxSubStepSize)), mMaxSubSteps);
	substepSize = PxMin(mAccumulator/substepCount, mMaxSubStepSize);

	mAccumulator -= PxReal(substepCount)*substepSize;
}

bool InvertedFixedStepper::advance(PxScene* scene, PxReal dt, void* scratchBlock, PxU32 scratchBlockSize)
{
	mScratchBlock = scratchBlock;
	mScratchBlockSize = scratchBlockSize;

	if(!mSync)
		mSync = SAMPLE_NEW(PsSyncAlloc);

	substepStrategy(dt, mNbSubSteps, mSubStepSize);
	
	if(mNbSubSteps == 0) return false;

	mScene = scene;

	mSync->reset();

	mCurrentSubStep = 1;

	mSimulationTime = 0.0f;
	mTimer.getElapsedSeconds();

	if(!mIsCollideRunning)
	{
		mCompletion0.setContinuation(*mScene->getTaskManager(), NULL);
		mSolveTask.setContinuation(&mCompletion0);
	}

	//kick off the solver task
	mSolveTask.removeReference();
	
	mFirstCompletionPending = true;

	return true;
}

void InvertedFixedStepper::postRender(const PxReal stepSize)
{
	mCompletion0.setContinuation(*mScene->getTaskManager(), NULL);

	// setup any tasks that should run in parallel to simulate()
	mSample->onSubstepSetup(mSubStepSize, &mCompletion0);

	mSolveTask.setContinuation(&mCompletion0);
	mCollideTask.setContinuation(&mSolveTask);

	//solve can't start to run with the completion of collide so we can't remove the solveTask reference yet
	//kick off the collision task
	mCollideTask.removeReference();

	// parallel sample tasks are started in mSolveTask (after solve was called which acquires a write lock).
}


void InvertedFixedStepper::substepDone(StepperTask* ownerTask)
{
	mIsCollideRunning = true;
	mSample->onSubstepPreFetchResult();

	{
#ifndef PX_PROFILE
		PxSceneWriteLock writeLock(*mScene);
#endif
		mScene->fetchResults(true);
	}
	
	PxReal delta = (PxReal)mTimer.getElapsedSeconds();
	mSimulationTime += delta;

	mSample->onSubstep(mSubStepSize);

	if(mCurrentSubStep>=mNbSubSteps)
	{
		mSync->set();
	}
	else
	{	
		//wait for collision finish before we tick off the mSolve task
		StepperTask &s = ownerTask == &mCompletion0 ? mCompletion1 : mCompletion0;
		s.setContinuation(*mScene->getTaskManager(), NULL);

		mCurrentSubStep++;

		mTimer.getElapsedSeconds();

		// setup any tasks that should run in parallel to simulate()
		mSample->onSubstepSetup(mSubStepSize, &s);

		mSolveTask.setContinuation(&s);
		mCollideTask.setContinuation(&mSolveTask);

		mCollideTask.removeReference();

		mSolveTask.removeReference();
		// after the first substep, completions run freely
		s.removeReference();
	}
}

