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


// ****************************************************************************
// This snippet shows how to coordinate threads performing asynchronous
// work during the scene simulation. After simulate() is called, user threads 
// are started that perform ray-casts against the scene. The call to 
// fetchResults() is delayed until all ray-casts have completed.
// ****************************************************************************

#include <ctype.h>

#include "PxPhysicsAPI.h"

#include "../SnippetUtils/SnippetUtils.h"
#include "../SnippetCommon/SnippetPrint.h"
#include "../SnippetCommon/SnippetPVD.h"


using namespace physx;
using namespace shdfnd; // internal platform abstractions for atomics, threads and synchronization

PxDefaultAllocator		 gAllocator;
PxDefaultErrorCallback	 gErrorCallback;

PxFoundation*			 gFoundation = NULL;
PxPhysics*				 gPhysics	= NULL;

PxDefaultCpuDispatcher*	 gDispatcher = NULL;
PxScene*				 gScene		= NULL;

PxMaterial*				 gMaterial	= NULL;

PxVisualDebuggerConnection*
						gConnection	= NULL;

struct RaycastThread
{
	SnippetUtils::Sync*		mWorkReadySyncHandle;
	SnippetUtils::Thread*	mThreadHandle;
};
const PxU32				 gNumThreads = 1;
RaycastThread			 gThreads[gNumThreads];

SnippetUtils::Sync*		 gWorkDoneSyncHandle;

const PxI32				 gRayCount = 1024;
volatile PxI32			 gRaysAvailable;
volatile PxI32			 gRaysCompleted;


static PxVec3 randVec3() 
{
	return (PxVec3(float(rand())/RAND_MAX,
		float(rand())/RAND_MAX, 
		float(rand())/RAND_MAX)*2.0f - PxVec3(1.0f)).getNormalized();
}

static void threadExecute(void* data)
{
	RaycastThread* raycastThread = static_cast<RaycastThread*>(data);

	// Perform random raycasts against the scene until stop.
	for(;;)
	{
		// Wait here for the sync to be set then reset the sync
		// to ensure that we only perform raycast work after the 
		// sync has been set again.
		SnippetUtils::syncWait(raycastThread->mWorkReadySyncHandle);
		SnippetUtils::syncReset(raycastThread->mWorkReadySyncHandle);

		// If the thread has been signaled to quit then exit this function.
		if (SnippetUtils::threadQuitIsSignalled(raycastThread->mThreadHandle))
			break;

		// Perform a fixed number of random raycasts against the scene
		// and share the work between multiple threads.
		while (SnippetUtils::atomicDecrement(&gRaysAvailable) >= 0)
		{
			PxVec3 dir = randVec3();

			PxRaycastBuffer buf;
			gScene->raycast(PxVec3(0.0f), dir.getNormalized(), 1000.0f, buf, PxHitFlag::eDEFAULT);

			// If this is the last raycast then signal this to the main thread.
			if (SnippetUtils::atomicIncrement(&gRaysCompleted) == gRayCount)
			{
				SnippetUtils::syncSet(gWorkDoneSyncHandle);
			}
		}
	}

	// Quit the current thread.
	SnippetUtils::threadQuit(raycastThread->mThreadHandle);
}

void createStack(const PxTransform& t, PxU32 size, PxReal halfExtent)
{
	PxShape* shape = gPhysics->createShape(PxBoxGeometry(halfExtent, halfExtent, halfExtent), *gMaterial);
	for(PxU32 i=0; i<size;i++)
	{
		for(PxU32 j=0;j<size-i;j++)
		{
			PxTransform localTm(PxVec3(PxReal(j*2) - PxReal(size-i), PxReal(i*2+1), 0) * halfExtent);
			PxRigidDynamic* body = gPhysics->createRigidDynamic(t.transform(localTm));
			body->attachShape(*shape);
			PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
			gScene->addActor(*body);
		}
	}
	shape->release();
}

void createPhysicsAndScene()
{
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
	PxProfileZoneManager* profileZoneManager = &PxProfileZoneManager::createProfileZoneManager(gFoundation);
	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,profileZoneManager);

	if(gPhysics->getPvdConnectionManager())
	{
		gConnection = PxVisualDebuggerExt::createConnection(gPhysics->getPvdConnectionManager(), PVD_HOST, 5425, 10);
	}

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	
	PxU32 numWorkers = PxMax(PxI32(SnippetUtils::getNbPhysicalCores())-1, 0);
	gDispatcher = PxDefaultCpuDispatcherCreate(numWorkers);
	sceneDesc.cpuDispatcher	= gDispatcher;
	sceneDesc.filterShader	= PxDefaultSimulationFilterShader;
	
	gScene = gPhysics->createScene(sceneDesc);
	
	PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0,1,0,0), *gMaterial);
	gScene->addActor(*groundPlane);

	for(PxU32 i=0;i<5;i++)
		createStack(PxTransform(PxVec3(0,0,i*10.0f)), 10, 2.0f);
}

void createRaycastThreads()
{
	// Create and start threads that will perform raycasts.
	// Create a sync for each thread so that a signal may be sent
	// from the main thread to the raycast thread that it can start 
	// performing raycasts.
	for (PxU32 i=0; i < gNumThreads; ++i)
	{
		//Create a sync.
		gThreads[i].mWorkReadySyncHandle = SnippetUtils::syncCreate();

		//Create and start a thread.
		gThreads[i].mThreadHandle =  SnippetUtils::threadCreate(threadExecute, &gThreads[i]);
	}

	// Create another sync so that the raycast threads can signal to the main 
	// thread that they have finished performing their raycasts.
	gWorkDoneSyncHandle = SnippetUtils::syncCreate();
}

void initPhysics()
{
	createPhysicsAndScene();
	createRaycastThreads();
}

void stepPhysics()
{
	// Start simulation
	gScene->simulate(1.0f/60.0f);

	// Start ray-cast threads
	gRaysAvailable = gRayCount;
	gRaysCompleted = 0;

	// Signal to each raycast thread that they can start performing raycasts.
	for (PxU32 i=0; i < gNumThreads; ++i)
	{
		SnippetUtils::syncSet(gThreads[i].mWorkReadySyncHandle);
	}

	// Wait for raycast threads to finish.
	SnippetUtils::syncWait(gWorkDoneSyncHandle);
	SnippetUtils::syncReset(gWorkDoneSyncHandle);

	// Fetch simulation results
	gScene->fetchResults(true);
}
	
void cleanupPhysics()
{
	// Signal threads to quit.
	for (PxU32 i=0; i < gNumThreads; ++i)
	{
		SnippetUtils::threadSignalQuit(gThreads[i].mThreadHandle);
		SnippetUtils::syncSet(gThreads[i].mWorkReadySyncHandle);
	}

	// Clean up raycast threads and syncs.
	for (PxU32 i=0; i < gNumThreads; ++i)
	{
		SnippetUtils::threadWaitForQuit(gThreads[i].mThreadHandle);
		SnippetUtils::threadRelease(gThreads[i].mThreadHandle);
		SnippetUtils::syncRelease(gThreads[i].mWorkReadySyncHandle);
	}

	// Clean up the sync for the main thread.
	SnippetUtils::syncRelease(gWorkDoneSyncHandle);

	gScene->release();

	gDispatcher->release();
	PxProfileZoneManager* profileZoneManager = gPhysics->getProfileZoneManager();
	if(gConnection != NULL)
		gConnection->release();
	gPhysics->release();
	profileZoneManager->release();
	gFoundation->release();
	
	printf("SnippetMultiThreading done.\n");
}

int snippetMain(int, const char*const*)
{
	initPhysics();

	for(PxU32 i=0; i<100; ++i)
		stepPhysics();

	cleanupPhysics();

	return 0;
}

