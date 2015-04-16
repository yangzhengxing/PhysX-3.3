/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_PROJECTION_H
#define RENDERER_PROJECTION_H

#include <RendererConfig.h>

namespace SampleRenderer
{

	class RendererProjection
	{
		public:
			RendererProjection(float fov, float aspectRatio, float nearPlane, float farPlane);
			RendererProjection(float left, float right, float bottom, float top, float near, float far);
			RendererProjection(const PxMat44 mat);
			
			void getColumnMajor44(float *f) const;
			void getRowMajor44(float *f) const;
			operator PxMat44 () const { return *reinterpret_cast<const PxMat44*>( m_matrix ); }
			PxMat44& getPxMat44() { return reinterpret_cast<PxMat44&>(*m_matrix ); }
			const PxMat44& getPxMat44() const { return reinterpret_cast<const PxMat44&>(*m_matrix ); }
			
		private:
			float m_matrix[16];
	};

	void   buildProjectMatrix(float *dst, const RendererProjection &proj, const physx::PxTransform &view);
	void   buildUnprojectMatrix(float *dst, const RendererProjection &proj, const physx::PxTransform &view);
	PxVec3 unproject(const RendererProjection &proj, const physx::PxTransform &view, PxF32 x, PxF32 y, PxF32 z = 0);
	PxVec3 project(  const RendererProjection &proj, const physx::PxTransform &view, const PxVec3& pos);

} // namespace SampleRenderer

#endif
