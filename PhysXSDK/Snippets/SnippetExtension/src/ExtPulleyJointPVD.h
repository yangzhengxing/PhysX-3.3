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


#ifndef CUSTOM_PULLEYJOINTCONSTRAINT_PVD_H
#define CUSTOM_PULLEYJOINTCONSTRAINT_PVD_H

#if PX_SUPPORT_VISUAL_DEBUGGER

#include "PxExtensionMetaDataObjects.h"
#include "PxSnippetExtensionMetaDataObjects.h"

#include "PxVisualDebuggerExt.h"
#include "PvdTypeNames.h"
#include "PvdObjectModelBaseTypes.h"

namespace physx { namespace debugger { namespace comm {
	class PvdDataStream;
}}}

namespace physx
{
	namespace debugger {
	
	#define DEFINE_NATIVE_PVD_PHYSX3_TYPE_MAP( type ) DEFINE_PVD_TYPE_NAME_MAP( type, "physx3", #type )

	DEFINE_NATIVE_PVD_PHYSX3_TYPE_MAP(CustomPulleyJoint);
	DEFINE_NATIVE_PVD_PHYSX3_TYPE_MAP(CustomPulleyJointGeneratedValues);
	
	
#undef DEFINE_NATIVE_PVD_PHYSX3_TYPE_MAP

}

namespace Ext
{
	void sendUserClassDescriptions(physx::debugger::comm::PvdDataStream& inStream);
}
}

#endif

#endif