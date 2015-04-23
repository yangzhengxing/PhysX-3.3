/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


// This file was generated by NxParameterized/scripts/GenParameterized.pl
// Created: 2015.02.25 07:18:32

#ifndef HEADER_SurfaceTraceParameters_h
#define HEADER_SurfaceTraceParameters_h

#include "NxParametersTypes.h"

#ifndef NX_PARAMETERIZED_ONLY_LAYOUTS
#include "NxParameterized.h"
#include "NxParameters.h"
#include "NxParameterizedTraits.h"
#include "NxTraitsInternal.h"
#endif

namespace physx
{
namespace apex
{
namespace destructible
{

#pragma warning(push)
#pragma warning(disable: 4324) // structure was padded due to __declspec(align())

namespace SurfaceTraceParametersNS
{


struct U8_DynamicArray1D_Type
{
	physx::PxU8* buf;
	bool isAllocated;
	physx::PxI32 elementSize;
	physx::PxI32 arraySizes[1];
};

struct U32_DynamicArray1D_Type
{
	physx::PxU32* buf;
	bool isAllocated;
	physx::PxI32 elementSize;
	physx::PxI32 arraySizes[1];
};


struct ParametersStruct
{

	U8_DynamicArray1D_Type submeshIndices;
	U32_DynamicArray1D_Type vertexIndices;
	physx::PxVec3 defaultNormal;

};

static const physx::PxU32 checksum[] = { 0x97a690a9, 0x7c950c3a, 0x7e771c34, 0x41bed788, };

} // namespace SurfaceTraceParametersNS

#ifndef NX_PARAMETERIZED_ONLY_LAYOUTS
class SurfaceTraceParameters : public NxParameterized::NxParameters, public SurfaceTraceParametersNS::ParametersStruct
{
public:
	SurfaceTraceParameters(NxParameterized::Traits* traits, void* buf = 0, PxI32* refCount = 0);

	virtual ~SurfaceTraceParameters();

	virtual void destroy();

	static const char* staticClassName(void)
	{
		return("SurfaceTraceParameters");
	}

	const char* className(void) const
	{
		return(staticClassName());
	}

	static const physx::PxU32 ClassVersion = ((physx::PxU32)0 << 16) + (physx::PxU32)0;

	static physx::PxU32 staticVersion(void)
	{
		return ClassVersion;
	}

	physx::PxU32 version(void) const
	{
		return(staticVersion());
	}

	static const physx::PxU32 ClassAlignment = 8;

	static const physx::PxU32* staticChecksum(physx::PxU32& bits)
	{
		bits = 8 * sizeof(SurfaceTraceParametersNS::checksum);
		return SurfaceTraceParametersNS::checksum;
	}

	static void freeParameterDefinitionTable(NxParameterized::Traits* traits);

	const physx::PxU32* checksum(physx::PxU32& bits) const
	{
		return staticChecksum(bits);
	}

	const SurfaceTraceParametersNS::ParametersStruct& parameters(void) const
	{
		SurfaceTraceParameters* tmpThis = const_cast<SurfaceTraceParameters*>(this);
		return *(static_cast<SurfaceTraceParametersNS::ParametersStruct*>(tmpThis));
	}

	SurfaceTraceParametersNS::ParametersStruct& parameters(void)
	{
		return *(static_cast<SurfaceTraceParametersNS::ParametersStruct*>(this));
	}

	virtual NxParameterized::ErrorType getParameterHandle(const char* long_name, NxParameterized::Handle& handle) const;
	virtual NxParameterized::ErrorType getParameterHandle(const char* long_name, NxParameterized::Handle& handle);

	void initDefaults(void);

protected:

	virtual const NxParameterized::DefinitionImpl* getParameterDefinitionTree(void);
	virtual const NxParameterized::DefinitionImpl* getParameterDefinitionTree(void) const;


	virtual void getVarPtr(const NxParameterized::Handle& handle, void*& ptr, size_t& offset) const;

private:

	void buildTree(void);
	void initDynamicArrays(void);
	void initStrings(void);
	void initReferences(void);
	void freeDynamicArrays(void);
	void freeStrings(void);
	void freeReferences(void);

	static bool mBuiltFlag;
	static NxParameterized::MutexType mBuiltFlagMutex;
};

class SurfaceTraceParametersFactory : public NxParameterized::Factory
{
	static const char* const vptr;

public:
	virtual NxParameterized::Interface* create(NxParameterized::Traits* paramTraits)
	{
		// placement new on this class using mParameterizedTraits

		void* newPtr = paramTraits->alloc(sizeof(SurfaceTraceParameters), SurfaceTraceParameters::ClassAlignment);
		if (!NxParameterized::IsAligned(newPtr, SurfaceTraceParameters::ClassAlignment))
		{
			NX_PARAM_TRAITS_WARNING(paramTraits, "Unaligned memory allocation for class SurfaceTraceParameters");
			paramTraits->free(newPtr);
			return 0;
		}

		memset(newPtr, 0, sizeof(SurfaceTraceParameters)); // always initialize memory allocated to zero for default values
		return NX_PARAM_PLACEMENT_NEW(newPtr, SurfaceTraceParameters)(paramTraits);
	}

	virtual NxParameterized::Interface* finish(NxParameterized::Traits* paramTraits, void* bufObj, void* bufStart, physx::PxI32* refCount)
	{
		if (!NxParameterized::IsAligned(bufObj, SurfaceTraceParameters::ClassAlignment)
		        || !NxParameterized::IsAligned(bufStart, SurfaceTraceParameters::ClassAlignment))
		{
			NX_PARAM_TRAITS_WARNING(paramTraits, "Unaligned memory allocation for class SurfaceTraceParameters");
			return 0;
		}

		// Init NxParameters-part
		// We used to call empty constructor of SurfaceTraceParameters here
		// but it may call default constructors of members and spoil the data
		NX_PARAM_PLACEMENT_NEW(bufObj, NxParameterized::NxParameters)(paramTraits, bufStart, refCount);

		// Init vtable (everything else is already initialized)
		*(const char**)bufObj = vptr;

		return (SurfaceTraceParameters*)bufObj;
	}

	virtual const char* getClassName()
	{
		return (SurfaceTraceParameters::staticClassName());
	}

	virtual physx::PxU32 getVersion()
	{
		return (SurfaceTraceParameters::staticVersion());
	}

	virtual physx::PxU32 getAlignment()
	{
		return (SurfaceTraceParameters::ClassAlignment);
	}

	virtual const physx::PxU32* getChecksum(physx::PxU32& bits)
	{
		return (SurfaceTraceParameters::staticChecksum(bits));
	}
};
#endif // NX_PARAMETERIZED_ONLY_LAYOUTS

} // namespace destructible
} // namespace apex
} // namespace physx

#pragma warning(pop)

#endif
