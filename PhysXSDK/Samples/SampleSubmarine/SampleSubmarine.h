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


#ifndef SAMPLE_SUBMARINE_H
#define SAMPLE_SUBMARINE_H

#include "PhysXSample.h"
#include "PxSimulationEventCallback.h"

namespace physx
{
	class PxJoint;
}

class Crab;
class ParticleSystem;
class SubmarineCameraController;

struct ClassType
{
	enum Type
	{
		eSEA_MINE,
		eCRAB,
	};

	ClassType(const PxU32 type): mType(type)	{}
	PxU32 getType() const						{ return mType; }

	const PxU32 mType;
private:
	ClassType& operator=(const ClassType&);
};

struct FilterGroup
{
	enum Enum
	{
		eSUBMARINE		= (1 << 0),
		eMINE_HEAD		= (1 << 1),
		eMINE_LINK		= (1 << 2),
		eCRAB			= (1 << 3),
		eHEIGHTFIELD	= (1 << 4),
	};
};

struct Seamine: public ClassType, public SampleAllocateable
{
	Seamine() : ClassType(ClassType::eSEA_MINE), mMineHead(NULL) {}

	std::vector<PxRigidDynamic*>	mLinks;
	PxRigidDynamic*					mMineHead;
	
};

class SampleSubmarine : public PhysXSample, public PxSimulationEventCallback
{
	friend class Crab;
	public:
											SampleSubmarine(PhysXSampleApplication& app);
	virtual									~SampleSubmarine();

	///////////////////////////////////////////////////////////////////////////////

	// Implements PxSimulationEventCallback
	virtual void							onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);
	virtual void							onTrigger(PxTriggerPair* pairs, PxU32 count);
	virtual void							onConstraintBreak(PxConstraintInfo*, PxU32) {}
	virtual void							onWake(PxActor** , PxU32 ) {}
	virtual void							onSleep(PxActor** , PxU32 ){}

	///////////////////////////////////////////////////////////////////////////////

	// Implements SampleApplication
	virtual	void							onInit();
    virtual	void						    onInit(bool restart) { onInit(); }
	virtual	void							onShutdown();
	virtual	void							onTickPreRender(float dtime);
	virtual void							onDigitalInputEvent(const SampleFramework::InputEvent& , bool val);
	virtual void							onAnalogInputEvent(const SampleFramework::InputEvent& , float val);
	virtual void							onPointerInputEvent(const SampleFramework::InputEvent& ie, physx::PxU32 x, physx::PxU32 y, physx::PxReal dx, physx::PxReal dy, bool val);

	///////////////////////////////////////////////////////////////////////////////

	// Implements PhysXSampleApplication
	virtual void							helpRender(PxU32 x, PxU32 y, PxU8 textAlpha);
	virtual	void							descriptionRender(PxU32 x, PxU32 y, PxU8 textAlpha);
	virtual	void							customizeSample(SampleSetup&);
	virtual	void							customizeSceneDesc(PxSceneDesc&);
	virtual void							customizeRender();
	
	// called at end of a simulation substep
	virtual	void							onSubstep(float dtime);
	// called before the simulation begins, useful for setting up 
	// tasks that need to finish before the completionTask can be called
	virtual void							onSubstepSetup(float dtime, PxBaseTask* completionTask);	
	// called once the simulation has begun running
	virtual	void							onSubstepStart(float dtime);

	virtual void							collectInputEvents(std::vector<const SampleFramework::InputEvent*>& inputEvents);

	///////////////////////////////////////////////////////////////////////////////

	void                createMaterials();
	Seamine*			createSeamine(const PxVec3& position, PxReal height);
	PxRigidDynamic* 	createSubmarine(const PxVec3& inPosition, const PxReal yRot);
	void				explode(PxRigidActor* actor, const PxVec3& explosionPos, const PxReal explosionStrength);
	void				handleInput();
	PxRigidActor*		loadTerrain(const char* name, const PxReal heightScale, const PxReal rowScale, const PxReal columnScale);

	void				createDynamicActors();
	void				resetScene();

	std::vector<void*>&	getCrabsMemoryDeleteList() { return mCrabsMemoryDeleteList; }

	private:
			std::vector<PxJoint*>			mJoints;
			std::vector<Seamine*>			mMinesToExplode;
			std::vector<Seamine*>			mSeamines;
			std::vector<Crab*>				mCrabs;
			std::vector<void*>				mCrabsMemoryDeleteList;
			PxRigidDynamic*					mSubmarineActor;
			RenderMaterial*					mSeamineMaterial;
			PxRigidDynamic*					mCameraAttachedToActor;

			SubmarineCameraController*		mSubmarineCameraController;

#ifdef RENDERER_PSP2
			RenderMaterial*					mSubmarineMaterial;
			RenderMaterial*					mTreasureMaterial;			
#endif

};

#endif
