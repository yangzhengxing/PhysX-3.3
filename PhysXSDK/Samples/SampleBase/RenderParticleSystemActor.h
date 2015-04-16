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

#ifndef RENDER_PARTICLE_SYSTEM_ACTOR_H
#define RENDER_PARTICLE_SYSTEM_ACTOR_H

#include "RenderBaseActor.h"
#include "foundation/PxVec3.h"

namespace SampleRenderer
{
	class Renderer;
}
class ParticleSystem;

// NOTE: This class takes ownership of the passed ParticleSystem object.
class RenderParticleSystemActor : public RenderBaseActor
{
public:
										RenderParticleSystemActor(SampleRenderer::Renderer& renderer, 
																	ParticleSystem* ps,
																	bool _mesh_instancing = false,
																	bool _fading = false,
																	PxReal fadingPeriod = 1.0f,
																	PxReal debriScaleFactor = 1.0f);
	virtual								~RenderParticleSystemActor();

	virtual void						update(float deltaTime);
	void								updateSubstep(float deltaTime);
	ParticleSystem*						getParticleSystem() { return mPS; }
private:
	RenderParticleSystemActor& operator=(const RenderParticleSystemActor&);
	SampleRenderer::Renderer&			mRenderer;
	ParticleSystem*						mPS;
	bool								mUseMeshInstancing;
	bool								mUseSpritesMesh;
	bool								mFading;
};

#endif
