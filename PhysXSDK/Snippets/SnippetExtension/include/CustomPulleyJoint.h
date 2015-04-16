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


#ifndef CUSTOM_PULLEYJOINT_H
#define CUSTOM_PULLEYJOINT_H
/** \addtogroup extensions
  @{
*/

#include "extensions/PxJoint.h"

#ifndef PX_DOXYGEN
namespace physx
{
#endif

class CustomPulleyJoint;

struct PulleyJointConcreteType
{
	enum Enum
	{
		eUSER_PULLEY_JOINT = PxConcreteType::eFIRST_USER_EXTENSION 
	};
};

PX_DEFINE_TYPEINFO(CustomPulleyJoint,			PulleyJointConcreteType::eUSER_PULLEY_JOINT);


CustomPulleyJoint*		CustomPulleyJointCreate(PxPhysics& physics, 
									   PxRigidActor* actor0, const PxTransform& localFrame0, 
									   PxRigidActor* actor1, const PxTransform& localFrame1);

class CustomPulleyJoint : public PxJoint
{
public:	
	virtual void	setDistance(PxReal totalDistance) = 0;
	virtual PxReal	getDistance()  const = 0;
	
	virtual void	setRatio(PxReal ratio) = 0;
	virtual PxReal	getRatio()  const = 0;

	virtual void	setStiffness(PxReal stiffness) = 0;
	virtual PxReal	getStiffness()  const = 0;

	virtual void	setDamping(PxReal damping) = 0;
	virtual PxReal	getDamping()  const = 0;

	virtual void	setTolerance(PxReal tolerance) = 0;
	virtual PxReal	getTolerance()  const = 0;

	/**
	\brief Returns string name of dynamic type.  used for serialization
	\return	Class name of most derived type of this object.
	*/
	virtual	const char* getConcreteTypeName() const { return "CustomPulleyJoint"; }	
	
protected:
	//serializable

	/**
	\brief Constructor setting concrete type and base flags.
	*/
	CustomPulleyJoint(PxType concreteType, PxBaseFlags baseFlags) : PxJoint(concreteType, baseFlags) {}
	
	/**
	\brief Deserialization constructor setting base flags.
	*/
	CustomPulleyJoint(PxBaseFlags baseFlags) : PxJoint(baseFlags) {}

	/**
	\brief Returns whether a given type name matches with the type of this instance
	*/
	virtual	bool isKindOf(const char* name) const { return !strcmp("CustomPulleyJoint", name) || PxJoint::isKindOf(name); }

	//~serializable
};


#ifndef PX_DOXYGEN
} // namespace physx
#endif
/** @} */
#endif