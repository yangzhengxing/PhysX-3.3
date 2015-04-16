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
// This snippet illustrates the use of simple contact reports and contact modification.
//
// It demonstrates the use of the following contact modification features:
// (1)Local mass modification by normalizing the masses of bodies in a stack of bodies demonstrating instability due to large mass ratios.
// (2)Disabling contacts through contact modification.
// (3)Modifying the contact normal through contact modification.
// (4)Adjusting separation values to adjust the amount of penetration.
// (5)Adjusting the max impulse applied in the solver.
// (6)Setting target velocities to approximate effects like conveyor belts.
// 
// ****************************************************************************

#include <vector>

#include "PxPhysicsAPI.h"

#include "../SnippetUtils/SnippetUtils.h"
#include "../SnippetCommon/SnippetPrint.h"
#include "../SnippetCommon/SnippetPVD.h"

using namespace physx;


#define PI               3.141592654f

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene		= NULL;
PxMaterial*				gMaterial	= NULL;

PxVisualDebuggerConnection*		
						gConnection	= NULL;

std::vector<PxVec3> gContactPositions;
std::vector<PxVec3> gContactImpulses;
std::vector<PxVec3> gContactLinearImpulses[2];
std::vector<PxVec3> gContactAngularImpulses[2];

struct ContactModFlags
{
	enum
	{
		eADJUST_MASS_RATIOS		= 1,
		eIGNORE_CONTACT			= 2,
		eMODIFY_NORMAL			= 4,
		eADJUST_PENETRATION		= 8,
		eMAX_IMPULSE			= 16,
		eTARGET_VELOCITY		= 32
	};
};



PxFilterFlags contactReportFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0, 
										PxFilterObjectAttributes attributes1, PxFilterData filterData1,
										PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	PX_UNUSED(attributes0);
	PX_UNUSED(attributes1);
	PX_UNUSED(filterData0);
	PX_UNUSED(filterData1);
	PX_UNUSED(constantBlockSize);
	PX_UNUSED(constantBlock);

	// all initial and persisting reports for everything, with per-point data
	pairFlags = PxPairFlag::eRESOLVE_CONTACTS
			  |	PxPairFlag::eNOTIFY_TOUCH_FOUND 
			  | PxPairFlag::eNOTIFY_TOUCH_PERSISTS
			  | PxPairFlag::eNOTIFY_CONTACT_POINTS
			  | PxPairFlag::eMODIFY_CONTACTS;
	return PxFilterFlag::eDEFAULT;
}

static void adjustMassRatios(const PxRigidDynamic& dynamic0, const PxRigidDynamic& dynamic1, const PxReal maxMassRatio, PxContactModifyPair& pair)
{
	PxReal mass0 = dynamic0.getMass();
	PxReal mass1 = dynamic1.getMass();

	if(mass0 > mass1)
	{
		//dynamic0 is heavier than dynamic1 so we will locally increase the mass of dynamic1 
		//to be half the mass of dynamic0.
		PxReal ratio = mass0/mass1;
		if(ratio > maxMassRatio)
		{
			PxReal invMassScale = maxMassRatio/ratio;
			pair.contacts.setInvMassScale1(invMassScale);
			pair.contacts.setInvInertiaScale1(invMassScale);
		}
	}
	else
	{
		//dynamic1 is heavier than dynamic0 so we will locally increase the mass of dynamic0 
		//to be half the mass of dynamic1.
		PxReal ratio = mass1/mass0;
		if(ratio > maxMassRatio)
		{
			PxReal invMassScale = maxMassRatio/ratio;
			pair.contacts.setInvMassScale0(invMassScale);
			pair.contacts.setInvInertiaScale0(invMassScale);
		}
	}
}

static void ignoreContacts(PxContactModifyPair& pair)
{
	for(PxU32 i = 0; i < pair.contacts.size(); ++i)
	{
		pair.contacts.ignore(i);
	}
}

static void rotateNormals(PxContactModifyPair& pair, const PxQuat& rotation)
{
	for(PxU32 i = 0; i < pair.contacts.size(); ++i)
	{
		PxVec3 normal = pair.contacts.getNormal(i);
		pair.contacts.setNormal(i, rotation.rotate(normal));
	}
}

static void allowPenetration(PxContactModifyPair& pair, const PxReal allowedPenetration)
{
	for(PxU32 i = 0; i < pair.contacts.size(); ++i)
	{
		pair.contacts.setSeparation(i, pair.contacts.getSeparation(i) + allowedPenetration);
	}
}

static void setMaxImpulse(PxContactModifyPair& pair, const PxReal maxImpulse)
{
	for(PxU32 i = 0; i < pair.contacts.size(); ++i)
	{
		pair.contacts.setMaxImpulse(i, maxImpulse);
	}
}

static void setTargetVelocity(PxContactModifyPair& pair, const PxVec3& targetVelocity)
{
	for(PxU32 i = 0; i < pair.contacts.size(); ++i)
	{
		pair.contacts.setTargetVelocity(i, targetVelocity);
	}
}


class ContactModifyCallback: public PxContactModifyCallback
{
	void onContactModify(PxContactModifyPair* const pairs, PxU32 count)
	{
		//We define a maximum mass ratio that we will accept in this test, which is a ratio of 2
		const PxReal maxMassRatio = 2.f;
		//The quaternion used to rotate normals. We rotate around z axis by -60 degrees.
		const PxQuat rotation(-60.f/180.f * PI, PxVec3(0.f, 0.f, 1.f));
		//The amount of allowed penetration. When adjusting penetration, we add this to the penetration value such that the pair penetrate by 0.15 units.
		const PxReal allowedPenetration = 0.15f;
		//The maximum impulse allows to be applied.
		const PxReal maxImpulse = 2.f;
		//The target velocity
		const PxVec3 targetVelocity(0.f, 0.f, 2.f);

		for(PxU32 i = 0; i < count; i++)
		{

			//We use the userData as a simple mechanism to carry what we want our contact modification to do
			PxU32 flags = static_cast<PxU32>(reinterpret_cast<size_t>(pairs[i].actor[0]->userData) | reinterpret_cast<size_t>(pairs[i].actor[1]->userData));			

			if(flags & ContactModFlags::eADJUST_MASS_RATIOS)
			{
				const PxRigidDynamic* dynamic0 = pairs[i].actor[0]->is<PxRigidDynamic>();
				const PxRigidDynamic* dynamic1 = pairs[i].actor[1]->is<PxRigidDynamic>();
				if(dynamic0 != NULL && dynamic1 != NULL)
				{
					//We only want to perform local mass modification between 2 dynamic bodies because we intend on 
					//normalizing the mass ratios between the pair within a tolerable range
					adjustMassRatios(*dynamic0, *dynamic1, maxMassRatio, pairs[i]);
					
				}
			}
			else if(flags & ContactModFlags::eIGNORE_CONTACT)
			{
				ignoreContacts(pairs[i]);
			}
			else if (flags & ContactModFlags::eMODIFY_NORMAL)
			{
				rotateNormals(pairs[i], rotation);
			}
			else if (flags & ContactModFlags::eADJUST_PENETRATION)
			{
				allowPenetration(pairs[i], allowedPenetration);
			}
			else if (flags & ContactModFlags::eMAX_IMPULSE)
			{
				setMaxImpulse(pairs[i], maxImpulse);
			}
			else if (flags & ContactModFlags::eTARGET_VELOCITY)
			{
				setTargetVelocity(pairs[i], targetVelocity);
			}
		}
	}
};

ContactModifyCallback gContactModifyCallback;

PxU32 extractContactsWithMassScale(const PxContactPair& pair, PxContactPairPoint* userBuffer, PxU32 bufferSize, PxReal& invMassScale0, PxReal& invMassScale1)
{
	const PxU8* stream = pair.contactStream;

	PxU32 nbContacts = 0;

	if(pair.contactCount && bufferSize)
	{
		PxContactStreamIterator iter((PxU8*)stream, pair.contactStreamSize);

		stream += ((pair.contactStreamSize + 15) & ~15);

		const PxReal* impulses = reinterpret_cast<const PxReal*>(stream);

		PxU32 flippedContacts = (pair.flags & PxContactPairFlag::eINTERNAL_CONTACTS_ARE_FLIPPED);
		PxU32 hasImpulses = (pair.flags & PxContactPairFlag::eINTERNAL_HAS_IMPULSES);


		invMassScale0 = iter.getInvMassScale0();
		invMassScale1 = iter.getInvMassScale1();
		while(iter.hasNextPatch())
		{
			iter.nextPatch();
			while(iter.hasNextContact())
			{
				iter.nextContact();
				PxContactPairPoint& dst = userBuffer[nbContacts];
				dst.position = iter.getContactPoint();
				dst.separation = iter.getSeparation();
				dst.normal = iter.getContactNormal();
				if (!flippedContacts)
				{
					dst.internalFaceIndex0 = iter.getFaceIndex0();
					dst.internalFaceIndex1 = iter.getFaceIndex1();
				}
				else
				{
					dst.internalFaceIndex0 = iter.getFaceIndex1();
					dst.internalFaceIndex1 = iter.getFaceIndex0();
				}

				if (hasImpulses)
				{
					PxReal impulse = impulses[nbContacts];
					dst.impulse = dst.normal * impulse;
				}
				else
					dst.impulse = PxVec3(0.0f);
				++nbContacts;
				if(nbContacts == bufferSize)
					return nbContacts;
			}
		}
	}

	return nbContacts;
}



class ContactReportCallback: public PxSimulationEventCallback
{
	void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count)	{ PX_UNUSED(constraints); PX_UNUSED(count); }
	void onWake(PxActor** actors, PxU32 count)							{ PX_UNUSED(actors); PX_UNUSED(count); }
	void onSleep(PxActor** actors, PxU32 count)							{ PX_UNUSED(actors); PX_UNUSED(count); }
	void onTrigger(PxTriggerPair* pairs, PxU32 count)					{ PX_UNUSED(pairs); PX_UNUSED(count); }
	void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) 
	{
		PX_UNUSED((pairHeader));
		std::vector<PxContactPairPoint> contactPoints;

		PxU32 flags = static_cast<PxU32>(reinterpret_cast<size_t>(pairHeader.actors[0]->userData) | reinterpret_cast<size_t>(pairHeader.actors[1]->userData));

		PxRigidDynamic* dyn0 = pairHeader.actors[0]->is<PxRigidDynamic>();
		PxRigidDynamic* dyn1 = pairHeader.actors[1]->is<PxRigidDynamic>();
	
		if(dyn0 && dyn1)
		{
			for(PxU32 i=0;i<nbPairs;i++)
			{
				PxU32 contactCount = pairs[i].contactCount;
				
				if(flags & ContactModFlags::eADJUST_MASS_RATIOS)
				{
					if(contactCount)
					{
						contactPoints.resize(contactCount);
						PxReal invMassScale[2];
						extractContactsWithMassScale(pairs[i], &contactPoints[0], contactCount, invMassScale[0], invMassScale[1]);

						for(PxU32 j=0;j<contactCount;j++)
						{
							gContactPositions.push_back(contactPoints[j].position);
							//Push back reported contact impulses
							gContactImpulses.push_back(contactPoints[j].impulse);

							//Compute the effective linear/angular impulses for each body.
							//Note that the local mass scaling permits separate scales for invMass and invInertia.
							for(PxU32 k = 0; k < 2; ++k)
							{
								const PxRigidDynamic* dynamic = pairHeader.actors[k]->is<PxRigidDynamic>();
								PxVec3 linImpulse(0.f), angImpulse(0.f);
								if(dynamic != NULL)
								{
									PxRigidBodyExt::computeLinearAngularImpulse(*dynamic, dynamic->getGlobalPose(), contactPoints[j].position, 
										k == 0 ? contactPoints[j].impulse : -contactPoints[j].impulse, invMassScale[k], invMassScale[k], linImpulse, angImpulse);
								}
								gContactLinearImpulses[k].push_back(linImpulse);
								gContactAngularImpulses[k].push_back(angImpulse);
							}
						}
					}
				}
			}
		}
	}
};

ContactReportCallback gContactReportCallback;

void createStack(const PxTransform& t, PxU32 size, PxReal halfExtent)
{
	PxShape* shape = gPhysics->createShape(PxBoxGeometry(halfExtent, halfExtent, halfExtent), *gMaterial);
	for(PxU32 i=0; i<size;i++)
	{
		PxTransform localTm(PxVec3(0, PxReal(i*2+1), 0) * halfExtent);
		PxRigidDynamic* body = gPhysics->createRigidDynamic(t.transform(localTm));
		body->attachShape(*shape);
		PxRigidBodyExt::updateMassAndInertia(*body, (i+1)*(i+1)*(i+1)*10.0f);
		gScene->addActor(*body);
	}
	shape->release();
}

PxRigidActor* createBox(const PxTransform& t, const PxVec3& halfExtent, PxReal density)
{
	PxShape* shape = gPhysics->createShape(PxBoxGeometry(halfExtent), *gMaterial);
	PxRigidActor* actor;
	if(density == 0.f)
	{
		PxRigidStatic* body = gPhysics->createRigidStatic(t);
		body->attachShape(*shape);
		actor = body;		
	}
	else
	{
		PxRigidDynamic* body = gPhysics->createRigidDynamic(t);
		body->attachShape(*shape);
		PxRigidBodyExt::updateMassAndInertia(*body, 1);
		actor = body;
	}
	gScene->addActor(*actor);
	shape->release();
	return actor;
}

void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
	PxProfileZoneManager* profileZoneManager = &PxProfileZoneManager::createProfileZoneManager(gFoundation);
	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,profileZoneManager);
	PxInitExtensions(*gPhysics);

	if(gPhysics->getPvdConnectionManager())
	{
		gPhysics->getVisualDebugger()->setVisualDebuggerFlag(PxVisualDebuggerFlag::eTRANSMIT_CONTACTS, true);
		gConnection = PxVisualDebuggerExt::createConnection(gPhysics->getPvdConnectionManager(), PVD_HOST, 5425, 10);
	}

	PxU32 numWorkers = PxMax(PxI32(SnippetUtils::getNbPhysicalCores())-1, 0);
	gDispatcher = PxDefaultCpuDispatcherCreate(numWorkers);
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.gravity = PxVec3(0, -9.81f, 0);
	sceneDesc.filterShader	= contactReportFilterShader;			
	sceneDesc.simulationEventCallback = &gContactReportCallback;	
	sceneDesc.contactModifyCallback = &gContactModifyCallback;
	gScene = gPhysics->createScene(sceneDesc);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0,1,0,0), *gMaterial);
	gScene->addActor(*groundPlane);
	createStack(PxTransform(PxVec3(0,0.0f,10.0f)), 5, 2.0f);

	PxU32 nbActors = gScene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC);
	//This flags this body to normalize masses by using local mass modification, ensuring stability despite large mass ratios
	for(PxU32 i = 0; i < nbActors; ++i)
	{
		PxActor* actor;
		gScene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC, &actor, 1, i);
		PxRigidDynamic* dyn = actor->is<PxRigidDynamic>();
		dyn->userData = (void*)ContactModFlags::eADJUST_MASS_RATIOS;
	}

	//This is the same set-up as above but without local mass modification. The expectation is that this stack will collapse
	createStack(PxTransform(PxVec3(20.f,0.0f,10.0f)), 5, 2.0f);

	//We raise a flag on ignoreBox to trigger contact modification to ignore this pair.
	PxRigidActor* ignoreBox = createBox(PxTransform(PxVec3(0.f, 0.5f, 4.f)), PxVec3(2.f, 0.5f, 2.f), 0.f);
	ignoreBox->userData = (void*)ContactModFlags::eIGNORE_CONTACT;
	createBox(PxTransform(0.f, 2.f, 4.f), PxVec3(1.f), 1.f);

	//This static box is flagged to have its normal adjusted. We rotate the normal by 60 degrees so the expectation is that the dynamic box will slide off this surface
	PxRigidActor* modifyNormalBox = createBox(PxTransform(PxVec3(0.f, 0.5f, 0.f)), PxVec3(2.f, 0.5f, 2.f), 0.f);
	modifyNormalBox->userData = (void*)ContactModFlags::eMODIFY_NORMAL;
	createBox(PxTransform(0.f, 2.f, 0.f), PxVec3(1.f), 1.f);

	//This static box is flagged to have its penetration adjusted. The expectation is that the boxes will be visibly penetrated by 0.15 units.
	PxRigidActor* modifyPenBox = createBox(PxTransform(PxVec3(0.f, 0.5f, -4.f)), PxVec3(0.5f, 0.5f, 2.f), 0.f);
	modifyPenBox->userData = (void*)ContactModFlags::eADJUST_PENETRATION;
	createBox(PxTransform(0.f, 2.f, -4.f), PxVec3(1.f), 1.f);

	//This static box is flagged to have its max impulse clamped to 1. The expectation is that the dynamic box will slowly de-penetrate from the static box.
	PxRigidActor* maxImpulseBox = createBox(PxTransform(PxVec3(0.f, 0.75f, -8.f)), PxVec3(2.f, 0.75f, 2.f), 0.f);
	maxImpulseBox->userData = (void*)ContactModFlags::eMAX_IMPULSE;
	createBox(PxTransform(0.f, 1.25f, -8.f), PxVec3(1.f), 1.f);

	//This static box is flagged to have a target velocity. The expectation is that the dynamic box will travel along the static box as if it were a conveyor belt.
	PxRigidActor* conveyorBelt = createBox(PxTransform(PxVec3(-8.f, 1.f, 0.f)), PxVec3(3.f, 1.f, 8.f), 0.f);
	conveyorBelt->userData = (void*)ContactModFlags::eTARGET_VELOCITY;
	createBox(PxTransform(PxVec3(-8.f, 3.f, -7.f)), PxVec3(1.f), 1.f);

}

void stepPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	gContactPositions.clear();
	gContactImpulses.clear();

	gScene->simulate(1.0f/60.0f);
	gScene->fetchResults(true);
	printf("%d contact reports\n", PxU32(gContactPositions.size()));
}
	
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	gScene->release();
	gDispatcher->release();
	PxCloseExtensions();
	PxProfileZoneManager* profileZoneManager = gPhysics->getProfileZoneManager();

	if(gConnection != NULL)
		gConnection->release();

	gPhysics->release();
	profileZoneManager->release();
	gFoundation->release();
	
	printf("SnippetContactModification done.\n");
}

int snippetMain(int, const char*const*)
{
#ifdef RENDER_SNIPPET
	extern void renderLoop();
	renderLoop();
#else
	initPhysics(false);
	for(PxU32 i=0; i<250; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}

