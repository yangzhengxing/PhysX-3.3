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

#ifndef PARTICLE_EMITTER_RATE_H
#define PARTICLE_EMITTER_RATE_H

//----------------------------------------------------------------------------//

#include "ParticleEmitter.h"

//----------------------------------------------------------------------------//

class ParticleEmitterRate : public ParticleEmitter
{
public:
						ParticleEmitterRate(ParticleEmitter::Shape::Enum shape, PxReal	extentX, PxReal extentY, PxReal spacing);
	virtual				~ParticleEmitterRate();

	virtual		void	stepInternal(ParticleData& particles, PxReal dt, const PxVec3& externalAcceleration, PxReal maxParticleVelocity);

	void 				setRate(PxReal t)						{ mRate = t; }
	PxReal 				getRate()						const	{ return mRate; }

private:

	void initDenseSites();
	void shuffleDenseSites();
	void initSparseSiteHash(PxU32 numEmit, PxU32 sparseMax);
	PxU32 pickSparseEmissionSite(PxU32 sparseMax);

	PxReal				mRate;
	PxReal				mParticlesToEmit;
	std::vector<PxU32>	mSites;
};

//----------------------------------------------------------------------------//

#endif // PARTICLE_EMITTER_RATE_H
