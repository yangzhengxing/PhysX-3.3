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

// suppress LNK4221
#include "PxPreprocessor.h"
#include "PxVisualDebugger.h"
PX_DUMMY_SYMBOL

#if PX_SUPPORT_VISUAL_DEBUGGER

#include "ExtPulleyJointPVD.h"
#include "ExtPulleyJoint.h"
#include "ExtVisualDebugger.h"

#include "PvdMetaDataDefineProperties.h"
#include "PvdMetaDataPropertyVisitor.h"
#include "PvdTypeNames.h"
#include "PvdDataStream.h"

#include "CustomPulleyJoint.h"

namespace physx
{
namespace Ext
{
	using namespace Pvd;
	template<typename TObjType, typename TOperator>
	static inline void visitUserPvdInstanceProperties( TOperator inOperator )
	{
		PxClassInfoTraits<TObjType>().Info.visitInstanceProperties( makePvdPropertyFilter( inOperator ), 0 );	
	}

	template<typename TObjType>
	static void registerUserProperties( PvdDataStream& inStream )
	{
		inStream.createClass<TObjType>();
		PvdPropertyDefinitionHelper& theHelper( inStream.getPropertyDefinitionHelper() );
		PvdClassInfoDefine theDefinitionObj( theHelper, getPvdNamespacedNameForType<TObjType>() );
		visitUserPvdInstanceProperties<TObjType>( theDefinitionObj );
	}

	template<typename TObjType, typename TOperator>
	static inline void visitUserPvdProperties( TOperator inOperator )
	{
		PvdPropertyFilter<TOperator> theFilter( makePvdPropertyFilter( inOperator ) );
		PxU32 thePropCount = PxClassInfoTraits<TObjType>().Info.visitBaseProperties( theFilter );
		PxClassInfoTraits<TObjType>().Info.visitInstanceProperties( theFilter, thePropCount );
	}


	template<typename TObjType, typename TValueStructType>
	static void registerUserPropertiesAndValueStruct( PvdDataStream& inStream )
	{
		inStream.createClass<TObjType>();
		inStream.deriveClass<PxJoint,TObjType>();
		PvdPropertyDefinitionHelper& theHelper( inStream.getPropertyDefinitionHelper() );
		{
			PvdClassInfoDefine theDefinitionObj( theHelper, getPvdNamespacedNameForType<TObjType>() );
			visitUserPvdInstanceProperties<TObjType>( theDefinitionObj );
		}
		{
			PvdClassInfoValueStructDefine theDefinitionObj( theHelper );
			visitUserPvdProperties<TObjType>( theDefinitionObj );
			theHelper.addPropertyMessage<TObjType,TValueStructType>();
		}
	}

	void sendUserClassDescriptions(physx::debugger::comm::PvdDataStream& inStream)
	{
		registerUserPropertiesAndValueStruct<CustomPulleyJoint,CustomPulleyJointGeneratedValues>( inStream);
	}

}
}

#else

#include "CmPhysXCommon.h"
#include "PxVisualDebuggerExt.h"

namespace physx { namespace debugger {
	class PvdDataStream;
}}

#endif // PX_SUPPORT_VISUAL_DEBUGGER