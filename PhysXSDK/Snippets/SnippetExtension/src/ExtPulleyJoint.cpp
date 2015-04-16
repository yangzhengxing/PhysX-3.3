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

#include "ExtPulleyJoint.h"
#include "PxTolerancesScale.h"
#include "CmUtils.h"

using namespace physx;
using namespace Ext;

CustomPulleyJoint* physx::CustomPulleyJointCreate(PxPhysics& physics, 
									   PxRigidActor* actor0, const PxTransform& localFrame0, 
									   PxRigidActor* actor1, const PxTransform& localFrame1)
{
	void* buf  = shdfnd::ReflectionAllocator<PulleyJoint>().allocate(sizeof(PulleyJoint), __FILE__, __LINE__);
	Cm::markSerializedMem(buf, sizeof(PulleyJoint));
	PulleyJoint* j = PX_PLACEMENT_NEW(buf, PulleyJoint)(physics, actor0, localFrame0,  actor1, localFrame1);

	if(j->attach(physics, actor0, actor1))
		return j;

	PX_DELETE(j);
	return NULL;
}

namespace
{
void PulleyJointVisualize(PxConstraintVisualizer&		viz,
						 const void*					constantBlock,
						 const PxTransform&				body0Transform,
						 const PxTransform&				body1Transform,
						 PxU32							/*flags*/)
{
	const PulleyJointData& data = *reinterpret_cast<const PulleyJointData*>(constantBlock);

	PxTransform cA2w = body0Transform * data.c2b[0];
	PxTransform cB2w = body1Transform * data.c2b[1];
	viz.visualizeJointFrames(cA2w, cB2w);

	// pulley points
	viz.visualizeJointFrames(PxTransform(data.pulley[0]), PxTransform(data.pulley[1]));
}

void PulleyJointProject(const void* /*constantBlock*/,
					   PxTransform& /*bodyAToWorld*/,
					   PxTransform& /*bodyBToWorld*/,
					   bool /*projectToA*/)
{
}
};

void PulleyJoint::setDistance(PxReal totalDistance)
{
	data().distance = totalDistance; 
	markDirty();
}

PxReal PulleyJoint::getDistance() const
{
	return data().distance; 
}

void PulleyJoint::setRatio(PxReal ratio)
{
	data().ratio = ratio; 
	markDirty();
}

PxReal PulleyJoint::getRatio() const
{
	return data().ratio; 
}

void PulleyJoint::setStiffness(PxReal stiffness)
{
	data().stiffness = stiffness; 
	markDirty();
}

PxReal PulleyJoint::getStiffness()	const
{
	return data().stiffness;
}

void PulleyJoint::setDamping(PxReal damping)
{
	data().damping = damping; 
	markDirty();
}

PxReal PulleyJoint::getDamping() const
{
	return data().damping;
}

void PulleyJoint::setTolerance(PxReal tolerance)	
{
	data().tolerance = tolerance; 
	markDirty();
}

PxReal PulleyJoint::getTolerance() const
{
	return data().tolerance;
}

bool PulleyJoint::attach(PxPhysics &physics, PxRigidActor* actor0, PxRigidActor* actor1)
{
	mPxConstraint = physics.createConstraint(actor0, actor1, *this, sShaders, sizeof(PulleyJointData));
	return mPxConstraint != NULL;
}

PulleyJoint::PulleyJoint(PxPhysics& physics, 
			PxRigidActor* actor0, const PxTransform& localFrame0, 
			PxRigidActor* actor1, const PxTransform& localFrame1)
: PulleyJointT(PulleyJointConcreteType::eUSER_PULLEY_JOINT, PxBaseFlag::eOWNS_MEMORY | PxBaseFlag::eIS_RELEASABLE)
{
	PulleyJointData* data = reinterpret_cast<PulleyJointData*>(PX_ALLOC(sizeof(PulleyJointData), PX_DEBUG_EXP("PulleyJointData")));
	Cm::markSerializedMem(data, sizeof(PulleyJointData));	
	mData = data;
	
	initCommonData(*data,actor0, localFrame0, actor1, localFrame1);
	
	data->pulley[0] = PxVec3(-1,7,0);
	data->pulley[1] = PxVec3(1,7,0);
	data->distance = 4.f;
	data->ratio = 2.f;

	data->stiffness = 0.0f;		
	data->damping = 0.0f;
	data->tolerance = 0.025f * physics.getTolerancesScale().length;
}

void PulleyJoint::exportExtraData(PxSerializationContext& context)
{
	if(mData)
	{
		context.alignData();
		context.writeData(mData, sizeof(PulleyJointData));
	}
	context.writeName(mName);
}

void PulleyJoint::importExtraData(PxDeserializationContext& context)
{
	if(mData)
	{
		context.alignExtraData();
		mData = context.readExtraData<PulleyJointData>();		
	}
	context.readName(mName);
}

void PulleyJoint::resolveReferences(PxDeserializationContext& context)
{
	setPxConstraint(resolveConstraintPtr(context, getPxConstraint(), getConnector(), sShaders));	
}

PulleyJoint* PulleyJoint::createObject(PxU8*& address, PxDeserializationContext& context)
{
	PulleyJoint* obj = new (address) PulleyJoint(PxBaseFlag::eIS_RELEASABLE);
	address += sizeof(PulleyJoint);	
	obj->importExtraData(context);
	obj->resolveReferences(context);
	return obj;
}

PxConstraintShaderTable Ext::PulleyJoint::sShaders = { Ext::PulleyJointSolverPrep, 0, 0, PulleyJointProject, PulleyJointVisualize };