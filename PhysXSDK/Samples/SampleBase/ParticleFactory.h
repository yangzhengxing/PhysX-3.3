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

#ifndef PARTICLE_FACTORY_H
#define PARTICLE_FACTORY_H

//----------------------------------------------------------------------------//
#include "PxPhysicsAPI.h"
#include "PhysXSampleApplication.h"

//----------------------------------------------------------------------------//

struct ParticleData : public SampleAllocateable
{
	ParticleData() : maxParticles(0), numParticles(0) {}

	ParticleData(PxU32 _maxParticles)
	{
		initialize(_maxParticles);
	}

	void initialize(PxU32 _maxParticles)
	{
		maxParticles = _maxParticles;
		numParticles = 0;
		positions.resize(maxParticles);
		velocities.resize(maxParticles);
		restOffsets.resize(0);
	}

	SampleArray<PxVec3> positions;
	SampleArray<PxVec3> velocities;
	SampleArray<PxF32> restOffsets;
	PxU32	maxParticles;
	PxU32	numParticles;
};

//----------------------------------------------------------------------------//

void CreateParticleAABB(ParticleData& particleData, const PxBounds3& aabb, const PxVec3& vel, float distance);
void CreateParticleSphere(ParticleData& particleData, const PxVec3& pos, const PxVec3& vel, float distance, unsigned sideNum);
void CreateParticleRand(ParticleData& particleData, const PxVec3& center, const PxVec3& range,const PxVec3& vel);
void SetParticleRestOffsetVariance(ParticleData& particleData, PxF32 maxRestOffset, PxF32 restOffsetVariance);

//----------------------------------------------------------------------------//

#endif // PARTICLE_FACTORY_H
