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

#ifndef PARTICLE_EMITTER_PRESSURE_H
#define PARTICLE_EMITTER_PRESSURE_H

//----------------------------------------------------------------------------//

#include "ParticleEmitter.h"

//----------------------------------------------------------------------------//

class ParticleEmitterPressure : public ParticleEmitter
{

public:
						ParticleEmitterPressure(ParticleEmitter::Shape::Enum shape, PxReal	extentX, PxReal extentY, PxReal spacing);
	virtual				~ParticleEmitterPressure();

	virtual		void	stepInternal(ParticleData& particles, PxReal dt, const PxVec3& externalAcceleration, PxReal maxParticleVelocity);

				void	setMaxRate(PxReal v)									{ mMaxRate = v; }
				PxReal	getMaxRate() const										{ return mMaxRate; }


private:

	struct SiteData
	{
		PxVec3 position;
		PxVec3 velocity;
		bool predecessor;
		PxReal noiseZ;
	};

private:

	PxVec3 mSimulationAcceleration;
	PxReal mSimulationMaxVelocity;

	void clearPredecessors();

	bool stepEmissionSite(
		SiteData& siteData,
		ParticleData& spawnData,
		PxU32& spawnNum, 
		const PxU32 spawnMax,
		const PxVec3 &sitePos, 
		const PxVec3 &siteVel,
		const PxReal dt);

	void predictPredecessorPos(SiteData& siteData, PxReal dt);
	void updatePredecessor(SiteData& siteData, const PxVec3& position, const PxVec3& velocity);

private:

	std::vector<SiteData>	mSites;
	PxReal					mMaxZNoiseOffset;
	PxReal					mMaxRate;
};

//----------------------------------------------------------------------------//

#endif // PARTICLE_EMITTER_PRESSURE_H
