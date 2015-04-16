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
// This snippet demonstrates the use of broad phase regions (MBP).
//
// It shows the setup of MBP and its regions. In this example 4 regions are setup
// and set for the MBP. Created stacks are then simulated in multiple regions.
// Note that current regions setup is not optimal, some objects get out of regions bounds.
// In this case a warning is reported. It is possible to add PxBroadPhaseCallback
// to scene to handle such cases. 
//
// ****************************************************************************

#include <ctype.h>
#include <vector>

#include "PxPhysicsAPI.h"

#include "../SnippetUtils/SnippetUtils.h"
#include "../SnippetCommon/SnippetPrint.h"
#include "../SnippetCommon/SnippetPVD.h"


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

PxReal stackZ = 10.0f;

PxU32 gRegionHandles[4];

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

class SnippetMBPBroadPhaseCallback : public physx::PxBroadPhaseCallback
{
	std::vector<PxActor*> outOfBoundsActors;
public:
	virtual void onObjectOutOfBounds(PxShape& /*shape*/, PxActor& actor)
	{
		PxU32 i = 0;
		for(; i < outOfBoundsActors.size(); ++i)
		{
			if(outOfBoundsActors[i] == &actor)
				break;
		}
		if(i == outOfBoundsActors.size())
		{
			outOfBoundsActors.push_back(&actor);
		}
	}

	virtual void onObjectOutOfBounds(PxAggregate& /*aggregate*/)
	{
		//This test does not use aggregates so no need to do anything here
	}

	void purgeOutOfBoundsObjects()
	{
		for(PxU32 i = 0; i < outOfBoundsActors.size(); ++i)
		{
			outOfBoundsActors[i]->release();
		}
		outOfBoundsActors.clear();
	}
} gBroadPhaseCallback;


void initPhysics(bool interactive)
{
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
	PxProfileZoneManager* profileZoneManager = &PxProfileZoneManager::createProfileZoneManager(gFoundation);
	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,profileZoneManager);

	if(gPhysics->getPvdConnectionManager())
	{
		gPhysics->getVisualDebugger()->setVisualizeConstraints(true);
		gPhysics->getVisualDebugger()->setVisualDebuggerFlag(PxVisualDebuggerFlag::eTRANSMIT_CONTACTS, true);
		gPhysics->getVisualDebugger()->setVisualDebuggerFlag(PxVisualDebuggerFlag::eTRANSMIT_SCENEQUERIES, true);	
		gConnection = PxVisualDebuggerExt::createConnection(gPhysics->getPvdConnectionManager(), PVD_HOST, 5425, 10);
	}

	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	
	PxU32 numWorkers = PxMax(PxI32(SnippetUtils::getNbPhysicalCores())-1, 0);
	gDispatcher = PxDefaultCpuDispatcherCreate(numWorkers);
	sceneDesc.cpuDispatcher	= gDispatcher;
	sceneDesc.filterShader	= PxDefaultSimulationFilterShader;

	sceneDesc.broadPhaseType = PxBroadPhaseType::eMBP;

	gScene = gPhysics->createScene(sceneDesc);

	PxBroadPhaseRegion regions[4] =
	{
		{	PxBounds3(PxVec3(-100, -100, -100),  PxVec3(  0, 100,   0)), (void*)1 },
		{	PxBounds3(PxVec3(-100, -100,    0),  PxVec3(  0, 100, 100)), (void*)2 }, 
		{	PxBounds3(PxVec3(   0, -100, -100),  PxVec3(100, 100,   0)), (void*)3 },
		{	PxBounds3(PxVec3(   0, -100,    0),  PxVec3(100, 100, 100)), (void*)4 }
	};

	for(PxU32 i=0;i<4;i++)
		gScene->addBroadPhaseRegion(regions[i]);

	gScene->setBroadPhaseCallback(&gBroadPhaseCallback);

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
	gScene->fetchResults(true);
	gBroadPhaseCallback.purgeOutOfBoundsObjects();
}
	
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	gScene->release();
	gDispatcher->release();
	PxProfileZoneManager* profileZoneManager = gPhysics->getProfileZoneManager();
	if(gConnection != NULL)
		gConnection->release();
	gPhysics->release();	
	profileZoneManager->release();
	gFoundation->release();

	printf("SnippetMBP done.\n");
}

void keyPress(const char key, const PxTransform& camera)
{
	switch(toupper(key))
	{
	case 'B':	createStack(PxTransform(PxVec3(0,0,stackZ-=10.0f)), 10, 2.0f);						break;
	case ' ':	createDynamic(camera, PxSphereGeometry(3.0f), camera.rotate(PxVec3(0,0,-1))*200);	break;
	}
}

int snippetMain(int, const char*const*)
{
#ifdef RENDER_SNIPPET
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}
