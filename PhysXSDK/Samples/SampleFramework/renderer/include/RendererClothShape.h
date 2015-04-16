/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_CLOTH_SHAPE_H
#define RENDERER_CLOTH_SHAPE_H

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
	class RendererIndexBuffer;

	class RendererClothShape : public RendererShape
	{
		enum VertexBufferEnum
		{
			STATIC_VB,
			DYNAMIC_VB,
			NUM_VERTEX_BUFFERS
		};
	public:
		RendererClothShape(Renderer& renderer, 
			const PxVec3* verts, PxU32 numVerts,
			const PxVec3* normals,
			const PxReal* uvs,
			const PxU16* faces, PxU32 numFaces, bool flipWinding=false,
			PxCudaContextManager* ctxMgr=NULL);
        
		// must acquire the cuda context and map buffers before calling
		bool update(CUdeviceptr srcVerts, PxU32 numVerts);
        void update(const PxVec3* verts, PxU32 numVerts, const PxVec3* normals);

		// helper functions to map the buffers for multiple shapes 
		// at once because interop mapping has a large per-call overhead
		// thread must acquire the cuda context before calling
		static void mapShapes(RendererClothShape** shapes, PxU32 n);
		static void unmapShapes(RendererClothShape** shapes, PxU32 n);

		virtual ~RendererClothShape();

		bool isInteropEnabled() const { return m_ctxMgr != NULL; }

	private:
		RendererVertexBuffer*	m_vertexBuffer[NUM_VERTEX_BUFFERS];
		RendererIndexBuffer*	m_indexBuffer;

		PxU32 m_numFaces;

		PxCudaContextManager* m_ctxMgr;
	};

} // namespace SampleRenderer

#endif
