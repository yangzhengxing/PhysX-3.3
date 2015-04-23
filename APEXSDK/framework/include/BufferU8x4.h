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
// Created: 2015.02.25 07:18:23

#ifndef HEADER_BufferU8x4_h
#define HEADER_BufferU8x4_h

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

#pragma warning(push)
#pragma warning(disable: 4324) // structure was padded due to __declspec(align())

namespace BufferU8x4NS
{

struct U8x4_Type;

struct U8x4_DynamicArray1D_Type
{
	U8x4_Type* buf;
	bool isAllocated;
	physx::PxI32 elementSize;
	physx::PxI32 arraySizes[1];
};

struct U8x4_Type
{
	physx::PxU8 x;
	physx::PxU8 y;
	physx::PxU8 z;
	physx::PxU8 w;
};

struct ParametersStruct
{

	U8x4_DynamicArray1D_Type data;

};

static const physx::PxU32 checksum[] = { 0x8364dd0f, 0xbc7542d0, 0x1a22d2d2, 0x01fc1923, };

} // namespace BufferU8x4NS

#ifndef NX_PARAMETERIZED_ONLY_LAYOUTS
class BufferU8x4 : public NxParameterized::NxParameters, public BufferU8x4NS::ParametersStruct
{
public:
	BufferU8x4(NxParameterized::Traits* traits, void* buf = 0, PxI32* refCount = 0);

	virtual ~BufferU8x4();

	virtual void destroy();

	static const char* staticClassName(void)
	{
		return("BufferU8x4");
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
		bits = 8 * sizeof(BufferU8x4NS::checksum);
		return BufferU8x4NS::checksum;
	}

	static void freeParameterDefinitionTable(NxParameterized::Traits* traits);

	const physx::PxU32* checksum(physx::PxU32& bits) const
	{
		return staticChecksum(bits);
	}

	const BufferU8x4NS::ParametersStruct& parameters(void) const
	{
		BufferU8x4* tmpThis = const_cast<BufferU8x4*>(this);
		return *(static_cast<BufferU8x4NS::ParametersStruct*>(tmpThis));
	}

	BufferU8x4NS::ParametersStruct& parameters(void)
	{
		return *(static_cast<BufferU8x4NS::ParametersStruct*>(this));
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

class BufferU8x4Factory : public NxParameterized::Factory
{
	static const char* const vptr;

public:
	virtual NxParameterized::Interface* create(NxParameterized::Traits* paramTraits)
	{
		// placement new on this class using mParameterizedTraits

		void* newPtr = paramTraits->alloc(sizeof(BufferU8x4), BufferU8x4::ClassAlignment);
		if (!NxParameterized::IsAligned(newPtr, BufferU8x4::ClassAlignment))
		{
			NX_PARAM_TRAITS_WARNING(paramTraits, "Unaligned memory allocation for class BufferU8x4");
			paramTraits->free(newPtr);
			return 0;
		}

		memset(newPtr, 0, sizeof(BufferU8x4)); // always initialize memory allocated to zero for default values
		return NX_PARAM_PLACEMENT_NEW(newPtr, BufferU8x4)(paramTraits);
	}

	virtual NxParameterized::Interface* finish(NxParameterized::Traits* paramTraits, void* bufObj, void* bufStart, physx::PxI32* refCount)
	{
		if (!NxParameterized::IsAligned(bufObj, BufferU8x4::ClassAlignment)
		        || !NxParameterized::IsAligned(bufStart, BufferU8x4::ClassAlignment))
		{
			NX_PARAM_TRAITS_WARNING(paramTraits, "Unaligned memory allocation for class BufferU8x4");
			return 0;
		}

		// Init NxParameters-part
		// We used to call empty constructor of BufferU8x4 here
		// but it may call default constructors of members and spoil the data
		NX_PARAM_PLACEMENT_NEW(bufObj, NxParameterized::NxParameters)(paramTraits, bufStart, refCount);

		// Init vtable (everything else is already initialized)
		*(const char**)bufObj = vptr;

		return (BufferU8x4*)bufObj;
	}

	virtual const char* getClassName()
	{
		return (BufferU8x4::staticClassName());
	}

	virtual physx::PxU32 getVersion()
	{
		return (BufferU8x4::staticVersion());
	}

	virtual physx::PxU32 getAlignment()
	{
		return (BufferU8x4::ClassAlignment);
	}

	virtual const physx::PxU32* getChecksum(physx::PxU32& bits)
	{
		return (BufferU8x4::staticChecksum(bits));
	}
};
#endif // NX_PARAMETERIZED_ONLY_LAYOUTS

} // namespace apex
} // namespace physx

#pragma warning(pop)

#endif
