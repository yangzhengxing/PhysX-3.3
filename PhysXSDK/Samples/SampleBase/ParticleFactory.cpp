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

#include "ParticleFactory.h"
#include "PsMathUtils.h"
#include "PxTkRandom.h"

using namespace PxToolkit;
//----------------------------------------------------------------------------//

void CreateParticleAABB(ParticleData& particleData, const PxBounds3& aabb, const PxVec3& vel, float distance)
{
	PxVec3 aabbDim = aabb.getExtents() * 2.0f;

	unsigned sideNumX = (unsigned)PxMax(1.0f, physx::shdfnd::floor(aabbDim.x / distance));
	unsigned sideNumY = (unsigned)PxMax(1.0f, physx::shdfnd::floor(aabbDim.y / distance));
	unsigned sideNumZ = (unsigned)PxMax(1.0f, physx::shdfnd::floor(aabbDim.z / distance));

	for(unsigned i=0; i<sideNumX; i++)
		for(unsigned j=0; j<sideNumY; j++)
			for(unsigned k=0; k<sideNumZ; k++)
			{
				if(particleData.numParticles >= particleData.maxParticles) 
					break;

				PxVec3 p = PxVec3(i*distance,j*distance,k*distance);
				p += aabb.minimum;

				particleData.positions[particleData.numParticles] = p;
				particleData.velocities[particleData.numParticles] = vel;
				particleData.numParticles++;
			}
}

//----------------------------------------------------------------------------//

void CreateParticleSphere(ParticleData& particleData, const PxVec3& pos, const PxVec3& vel, float distance, unsigned sideNum)
{
	float rad = sideNum*distance*0.5f;
	PxVec3 offset((sideNum-1)*distance*0.5f);

	for(unsigned i=0; i<sideNum; i++)
		for(unsigned j=0; j<sideNum; j++)
			for(unsigned k=0; k<sideNum; k++)
			{
				if(particleData.numParticles >= particleData.maxParticles) 
					break;

				PxVec3 p = PxVec3(i*distance,j*distance,k*distance);
				if((p-PxVec3(rad,rad,rad)).magnitude() < rad)
				{
					p += pos;
					p -= offset; // ISG: for symmetry

					particleData.positions[particleData.numParticles] = p;
					particleData.velocities[particleData.numParticles] = vel;
					particleData.numParticles++;
				}
			}
}

//-----------------------------------------------------------------------------------------------------------------//
void CreateParticleRand(ParticleData& particleData, const PxVec3& center, const PxVec3& range,const PxVec3& vel)
{
	PxToolkit::SetSeed(0);
    while(particleData.numParticles < particleData.maxParticles) 
	{
		PxVec3 p(Rand(-range.x, range.x), 
			Rand(-range.y, range.y), 
			Rand(-range.z, range.z));

		p += center;

		PxVec3 v(Rand(-vel.x, vel.x), 
			Rand(-vel.y, vel.y), 
			Rand(-vel.z, vel.z));

		particleData.positions[particleData.numParticles] = p;
		particleData.velocities[particleData.numParticles] = vel;
		particleData.numParticles++;
	}
}

//----------------------------------------------------------------------------//

void SetParticleRestOffsetVariance(ParticleData& particleData, PxF32 maxRestOffset, PxF32 restOffsetVariance)
{
	PxToolkit::SetSeed(0);

	if (particleData.restOffsets.size() == 0)
		particleData.restOffsets.resize(particleData.maxParticles);

	for (PxU32 i = 0 ; i < particleData.numParticles; ++i)
		particleData.restOffsets[i] = maxRestOffset*(1.0f - Rand(0.0f, restOffsetVariance));
}

//----------------------------------------------------------------------------//
