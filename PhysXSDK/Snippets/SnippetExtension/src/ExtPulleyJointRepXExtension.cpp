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

#include <stdio.h>
#include "ExtPulleyJoint.h"
#include "ExtConstraintHelper.h"
#include "CmRenderOutput.h"
#include "CmConeLimitHelper.h"
#include "PxTolerancesScale.h"
#include "CustomPulleyJoint.h"
#include "PxRepXSerializer.h"
#include "PxSerialization.h"
#include "PxMetaDataObjects.h"
#include "PxSnippetExtensionMetaDataObjects.h"
#include "ExtPulleyJointExtension.h"
#include "PxJointRepXSerializer.h"
#include "SnRepXSerializerImpl.h"

using namespace physx;
using namespace Ext;
using namespace Sn;
using namespace Cm;

namespace physx { 
	static inline CustomPulleyJoint* createJoint(PxPhysics& physics, 
					PxRigidActor* actor0, const PxTransform& localFrame0, 
					PxRigidActor* actor1, const PxTransform& localFrame1)
	{
		return CustomPulleyJointCreate( physics, actor0, localFrame0, actor1, localFrame1 );
	}
	
	template<>
	PxRepXObject PxJointRepXSerializer<CustomPulleyJoint>::fileToObject( XmlReader& inReader, XmlMemoryAllocator& inAllocator, PxRepXInstantiationArgs& inArgs, PxCollection* inCollection )
	{
		PxRigidActor* actor0 = NULL;
		PxRigidActor* actor1 = NULL;
		PxTransform localPose0 = PxTransform(PxIdentity);
		PxTransform localPose1 = PxTransform(PxIdentity);
		bool ok = true;
		if ( inReader.gotoChild( "Actors" ) )
		{
			ok = readReference<PxRigidActor>( inReader, *inCollection, "actor0", actor0 );
			ok &= readReference<PxRigidActor>( inReader, *inCollection, "actor1", actor1 );
			inReader.leaveChild();
		}
		CustomPulleyJoint* theJoint = !ok ? NULL : createJoint( inArgs.physics, actor0, localPose0, actor1, localPose1 );
		
		if ( theJoint )
			this->fileToObjectImpl( theJoint, inReader, inAllocator, inArgs, inCollection );
		return createRepXObject( theJoint );
	}

	template<>
	void PxJointRepXSerializer<CustomPulleyJoint>::objectToFileImpl(const CustomPulleyJoint* inObj, PxCollection* collection, XmlWriter& writer , MemoryBuffer& buffer, PxRepXInstantiationArgs& /*inArgs*/)
	{
		writeAllProperties( inObj, writer, buffer, *collection );
	}
}

void registerPulleyJointRepXExtension(PxSerializationRegistry& sr)
{
	sr.registerRepXSerializer(PulleyJointConcreteType::eUSER_PULLEY_JOINT, PX_NEW_REPX_SERIALIZER(PxJointRepXSerializer<CustomPulleyJoint>));
}
	
void unregisterPulleyJointRepXExtension(physx::PxSerializationRegistry& sr)
{
	PX_DELETE_REPX_SERIALIZER(sr.unregisterRepXSerializer(PulleyJointConcreteType::eUSER_PULLEY_JOINT));
}
