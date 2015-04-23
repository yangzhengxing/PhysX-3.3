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
// Created: 2015.02.25 07:18:53

#include "ClothingCookedPhysX3Param_0p2.h"
#include <string.h>
#include <stdlib.h>

using namespace NxParameterized;

namespace physx
{
namespace apex
{

using namespace ClothingCookedPhysX3Param_0p2NS;

const char* const ClothingCookedPhysX3Param_0p2Factory::vptr =
    NxParameterized::getVptr<ClothingCookedPhysX3Param_0p2, ClothingCookedPhysX3Param_0p2::ClassAlignment>();

const physx::PxU32 NumParamDefs = 37;
static NxParameterized::DefinitionImpl* ParamDefTable; // now allocated in buildTree [NumParamDefs];


static const size_t ParamLookupChildrenTable[] =
{
	1, 2, 3, 4, 6, 8, 10, 18, 23, 25, 27, 29, 31, 33, 34, 35, 36, 5, 7, 9, 11, 12, 13,
	14, 15, 16, 17, 19, 20, 21, 22, 24, 26, 28, 30, 32,
};

#define TENUM(type) physx::##type
#define CHILDREN(index) &ParamLookupChildrenTable[index]
static const NxParameterized::ParamLookupNode ParamLookupTable[NumParamDefs] =
{
	{ TYPE_STRUCT, false, 0, CHILDREN(0), 17 },
	{ TYPE_U32, false, (size_t)(&((ParametersStruct*)0)->physicalMeshId), NULL, 0 }, // physicalMeshId
	{ TYPE_U32, false, (size_t)(&((ParametersStruct*)0)->physicalSubMeshId), NULL, 0 }, // physicalSubMeshId
	{ TYPE_U32, false, (size_t)(&((ParametersStruct*)0)->numVertices), NULL, 0 }, // numVertices
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->deformableRestLengths), CHILDREN(17), 1 }, // deformableRestLengths
	{ TYPE_F32, false, 1 * sizeof(physx::PxF32), NULL, 0 }, // deformableRestLengths[]
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->deformableIndices), CHILDREN(18), 1 }, // deformableIndices
	{ TYPE_U32, false, 1 * sizeof(physx::PxU32), NULL, 0 }, // deformableIndices[]
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->selfCollisionIndices), CHILDREN(19), 1 }, // selfCollisionIndices
	{ TYPE_U32, false, 1 * sizeof(physx::PxU32), NULL, 0 }, // selfCollisionIndices[]
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->deformableSets), CHILDREN(20), 1 }, // deformableSets
	{ TYPE_STRUCT, false, 1 * sizeof(SetDesc_Type), CHILDREN(21), 6 }, // deformableSets[]
	{ TYPE_U32, false, (size_t)(&((SetDesc_Type*)0)->fiberEnd), NULL, 0 }, // deformableSets[].fiberEnd
	{ TYPE_U32, false, (size_t)(&((SetDesc_Type*)0)->longestFiber), NULL, 0 }, // deformableSets[].longestFiber
	{ TYPE_U32, false, (size_t)(&((SetDesc_Type*)0)->shortestFiber), NULL, 0 }, // deformableSets[].shortestFiber
	{ TYPE_U32, false, (size_t)(&((SetDesc_Type*)0)->numEdges), NULL, 0 }, // deformableSets[].numEdges
	{ TYPE_F32, false, (size_t)(&((SetDesc_Type*)0)->avgEdgeLength), NULL, 0 }, // deformableSets[].avgEdgeLength
	{ TYPE_U32, false, (size_t)(&((SetDesc_Type*)0)->avgFiberLength), NULL, 0 }, // deformableSets[].avgFiberLength
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->deformablePhaseDescs), CHILDREN(27), 1 }, // deformablePhaseDescs
	{ TYPE_STRUCT, false, 1 * sizeof(PhaseDesc_Type), CHILDREN(28), 3 }, // deformablePhaseDescs[]
	{ TYPE_U32, false, (size_t)(&((PhaseDesc_Type*)0)->phaseType), NULL, 0 }, // deformablePhaseDescs[].phaseType
	{ TYPE_U32, false, (size_t)(&((PhaseDesc_Type*)0)->setIndex), NULL, 0 }, // deformablePhaseDescs[].setIndex
	{ TYPE_U32, false, (size_t)(&((PhaseDesc_Type*)0)->restValueOffset), NULL, 0 }, // deformablePhaseDescs[].restValueOffset
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->tetherAnchors), CHILDREN(31), 1 }, // tetherAnchors
	{ TYPE_U32, false, 1 * sizeof(physx::PxU32), NULL, 0 }, // tetherAnchors[]
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->tetherLengths), CHILDREN(32), 1 }, // tetherLengths
	{ TYPE_F32, false, 1 * sizeof(physx::PxF32), NULL, 0 }, // tetherLengths[]
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->deformableInvVertexWeights), CHILDREN(33), 1 }, // deformableInvVertexWeights
	{ TYPE_F32, false, 1 * sizeof(physx::PxF32), NULL, 0 }, // deformableInvVertexWeights[]
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->virtualParticleIndices), CHILDREN(34), 1 }, // virtualParticleIndices
	{ TYPE_U32, false, 1 * sizeof(physx::PxU32), NULL, 0 }, // virtualParticleIndices[]
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->virtualParticleWeights), CHILDREN(35), 1 }, // virtualParticleWeights
	{ TYPE_F32, false, 1 * sizeof(physx::PxF32), NULL, 0 }, // virtualParticleWeights[]
	{ TYPE_U32, false, (size_t)(&((ParametersStruct*)0)->cookedDataVersion), NULL, 0 }, // cookedDataVersion
	{ TYPE_POINTER, false, (size_t)(&((ParametersStruct*)0)->fabricCPU), NULL, 0 }, // fabricCPU
	{ TYPE_POINTER, false, (size_t)(&((ParametersStruct*)0)->fabricGPU), NULL, 0 }, // fabricGPU
	{ TYPE_REF, false, (size_t)(&((ParametersStruct*)0)->nextCookedData), NULL, 0 }, // nextCookedData
};


bool ClothingCookedPhysX3Param_0p2::mBuiltFlag = false;
NxParameterized::MutexType ClothingCookedPhysX3Param_0p2::mBuiltFlagMutex;

ClothingCookedPhysX3Param_0p2::ClothingCookedPhysX3Param_0p2(NxParameterized::Traits* traits, void* buf, PxI32* refCount) :
	NxParameters(traits, buf, refCount)
{
	//mParameterizedTraits->registerFactory(className(), &ClothingCookedPhysX3Param_0p2FactoryInst);

	if (!buf) //Do not init data if it is inplace-deserialized
	{
		initDynamicArrays();
		initStrings();
		initReferences();
		initDefaults();
	}
}

ClothingCookedPhysX3Param_0p2::~ClothingCookedPhysX3Param_0p2()
{
	freeStrings();
	freeReferences();
	freeDynamicArrays();
}

void ClothingCookedPhysX3Param_0p2::destroy()
{
	// We cache these fields here to avoid overwrite in destructor
	bool doDeallocateSelf = mDoDeallocateSelf;
	NxParameterized::Traits* traits = mParameterizedTraits;
	physx::PxI32* refCount = mRefCount;
	void* buf = mBuffer;

	this->~ClothingCookedPhysX3Param_0p2();

	NxParameters::destroy(this, traits, doDeallocateSelf, refCount, buf);
}

const NxParameterized::DefinitionImpl* ClothingCookedPhysX3Param_0p2::getParameterDefinitionTree(void)
{
	if (!mBuiltFlag) // Double-checked lock
	{
		NxParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

const NxParameterized::DefinitionImpl* ClothingCookedPhysX3Param_0p2::getParameterDefinitionTree(void) const
{
	ClothingCookedPhysX3Param_0p2* tmpParam = const_cast<ClothingCookedPhysX3Param_0p2*>(this);

	if (!mBuiltFlag) // Double-checked lock
	{
		NxParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			tmpParam->buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

NxParameterized::ErrorType ClothingCookedPhysX3Param_0p2::getParameterHandle(const char* long_name, Handle& handle) const
{
	ErrorType Ret = NxParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

NxParameterized::ErrorType ClothingCookedPhysX3Param_0p2::getParameterHandle(const char* long_name, Handle& handle)
{
	ErrorType Ret = NxParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

void ClothingCookedPhysX3Param_0p2::getVarPtr(const Handle& handle, void*& ptr, size_t& offset) const
{
	ptr = getVarPtrHelper(&ParamLookupTable[0], const_cast<ClothingCookedPhysX3Param_0p2::ParametersStruct*>(&parameters()), handle, offset);
}


/* Dynamic Handle Indices */

void ClothingCookedPhysX3Param_0p2::freeParameterDefinitionTable(NxParameterized::Traits* traits)
{
	if (!traits)
	{
		return;
	}

	if (!mBuiltFlag) // Double-checked lock
	{
		return;
	}

	NxParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);

	if (!mBuiltFlag)
	{
		return;
	}

	for (physx::PxU32 i = 0; i < NumParamDefs; ++i)
	{
		ParamDefTable[i].~DefinitionImpl();
	}

	traits->free(ParamDefTable);

	mBuiltFlag = false;
}

#define PDEF_PTR(index) (&ParamDefTable[index])

void ClothingCookedPhysX3Param_0p2::buildTree(void)
{

	physx::PxU32 allocSize = sizeof(NxParameterized::DefinitionImpl) * NumParamDefs;
	ParamDefTable = (NxParameterized::DefinitionImpl*)(mParameterizedTraits->alloc(allocSize));
	memset(static_cast<void*>(ParamDefTable), 0, allocSize);

	for (physx::PxU32 i = 0; i < NumParamDefs; ++i)
	{
		NX_PARAM_PLACEMENT_NEW(ParamDefTable + i, NxParameterized::DefinitionImpl)(*mParameterizedTraits);
	}

	// Initialize DefinitionImpl node: nodeIndex=0, longName=""
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[0];
		ParamDef->init("", TYPE_STRUCT, "STRUCT", true);






	}

	// Initialize DefinitionImpl node: nodeIndex=1, longName="physicalMeshId"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[1];
		ParamDef->init("physicalMeshId", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=2, longName="physicalSubMeshId"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[2];
		ParamDef->init("physicalSubMeshId", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=3, longName="numVertices"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[3];
		ParamDef->init("numVertices", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=4, longName="deformableRestLengths"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[4];
		ParamDef->init("deformableRestLengths", TYPE_ARRAY, NULL, true);





		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=5, longName="deformableRestLengths[]"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[5];
		ParamDef->init("deformableRestLengths", TYPE_F32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=6, longName="deformableIndices"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[6];
		ParamDef->init("deformableIndices", TYPE_ARRAY, NULL, true);





		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=7, longName="deformableIndices[]"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[7];
		ParamDef->init("deformableIndices", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=8, longName="selfCollisionIndices"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[8];
		ParamDef->init("selfCollisionIndices", TYPE_ARRAY, NULL, true);





		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=9, longName="selfCollisionIndices[]"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[9];
		ParamDef->init("selfCollisionIndices", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=10, longName="deformableSets"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[10];
		ParamDef->init("deformableSets", TYPE_ARRAY, NULL, true);





		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=11, longName="deformableSets[]"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[11];
		ParamDef->init("deformableSets", TYPE_STRUCT, "SetDesc", true);






	}

	// Initialize DefinitionImpl node: nodeIndex=12, longName="deformableSets[].fiberEnd"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[12];
		ParamDef->init("fiberEnd", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=13, longName="deformableSets[].longestFiber"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[13];
		ParamDef->init("longestFiber", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=14, longName="deformableSets[].shortestFiber"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[14];
		ParamDef->init("shortestFiber", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=15, longName="deformableSets[].numEdges"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[15];
		ParamDef->init("numEdges", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=16, longName="deformableSets[].avgEdgeLength"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[16];
		ParamDef->init("avgEdgeLength", TYPE_F32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=17, longName="deformableSets[].avgFiberLength"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[17];
		ParamDef->init("avgFiberLength", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=18, longName="deformablePhaseDescs"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[18];
		ParamDef->init("deformablePhaseDescs", TYPE_ARRAY, NULL, true);





		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=19, longName="deformablePhaseDescs[]"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[19];
		ParamDef->init("deformablePhaseDescs", TYPE_STRUCT, "PhaseDesc", true);






	}

	// Initialize DefinitionImpl node: nodeIndex=20, longName="deformablePhaseDescs[].phaseType"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[20];
		ParamDef->init("phaseType", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=21, longName="deformablePhaseDescs[].setIndex"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[21];
		ParamDef->init("setIndex", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=22, longName="deformablePhaseDescs[].restValueOffset"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[22];
		ParamDef->init("restValueOffset", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=23, longName="tetherAnchors"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[23];
		ParamDef->init("tetherAnchors", TYPE_ARRAY, NULL, true);





		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=24, longName="tetherAnchors[]"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[24];
		ParamDef->init("tetherAnchors", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=25, longName="tetherLengths"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[25];
		ParamDef->init("tetherLengths", TYPE_ARRAY, NULL, true);





		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=26, longName="tetherLengths[]"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[26];
		ParamDef->init("tetherLengths", TYPE_F32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=27, longName="deformableInvVertexWeights"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[27];
		ParamDef->init("deformableInvVertexWeights", TYPE_ARRAY, NULL, true);





		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=28, longName="deformableInvVertexWeights[]"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[28];
		ParamDef->init("deformableInvVertexWeights", TYPE_F32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=29, longName="virtualParticleIndices"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[29];
		ParamDef->init("virtualParticleIndices", TYPE_ARRAY, NULL, true);





		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=30, longName="virtualParticleIndices[]"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[30];
		ParamDef->init("virtualParticleIndices", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=31, longName="virtualParticleWeights"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[31];
		ParamDef->init("virtualParticleWeights", TYPE_ARRAY, NULL, true);





		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=32, longName="virtualParticleWeights[]"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[32];
		ParamDef->init("virtualParticleWeights", TYPE_F32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=33, longName="cookedDataVersion"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[33];
		ParamDef->init("cookedDataVersion", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=34, longName="fabricCPU"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[34];
		ParamDef->init("fabricCPU", TYPE_POINTER, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("DONOTSERIALIZE", physx::PxU64(1), true);
		ParamDefTable[34].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("DONOTSERIALIZE", physx::PxU64(1), true);
		ParamDefTable[34].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=35, longName="fabricGPU"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[35];
		ParamDef->init("fabricGPU", TYPE_POINTER, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("DONOTSERIALIZE", physx::PxU64(1), true);
		ParamDefTable[35].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("DONOTSERIALIZE", physx::PxU64(1), true);
		ParamDefTable[35].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=36, longName="nextCookedData"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[36];
		ParamDef->init("nextCookedData", TYPE_REF, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("INCLUDED", physx::PxU64(1), true);
		ParamDefTable[36].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("INCLUDED", physx::PxU64(1), true);
		HintTable[1].init("shortDescription", "Daisy-chain together multiple cooked data objects", true);
		ParamDefTable[36].setHints((const NxParameterized::Hint**)HintPtrTable, 2);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */


		static const char* const RefVariantVals[] = { "ClothingCookedPhysX3Param" };
		ParamDefTable[36].setRefVariantVals((const char**)RefVariantVals, 1);



	}

	// SetChildren for: nodeIndex=0, longName=""
	{
		static Definition* Children[17];
		Children[0] = PDEF_PTR(1);
		Children[1] = PDEF_PTR(2);
		Children[2] = PDEF_PTR(3);
		Children[3] = PDEF_PTR(4);
		Children[4] = PDEF_PTR(6);
		Children[5] = PDEF_PTR(8);
		Children[6] = PDEF_PTR(10);
		Children[7] = PDEF_PTR(18);
		Children[8] = PDEF_PTR(23);
		Children[9] = PDEF_PTR(25);
		Children[10] = PDEF_PTR(27);
		Children[11] = PDEF_PTR(29);
		Children[12] = PDEF_PTR(31);
		Children[13] = PDEF_PTR(33);
		Children[14] = PDEF_PTR(34);
		Children[15] = PDEF_PTR(35);
		Children[16] = PDEF_PTR(36);

		ParamDefTable[0].setChildren(Children, 17);
	}

	// SetChildren for: nodeIndex=4, longName="deformableRestLengths"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(5);

		ParamDefTable[4].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=6, longName="deformableIndices"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(7);

		ParamDefTable[6].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=8, longName="selfCollisionIndices"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(9);

		ParamDefTable[8].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=10, longName="deformableSets"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(11);

		ParamDefTable[10].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=11, longName="deformableSets[]"
	{
		static Definition* Children[6];
		Children[0] = PDEF_PTR(12);
		Children[1] = PDEF_PTR(13);
		Children[2] = PDEF_PTR(14);
		Children[3] = PDEF_PTR(15);
		Children[4] = PDEF_PTR(16);
		Children[5] = PDEF_PTR(17);

		ParamDefTable[11].setChildren(Children, 6);
	}

	// SetChildren for: nodeIndex=18, longName="deformablePhaseDescs"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(19);

		ParamDefTable[18].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=19, longName="deformablePhaseDescs[]"
	{
		static Definition* Children[3];
		Children[0] = PDEF_PTR(20);
		Children[1] = PDEF_PTR(21);
		Children[2] = PDEF_PTR(22);

		ParamDefTable[19].setChildren(Children, 3);
	}

	// SetChildren for: nodeIndex=23, longName="tetherAnchors"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(24);

		ParamDefTable[23].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=25, longName="tetherLengths"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(26);

		ParamDefTable[25].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=27, longName="deformableInvVertexWeights"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(28);

		ParamDefTable[27].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=29, longName="virtualParticleIndices"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(30);

		ParamDefTable[29].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=31, longName="virtualParticleWeights"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(32);

		ParamDefTable[31].setChildren(Children, 1);
	}

	mBuiltFlag = true;

}
void ClothingCookedPhysX3Param_0p2::initStrings(void)
{
}

void ClothingCookedPhysX3Param_0p2::initDynamicArrays(void)
{
	deformableRestLengths.buf = NULL;
	deformableRestLengths.isAllocated = true;
	deformableRestLengths.elementSize = sizeof(physx::PxF32);
	deformableRestLengths.arraySizes[0] = 0;
	deformableIndices.buf = NULL;
	deformableIndices.isAllocated = true;
	deformableIndices.elementSize = sizeof(physx::PxU32);
	deformableIndices.arraySizes[0] = 0;
	selfCollisionIndices.buf = NULL;
	selfCollisionIndices.isAllocated = true;
	selfCollisionIndices.elementSize = sizeof(physx::PxU32);
	selfCollisionIndices.arraySizes[0] = 0;
	deformableSets.buf = NULL;
	deformableSets.isAllocated = true;
	deformableSets.elementSize = sizeof(SetDesc_Type);
	deformableSets.arraySizes[0] = 0;
	deformablePhaseDescs.buf = NULL;
	deformablePhaseDescs.isAllocated = true;
	deformablePhaseDescs.elementSize = sizeof(PhaseDesc_Type);
	deformablePhaseDescs.arraySizes[0] = 0;
	tetherAnchors.buf = NULL;
	tetherAnchors.isAllocated = true;
	tetherAnchors.elementSize = sizeof(physx::PxU32);
	tetherAnchors.arraySizes[0] = 0;
	tetherLengths.buf = NULL;
	tetherLengths.isAllocated = true;
	tetherLengths.elementSize = sizeof(physx::PxF32);
	tetherLengths.arraySizes[0] = 0;
	deformableInvVertexWeights.buf = NULL;
	deformableInvVertexWeights.isAllocated = true;
	deformableInvVertexWeights.elementSize = sizeof(physx::PxF32);
	deformableInvVertexWeights.arraySizes[0] = 0;
	virtualParticleIndices.buf = NULL;
	virtualParticleIndices.isAllocated = true;
	virtualParticleIndices.elementSize = sizeof(physx::PxU32);
	virtualParticleIndices.arraySizes[0] = 0;
	virtualParticleWeights.buf = NULL;
	virtualParticleWeights.isAllocated = true;
	virtualParticleWeights.elementSize = sizeof(physx::PxF32);
	virtualParticleWeights.arraySizes[0] = 0;
}

void ClothingCookedPhysX3Param_0p2::initDefaults(void)
{

	freeStrings();
	freeReferences();
	freeDynamicArrays();
	physicalMeshId = physx::PxU32(0);
	physicalSubMeshId = physx::PxU32(0);
	numVertices = physx::PxU32(0);
	cookedDataVersion = physx::PxU32(0);
	fabricCPU = NULL;
	fabricGPU = NULL;

	initDynamicArrays();
	initStrings();
	initReferences();
}

void ClothingCookedPhysX3Param_0p2::initReferences(void)
{
	nextCookedData = NULL;

}

void ClothingCookedPhysX3Param_0p2::freeDynamicArrays(void)
{
	if (deformableRestLengths.isAllocated && deformableRestLengths.buf)
	{
		mParameterizedTraits->free(deformableRestLengths.buf);
	}
	if (deformableIndices.isAllocated && deformableIndices.buf)
	{
		mParameterizedTraits->free(deformableIndices.buf);
	}
	if (selfCollisionIndices.isAllocated && selfCollisionIndices.buf)
	{
		mParameterizedTraits->free(selfCollisionIndices.buf);
	}
	if (deformableSets.isAllocated && deformableSets.buf)
	{
		mParameterizedTraits->free(deformableSets.buf);
	}
	if (deformablePhaseDescs.isAllocated && deformablePhaseDescs.buf)
	{
		mParameterizedTraits->free(deformablePhaseDescs.buf);
	}
	if (tetherAnchors.isAllocated && tetherAnchors.buf)
	{
		mParameterizedTraits->free(tetherAnchors.buf);
	}
	if (tetherLengths.isAllocated && tetherLengths.buf)
	{
		mParameterizedTraits->free(tetherLengths.buf);
	}
	if (deformableInvVertexWeights.isAllocated && deformableInvVertexWeights.buf)
	{
		mParameterizedTraits->free(deformableInvVertexWeights.buf);
	}
	if (virtualParticleIndices.isAllocated && virtualParticleIndices.buf)
	{
		mParameterizedTraits->free(virtualParticleIndices.buf);
	}
	if (virtualParticleWeights.isAllocated && virtualParticleWeights.buf)
	{
		mParameterizedTraits->free(virtualParticleWeights.buf);
	}
}

void ClothingCookedPhysX3Param_0p2::freeStrings(void)
{
}

void ClothingCookedPhysX3Param_0p2::freeReferences(void)
{
	if (nextCookedData)
	{
		nextCookedData->destroy();
	}

}

} // namespace apex
} // namespace physx
