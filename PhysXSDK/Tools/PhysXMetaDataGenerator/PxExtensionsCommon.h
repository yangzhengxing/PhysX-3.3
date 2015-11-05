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
#ifndef PX_EXTENSIONS_COMMON_H
#define PX_EXTENSIONS_COMMON_H

#include "PxPhysXConfig.h"

struct PropertyOverride
{
	const char* TypeName;
	const char* PropName;
	const char* OverridePropName;
	PropertyOverride( const char* tn, const char* pn, const char* opn )
		: TypeName( tn )
		, PropName( pn )
		, OverridePropName( opn )
	{
	}
};

//Property overrides will output this exact property name instead of the general
//property name that would be used.  The properties need to have no template arguments
//and exactly the same initialization as the classes they are overriding.
struct DisabledPropertyEntry
{
	const char* mTypeName;
	const char* mPropertyName;
	DisabledPropertyEntry( const char* inTypeName, const char* inValueName )
		: mTypeName( inTypeName )
		, mPropertyName( inValueName )
	{
	}
};


struct CustomProperty
{
	const char* mPropertyType;
	const char* mTypeName;
	const char* mValueStructDefinition;
	const char* mValueStructInit;

	CustomProperty( const char* inTypeName, const char* inName, const char* inPropertyType, const char* valueStructDefinition, const char* valueStructInit )
		: mPropertyType( inPropertyType )
		, mTypeName( inTypeName )
		, mValueStructDefinition( valueStructDefinition )
		, mValueStructInit( valueStructInit )
	{
	}
};

#endif // PX_EXTENSIONS_COMMON_H
