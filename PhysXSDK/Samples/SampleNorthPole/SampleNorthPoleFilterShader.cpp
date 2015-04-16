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


#include "PxPhysicsAPI.h"
#include "SampleNorthPole.h"

void SampleNorthPole::customizeSceneDesc(PxSceneDesc& sceneDesc)
{
	sceneDesc.gravity					= PxVec3(0,-9.81,0);
	sceneDesc.filterShader				= filter;
	sceneDesc.simulationEventCallback	= this;
	sceneDesc.flags						|= PxSceneFlag::eENABLE_CCD;
	sceneDesc.flags						|= PxSceneFlag::eREQUIRE_RW_LOCK;
}

void SampleNorthPole::setSnowball(PxShape& shape)
{
	PxFilterData fd = shape.getSimulationFilterData();
	fd.word3 |= SNOWBALL_FLAG;
	shape.setSimulationFilterData(fd);
}

bool SampleNorthPole::needsContactReport(const PxFilterData& filterData0, const PxFilterData& filterData1)
{
	const PxU32 needsReport = PxU32(DETACHABLE_FLAG | SNOWBALL_FLAG);
	PxU32 flags = (filterData0.word3 | filterData1.word3);
	return (flags & needsReport) == needsReport;
}

void SampleNorthPole::setDetachable(PxShape& shape)
{
	PxFilterData fd = shape.getSimulationFilterData();
	fd.word3 |= PxU32(DETACHABLE_FLAG);
	shape.setSimulationFilterData(fd);
}

bool SampleNorthPole::isDetachable(PxFilterData& filterData)
{
	return filterData.word3 & PxU32(DETACHABLE_FLAG) ? true : false;
}

void SampleNorthPole::setCCDActive(PxShape& shape, PxRigidBody* rigidBody)
{
	rigidBody->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, true);
	PxFilterData fd = shape.getSimulationFilterData();
	fd.word3 |= CCD_FLAG;
	shape.setSimulationFilterData(fd);
	
}

bool SampleNorthPole::isCCDActive(PxFilterData& filterData)
{
	return filterData.word3 & CCD_FLAG ? true : false;
}

PxFilterFlags SampleNorthPole::filter(	PxFilterObjectAttributes attributes0,
						PxFilterData filterData0, 
						PxFilterObjectAttributes attributes1,
						PxFilterData filterData1,
						PxPairFlags& pairFlags,
						const void* constantBlock,
						PxU32 constantBlockSize)
{

	if (isCCDActive(filterData0) || isCCDActive(filterData1))
	{
		pairFlags |= PxPairFlag::eCCD_LINEAR;
	}

	if (needsContactReport(filterData0, filterData1))
	{
		pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
	}

	pairFlags |= PxPairFlag::eCONTACT_DEFAULT;
	return PxFilterFlags();
}

void SampleNorthPole::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
	for(PxU32 i=0; i < nbPairs; i++)
	{
		PxU32 n = 2;
		const PxContactPairFlag::Enum delShapeFlags[] = { PxContactPairFlag::eREMOVED_SHAPE_0, PxContactPairFlag::eREMOVED_SHAPE_1 };
		const PxContactPair& cp = pairs[i];
		while(n--)
		{
			if(!(cp.flags & delShapeFlags[n]))
			{
				PxShape* shape = cp.shapes[n];
				PxFilterData fd = shape->getSimulationFilterData();
				if(isDetachable(fd))
				{
					mDetaching.push_back(shape);
				}
			}
		}
	}
}
