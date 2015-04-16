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

#include "SampleVehicle_SceneQuery.h"
#include "vehicle/PxVehicleSDK.h"
#include "PxFiltering.h"
#include "PsFoundation.h"
#include "PsUtilities.h"

#define CHECK_MSG(exp, msg) (!!(exp) || (physx::shdfnd::getFoundation().error(physx::PxErrorCode::eINVALID_PARAMETER, __FILE__, __LINE__, msg), 0) )
#define SIZEALIGN16(size) (((unsigned)(size)+15)&((unsigned)(~15)));

void SampleVehicleSetupDrivableShapeQueryFilterData(PxFilterData* qryFilterData)
{
	CHECK_MSG(0==qryFilterData->word3, "word3 is reserved for filter data for vehicle raycast queries");
	qryFilterData->word3 = (PxU32)SAMPLEVEHICLE_DRIVABLE_SURFACE;
}

void SampleVehicleSetupNonDrivableShapeQueryFilterData(PxFilterData* qryFilterData)
{
	CHECK_MSG(0==qryFilterData->word3, "word3 is reserved for filter data for vehicle raycast queries");
	qryFilterData->word3 = (PxU32)SAMPLEVEHICLE_UNDRIVABLE_SURFACE;
}

void SampleVehicleSetupVehicleShapeQueryFilterData(PxFilterData* qryFilterData)
{
	CHECK_MSG(0==qryFilterData->word3, "word3 is reserved for filter data for vehicle raycast queries");
	qryFilterData->word3 = (PxU32)SAMPLEVEHICLE_UNDRIVABLE_SURFACE;
}

SampleVehicleSceneQueryData* SampleVehicleSceneQueryData::allocate(const PxU32 maxNumWheels)
{
	const PxU32 size0 = SIZEALIGN16(sizeof(SampleVehicleSceneQueryData));
	const PxU32 size1 = SIZEALIGN16(sizeof(PxRaycastQueryResult)*maxNumWheels);
	const PxU32 size2 = SIZEALIGN16(sizeof(PxRaycastHit)*maxNumWheels);
	const PxU32 size = size0 + size1 + size2;
	SampleVehicleSceneQueryData* sqData = (SampleVehicleSceneQueryData*)PX_ALLOC(size, PX_DEBUG_EXP("PxVehicleNWSceneQueryData"));
	sqData->init();
	PxU8* ptr = (PxU8*) sqData;
	ptr += size0;
	sqData->mSqResults = (PxRaycastQueryResult*)ptr;
	sqData->mNbSqResults = maxNumWheels;
	ptr += size1;
	sqData->mSqHitBuffer = (PxRaycastHit*)ptr;
	ptr += size2;
	sqData->mNumQueries = maxNumWheels;
	return sqData;
}

void SampleVehicleSceneQueryData::free()
{
	PX_FREE(this);
}

PxBatchQuery* SampleVehicleSceneQueryData::setUpBatchedSceneQuery(PxScene* scene)
{
	PxBatchQueryDesc sqDesc(mNbSqResults, 0, 0);
	sqDesc.queryMemory.userRaycastResultBuffer = mSqResults;
	sqDesc.queryMemory.userRaycastTouchBuffer = mSqHitBuffer;
	sqDesc.queryMemory.raycastTouchBufferSize = mNumQueries;
	sqDesc.preFilterShader = mPreFilterShader;
	sqDesc.spuPreFilterShader = mSpuPreFilterShader;
	sqDesc.spuPreFilterShaderSize = mSpuPreFilterShaderSize;
	return scene->createBatchQuery(sqDesc);
}




