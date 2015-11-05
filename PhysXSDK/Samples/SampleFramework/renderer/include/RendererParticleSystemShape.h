/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_PARTICLE_SYSTEM_SHAPE_H
#define RENDERER_PARTICLE_SYSTEM_SHAPE_H

#include <RendererShape.h>

namespace physx
{
	namespace pxtask
	{
		class CudaContextManager;
	}
}

// fwd to avoid including cuda.h
#if defined(__x86_64) || defined(AMD64) || defined(_M_AMD64)
typedef unsigned long long CUdeviceptr;
#else
typedef unsigned int CUdeviceptr;
#endif

namespace SampleRenderer
{

	class RendererVertexBuffer;
	class RendererInstanceBuffer;
	class RendererIndexBuffer;

	class RendererParticleSystemShape : public RendererShape
	{
		enum VertexBufferEnum
		{
			STATIC_VB,
			DYNAMIC_POS_VB,
			DYNAMIC_COL_VB,
			NUM_VERTEX_BUFFERS
		};

	public:
								RendererParticleSystemShape(Renderer &renderer, 
									physx::PxU32 num_vertices, 
									bool _mInstanced,
									bool _mFading,
									PxReal fadingPeriod = 1.0f,
									PxReal debriScaleFactor = 1.0f,
									PxCudaContextManager* ctxMgr=NULL
									);
		virtual					~RendererParticleSystemShape(void);

		bool					updateBillboard(PxU32 validParticleRange, 
										CUdeviceptr positions, 
										CUdeviceptr validParticleBitmap,
										CUdeviceptr lifetimes,
										PxU32 numParticles);

		bool					updateInstanced(PxU32 validParticleRange, 
										CUdeviceptr positions, 
										CUdeviceptr validParticleBitmap,
										CUdeviceptr orientations,
										PxU32 numParticles);

		void					updateBillboard(PxU32 validParticleRange, 
										 const PxVec3* positions, 
										 const PxU32* validParticleBitmap,
										 const PxReal* lifetime = NULL);

		void					updateInstanced(PxU32 validParticleRange, 
										const PxVec3* positions, 
										const PxU32* validParticleBitmap,
										const PxMat33* orientation);

		bool					isInteropEnabled() { return mCtxMgr != NULL; }

	private:
		bool					mInstanced;
		bool					mFading;
		PxReal					mFadingPeriod;
		PxU32					mMaxParticles;
		RendererVertexBuffer*	mVertexBuffer[NUM_VERTEX_BUFFERS];
		RendererInstanceBuffer*	mInstanceBuffer;
		RendererIndexBuffer*	mIndexBuffer;

		PxCudaContextManager*	mCtxMgr;

		void					initializeVertexBuffer(PxU32 color);
		void					initializeBuffersAsSimpleConvex(PxU32 color, PxReal scaleFactor);
		void					initializeInstanceBuffer();
	};

} // namespace SampleRenderer

#endif
