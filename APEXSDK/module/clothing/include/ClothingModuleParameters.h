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
// Created: 2015.02.25 07:18:30

#ifndef HEADER_ClothingModuleParameters_h
#define HEADER_ClothingModuleParameters_h

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
namespace clothing
{

#pragma warning(push)
#pragma warning(disable: 4324) // structure was padded due to __declspec(align())

namespace ClothingModuleParametersNS
{



struct ParametersStruct
{

	physx::PxU32 maxNumCompartments;
	physx::PxU32 maxUnusedPhysXResources;
	bool allowAsyncCooking;
	bool asyncFetchResults;
	physx::PxU32 avgSimFrequencyWindow;
	bool allowApexWorkBetweenSubsteps;
	physx::PxF32 interCollisionDistance;
	physx::PxF32 interCollisionStiffness;
	physx::PxU32 interCollisionIterations;
	bool sparseSelfCollision;
	physx::PxU32 maxTimeRenderProxyInPool;

};

static const physx::PxU32 checksum[] = { 0x15043a9d, 0x77224355, 0x4c92d234, 0x3bbce77c, };

} // namespace ClothingModuleParametersNS

#ifndef NX_PARAMETERIZED_ONLY_LAYOUTS
class ClothingModuleParameters : public NxParameterized::NxParameters, public ClothingModuleParametersNS::ParametersStruct
{
public:
	ClothingModuleParameters(NxParameterized::Traits* traits, void* buf = 0, PxI32* refCount = 0);

	virtual ~ClothingModuleParameters();

	virtual void destroy();

	static const char* staticClassName(void)
	{
		return("ClothingModuleParameters");
	}

	const char* className(void) const
	{
		return(staticClassName());
	}

	static const physx::PxU32 ClassVersion = ((physx::PxU32)0 << 16) + (physx::PxU32)1;

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
		bits = 8 * sizeof(ClothingModuleParametersNS::checksum);
		return ClothingModuleParametersNS::checksum;
	}

	static void freeParameterDefinitionTable(NxParameterized::Traits* traits);

	const physx::PxU32* checksum(physx::PxU32& bits) const
	{
		return staticChecksum(bits);
	}

	const ClothingModuleParametersNS::ParametersStruct& parameters(void) const
	{
		ClothingModuleParameters* tmpThis = const_cast<ClothingModuleParameters*>(this);
		return *(static_cast<ClothingModuleParametersNS::ParametersStruct*>(tmpThis));
	}

	ClothingModuleParametersNS::ParametersStruct& parameters(void)
	{
		return *(static_cast<ClothingModuleParametersNS::ParametersStruct*>(this));
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

class ClothingModuleParametersFactory : public NxParameterized::Factory
{
	static const char* const vptr;

public:
	virtual NxParameterized::Interface* create(NxParameterized::Traits* paramTraits)
	{
		// placement new on this class using mParameterizedTraits

		void* newPtr = paramTraits->alloc(sizeof(ClothingModuleParameters), ClothingModuleParameters::ClassAlignment);
		if (!NxParameterized::IsAligned(newPtr, ClothingModuleParameters::ClassAlignment))
		{
			NX_PARAM_TRAITS_WARNING(paramTraits, "Unaligned memory allocation for class ClothingModuleParameters");
			paramTraits->free(newPtr);
			return 0;
		}

		memset(newPtr, 0, sizeof(ClothingModuleParameters)); // always initialize memory allocated to zero for default values
		return NX_PARAM_PLACEMENT_NEW(newPtr, ClothingModuleParameters)(paramTraits);
	}

	virtual NxParameterized::Interface* finish(NxParameterized::Traits* paramTraits, void* bufObj, void* bufStart, physx::PxI32* refCount)
	{
		if (!NxParameterized::IsAligned(bufObj, ClothingModuleParameters::ClassAlignment)
		        || !NxParameterized::IsAligned(bufStart, ClothingModuleParameters::ClassAlignment))
		{
			NX_PARAM_TRAITS_WARNING(paramTraits, "Unaligned memory allocation for class ClothingModuleParameters");
			return 0;
		}

		// Init NxParameters-part
		// We used to call empty constructor of ClothingModuleParameters here
		// but it may call default constructors of members and spoil the data
		NX_PARAM_PLACEMENT_NEW(bufObj, NxParameterized::NxParameters)(paramTraits, bufStart, refCount);

		// Init vtable (everything else is already initialized)
		*(const char**)bufObj = vptr;

		return (ClothingModuleParameters*)bufObj;
	}

	virtual const char* getClassName()
	{
		return (ClothingModuleParameters::staticClassName());
	}

	virtual physx::PxU32 getVersion()
	{
		return (ClothingModuleParameters::staticVersion());
	}

	virtual physx::PxU32 getAlignment()
	{
		return (ClothingModuleParameters::ClassAlignment);
	}

	virtual const physx::PxU32* getChecksum(physx::PxU32& bits)
	{
		return (ClothingModuleParameters::staticChecksum(bits));
	}
};
#endif // NX_PARAMETERIZED_ONLY_LAYOUTS

} // namespace clothing
} // namespace apex
} // namespace physx

#pragma warning(pop)

#endif
