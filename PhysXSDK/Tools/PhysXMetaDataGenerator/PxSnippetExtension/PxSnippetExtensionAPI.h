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
#ifndef PX_SNIPPET_EXTENSIOIN_API  
#define PX_SNIPPET_EXTENSIOIN_API

#include "PxExtensionsCommon.h"


static const char* gUserPhysXTypes[] = 
{
	"CustomPulleyJoint",
};

static const char* gRequiredPhysXTypes[] = 
{
	"PxJoint",	
};

//We absolutely never generate information about these types, even if types
//we do care about are derived from these types.
static const char* gAvoidedPhysXTypes[] = 
{
    "PxSerializable",
    "PxObservable",
	"PxBase",
    "PxBaseFlag::Enum",
};

#include "extensions/PxExtensionsAPI.h"
#include "CustomPulleyJoint.h"
#endif
