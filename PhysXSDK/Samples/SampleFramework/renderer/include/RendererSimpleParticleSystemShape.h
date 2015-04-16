/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_SIMPLE_PARTICLE_SYSTEM_SHAPE_H
#define RENDERER_SIMPLE_PARTICLE_SYSTEM_SHAPE_H

#include <RendererShape.h>

namespace SampleRenderer
{

	class RendererVertexBuffer;
	class RendererIndexBuffer;

	// this shape is used when no sprite rendering is possible - dx11 with feature dx9 for example
	class RendererSimpleParticleSystemShape : public RendererShape
	{
	public:
								RendererSimpleParticleSystemShape(Renderer &renderer, 
									physx::PxU32 num_vertices);
		virtual					~RendererSimpleParticleSystemShape(void);

		void					updateBillboard(PxU32 validParticleRange, 
										 const PxVec3* positions, 
										 const PxU32* validParticleBitmap,
										 const PxReal* lifetime = NULL);

	private:
		PxU32					mMaxParticles;
		RendererVertexBuffer*	mVertexBuffer;
		RendererIndexBuffer*	mIndexBuffer;

		void					initializeVertexBuffer(PxU32 color);
	};

} // namespace SampleRenderer

#endif
