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

#include <ctype.h>

// ****************************************************************************
// This snippet illustrates how to create a custom joint type.
// It adds support for binary serialization, RepX serialization and PVD 
// visualization.
// ****************************************************************************

#include "PxPhysicsAPI.h"
#include "PxCollectionExt.h"
#include "PxSerialization.h"

#include "PsThread.h"

#include "ExtPulleyJointExtension.h"
#include "ExtPulleyJointPVD.h"

#include "CustomPulleyJoint.h"

#include "../../SnippetCommon/SnippetPrint.h"
#include "../../SnippetCommon/SnippetPVD.h"


#define USE_CONVX	

using namespace physx;
using namespace physx::debugger;
using namespace physx::debugger::comm;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;
PxCooking*				gCooking	= NULL;
PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene		= NULL;
PxVisualDebuggerConnection*		 
						gConnection	= NULL;
PxU8*					gAlignedBlock = NULL;
PxSerializationRegistry* gSerializationRegistry = NULL;
PxCollection*           gCollection = NULL;

#define RELEASE_AND_RESET(x)  { if(x) { x->release(); x = NULL; } }

static PxCollection* createCollection()
{
	PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	
	PxTransform pose1(PxVec3(-1.0, 4.0f, 0), PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
	PxRigidDynamic* capsule1 = PxCreateDynamic(*gPhysics, pose1, PxCapsuleGeometry(1, 0.5), *material, 10.0f);
	capsule1->setAngularDamping(0.5f);

	PxTransform pose2(PxVec3(1.0, 4.0f, 0), PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
	PxRigidDynamic* capsule2 = PxCreateDynamic(*gPhysics, pose2, PxCapsuleGeometry(1, 0.5), *material, 10.0f );
	capsule2->setAngularDamping(0.5f);

	const PxVec3 globalAxis = PxVec3(0,-1,0);
	CustomPulleyJoint *joint = CustomPulleyJointCreate(*gPhysics,
													   capsule1, PxTransform(PxVec3(0,2,0)),
													   capsule2, PxTransform(PxVec3(0,2,0)));

	PX_ASSERT(joint);
	PxSetJointGlobalFrame(*joint, NULL, &globalAxis);
	joint->setStiffness(1.f);
	joint->setRatio(2.f);
	joint->setDistance(4.f);

	PxCollection* collection = PxCreateCollection();			
	collection->add(*joint);
	PxSerialization::complete(*collection, *gSerializationRegistry);
	
	return collection;
}

#if PX_SUPPORT_VISUAL_DEBUGGER
struct CustomJointConnectionHandler : public PvdConnectionHandler
{
	virtual void onPvdSendClassDescriptions( PvdConnection& inFactory )
	{
		//register the joint classes.
		PvdDataStream* connection = &inFactory.createDataStream();
		connection->addRef();
		Ext::sendUserClassDescriptions( *connection );
		connection->flush();
		connection->release();
	}
	virtual void onPvdConnected( PvdConnection& )
	{
	}
	virtual void onPvdDisconnected( PvdConnection&)
	{
	}
};

static CustomJointConnectionHandler gCustomPvdHandler;
#endif

void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);	
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
	PxProfileZoneManager* profileZoneManager = &PxProfileZoneManager::createProfileZoneManager(gFoundation);	
	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, profileZoneManager);
	PxInitExtensions(*gPhysics);
	gSerializationRegistry = PxSerialization::createSerializationRegistry(*gPhysics);	
	registerPulleyJointBinaryExtension(*gSerializationRegistry);
	registerPulleyJointRepXExtension(*gSerializationRegistry);

#if PX_SUPPORT_VISUAL_DEBUGGER
	if ( gPhysics->getPvdConnectionManager() != NULL )
	{
		gPhysics->getVisualDebugger()->setVisualizeConstraints(true);
		gPhysics->getVisualDebugger()->setVisualDebuggerFlag(PxVisualDebuggerFlag::eTRANSMIT_CONTACTS, true);
		gPhysics->getPvdConnectionManager()->addHandler( gCustomPvdHandler );
		gConnection = PxVisualDebuggerExt::createConnection(gPhysics->getPvdConnectionManager(), PVD_HOST, 5425, 10);
	}
#endif
	
	PxU32 numWorkers = PxMax(PxI32(shdfnd::Thread::getNbPhysicalCores())-1, 0);
	gDispatcher = PxDefaultCpuDispatcherCreate(numWorkers);
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0, -9.81f, 0);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader	= PxDefaultSimulationFilterShader;
	gScene = gPhysics->createScene(sceneDesc);

	gCooking = PxCreateCooking(PX_PHYSICS_VERSION, *gFoundation, PxCookingParams(PxTolerancesScale()));	
}

void stepPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	gScene->simulate(1.0f/60.0f);
	gScene->fetchResults(true);
}
	
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	
	unregisterPulleyJointRepXExtension(*gSerializationRegistry);
	unregisterPulleyJointBinaryExtension(*gSerializationRegistry);
	RELEASE_AND_RESET(gSerializationRegistry);
	RELEASE_AND_RESET(gScene);
	RELEASE_AND_RESET(gDispatcher);
	PxProfileZoneManager* profileZoneManager = gPhysics->getProfileZoneManager();
	RELEASE_AND_RESET(gConnection);
	RELEASE_AND_RESET(gPhysics);
	RELEASE_AND_RESET(gCooking);	
	profileZoneManager->release();
	PxCloseExtensions();
	RELEASE_AND_RESET(gFoundation);
	free(gAlignedBlock);	
}

void instanceCollectionWithRepX()
{
	PxCollection* c = createCollection();

	PxDefaultMemoryOutputStream stream;
	PxSerialization::serializeCollectionToXml(stream, *c, *gSerializationRegistry);
	c->release();
	
	PxDefaultMemoryInputData inputStream(stream.getData(), stream.getSize());		
	c = PxSerialization::createCollectionFromXml(inputStream, *gCooking, *gSerializationRegistry);	
	gScene->addCollection( *c );
	gCollection = c;

	PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0,1,0,0), *material);
	gScene->addActor(*groundPlane);
}

static void* createAlignedBlock(PxInputData& data, PxU8*& baseAddr)
{
	PxU32 length = data.getLength();
	baseAddr = (PxU8*)malloc(length+PX_SERIAL_FILE_ALIGN);
	void* alignedBlock = (void*)((size_t(baseAddr) + PX_SERIAL_FILE_ALIGN)&~(PX_SERIAL_FILE_ALIGN-1));;
	data.read(alignedBlock, length);
	return alignedBlock;
}

void instanceCollectionWithBinary()
{
	PxCollection* c = createCollection();
	
	PxDefaultMemoryOutputStream stream;
	PxSerialization::serializeCollectionToBinary(stream, *c, *gSerializationRegistry);
	c->release();

#ifdef USE_CONVX
	PxDefaultMemoryOutputStream metadataStream;
	PxSerialization::dumpBinaryMetaData(metadataStream, *gSerializationRegistry);
	
	PxBinaryConverter* binaryConverter = PxSerialization::createBinaryConverter();
	binaryConverter->setReportMode(PxConverterReportMode::eNORMAL);
	
	PxDefaultMemoryInputData metaDataInStreamSrc(metadataStream.getData(), metadataStream.getSize());
	PxDefaultMemoryInputData metaDataInStreamDst(metadataStream.getData(), metadataStream.getSize());
	
	bool isMetaDataSet = binaryConverter->setMetaData(metaDataInStreamSrc, metaDataInStreamDst);
	PX_ASSERT(isMetaDataSet);
	PX_UNUSED(isMetaDataSet);
	
	PxDefaultMemoryInputData binaryDataInStream(stream.getData(), stream.getSize());
	PxDefaultMemoryOutputStream binaryDataOutStream;
	bool isConverted = binaryConverter->convert(binaryDataInStream, binaryDataInStream.getLength(), binaryDataOutStream);
	PX_ASSERT(isConverted);
	PX_UNUSED(isConverted);
	binaryConverter->release();
#endif

#ifdef USE_CONVX
	PxDefaultMemoryInputData inputStream(binaryDataOutStream.getData(), binaryDataOutStream.getSize());
#else
	PxDefaultMemoryInputData inputStream(stream.getData(), stream.getSize());
#endif

	void* alignedBlock = createAlignedBlock(inputStream, gAlignedBlock);
	c = PxSerialization::createCollectionFromBinary(alignedBlock, *gSerializationRegistry);
	gScene->addCollection(*c);
	gCollection = c;

	PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0,1,0,0), *material);
	gScene->addActor(*groundPlane);	
}


int snippetMain(int, const char*const*)
{	
	initPhysics(true);	

	printf("instance with repx data\n");
	instanceCollectionWithRepX();	

	static const PxU32 frameCount = 100;
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	
	PxCollectionExt::releaseObjects(*gCollection);

	printf("instance with binary data\n");
	instanceCollectionWithBinary();
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);

	cleanupPhysics(false);		
	printf("SnippetExtension done.\n");

	return 0;
}
