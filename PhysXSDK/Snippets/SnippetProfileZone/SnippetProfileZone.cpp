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
// This snippet demonstrates how to query PxProfileZone event data that is internal
// to the PhysX SDK.  
//
// The profiler caters for multiple profile zones (e.g. PhysX and APEX) and multiple clients
// (e.g. the application and PVD.)
//
// The snippet makes use of the PxDefaultBufferedProfiler class. This class manages
// the PxProfileZoneManager and PxProfileZone callbacks in order to retrieve the 
// profile event data from specified profile zones.
// There is a single app-wide ProfileZoneManager, which is created by PxDefaultBufferedProfiler
// before the instantiation of any profile zones.
//
// Every physics step we flush the PxDefaultBufferedProfiler. All registered PxProfileZones
// will then flush their event buffers and clients receive the buffer events through the
// PxBufferedProfilerCallback.
// 
// PhysX events are collected and printed to the screen each simulation step.
// ****************************************************************************

#include <vector>
#include <algorithm>

#include "PxPhysicsAPI.h"

#include "../SnippetCommon/SnippetPrint.h"
#include "../SnippetCommon/SnippetPVD.h"
#include "../SnippetUtils/SnippetUtils.h"


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene		= NULL;

PxMaterial*				gMaterial	= NULL;

PxVisualDebuggerConnection*
						gConnection	= NULL;

PxDefaultBufferedProfiler*	gDefaultBufferProfiler = NULL;


namespace physx
{
bool operator<(const PxBufferedProfilerEvent &e1, const PxBufferedProfilerEvent& e2)
{
	// sort the cross-thread events to the front
	if(e1.threadId == PxBufferedProfilerCallback::CROSS_THREAD_ID && e2.threadId != PxBufferedProfilerCallback::CROSS_THREAD_ID) 
		return true;
	else if(e2.threadId == PxBufferedProfilerCallback::CROSS_THREAD_ID)
		return false;

	// otherwise sort by thread ID, then event ID
	return (e1.threadId < e2.threadId) || ((e1.threadId == e2.threadId) && (e1.id <e2.id));	
}
}

// This is the main class that handles events and collects them for later printing
class SnippetBufferedProfilerCallback: public PxBufferedProfilerCallback
{
public:

	// if the event buffer is flushed, each event is send in this callback
	virtual void onEvent(const PxBufferedProfilerEvent& event) 
	{		
		mEvents.push_back(event);
	}

	// print the stored events on screen
	void printEvents()
	{
		std::sort(mEvents.begin(),mEvents.end());
	
		printf("------------------------------ frame start ------------------------------------- \n");
		for(PxU32 i=0;i<mEvents.size(); i++)
		{
			PxBufferedProfilerEvent& e = mEvents[i];
			if(i==0 || e.threadId != mEvents[i-1].threadId)
			{
				if(e.threadId == PxBufferedProfilerCallback::CROSS_THREAD_ID)
					printf("---------------------- Cross-thread events ---------------------------- \n");
				else
					printf("\n---------------------- Thread id %d events ---------------------------- \n", e.threadId);
			}

			float timeInMs = (e.stopTimeNs - e.startTimeNs)/1000000.0f;
			printf("%-40s: %5.5f ms\n", e.name, timeInMs);

		}
		printf("------------------------------ frame end ----------------------------------- \n");

		mEvents.clear();
	}
protected:
	std::vector<PxBufferedProfilerEvent> mEvents;
} snippetBufferedProfilerCallback;



PxReal stackZ = 10.0f;

PxRigidDynamic* createDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity=PxVec3(0))
{
	PxRigidDynamic* dynamic = PxCreateDynamic(*gPhysics, t, geometry, *gMaterial, 10.0f);
	dynamic->setAngularDamping(0.5f);
	dynamic->setLinearVelocity(velocity);
	gScene->addActor(*dynamic);
	return dynamic;
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

void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

	// when PhysX starts up, it will add a PhysX SDK profile zone. So we create
	// the PxDefaultBufferedProfiler before creating PxPhysics, so that it receives the zone creation event.
	// PxProfileZoneManager is instantiated inside PxDefaultBufferedProfiler to ensure that a PxProfileZoneManager instance
	// can be passed to PxCreatePhysics as a function argument..
	gDefaultBufferProfiler = PxDefaultBufferedProfilerCreate(*gFoundation, "PhysXSDK PxTaskManager");
	// we add our callback to receive events after the event buffer has been flushed.
	gDefaultBufferProfiler->addBufferedProfilerCallback(snippetBufferedProfilerCallback);	

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,&gDefaultBufferProfiler->getProfileZoneManager());

	if(gPhysics->getPvdConnectionManager())
	{
		gPhysics->getVisualDebugger()->setVisualizeConstraints(true);
		gPhysics->getVisualDebugger()->setVisualDebuggerFlag(PxVisualDebuggerFlag::eTRANSMIT_CONTACTS, true);
		gPhysics->getVisualDebugger()->setVisualDebuggerFlag(PxVisualDebuggerFlag::eTRANSMIT_SCENEQUERIES, true);
		gConnection = PxVisualDebuggerExt::createConnection(gPhysics->getPvdConnectionManager(), PVD_HOST, 5425, 10);
	}

	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher	= gDispatcher;
	sceneDesc.filterShader	= PxDefaultSimulationFilterShader;
	gScene = gPhysics->createScene(sceneDesc);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0,1,0,0), *gMaterial);
	gScene->addActor(*groundPlane);

	for(PxU32 i=0;i<5;i++)
		createStack(PxTransform(PxVec3(0,0,stackZ-=10.0f)), 10, 2.0f);

	if(!interactive)
		createDynamic(PxTransform(PxVec3(0,40,100)), PxSphereGeometry(10), PxVec3(0,-50,-100));
}

void stepPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gScene->simulate(1.0f/60.0f);

	// Custom events recorded before fetchResults will appear in the same frame buffer as physx events.
	// Events recorded after fetchResults will appear in the next frame buffer.
	gScene->fetchResults(true);

	// flush the profile zone events so we get the recorded data
	gDefaultBufferProfiler->flushEvents();
	// print the flushed events on screen
	snippetBufferedProfilerCallback.printEvents();	
}

void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	gScene->release();
	gDispatcher->release();
	if(gConnection != NULL)
		gConnection->release();
	gPhysics->release();	
	gDefaultBufferProfiler->release();
	gFoundation->release();

	printf("SnippetProfileZone done.\n");
}

int snippetMain(int, const char*const*)
{
	static const PxU32 frameCount = 10;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);

	return 0;
}
