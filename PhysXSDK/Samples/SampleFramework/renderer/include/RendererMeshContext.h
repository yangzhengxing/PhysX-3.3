/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_MESH_CONTEXT_H
#define RENDERER_MESH_CONTEXT_H

#include <RendererConfig.h>

namespace SampleRenderer
{

	class Renderer;
	class RendererMesh;
	class RendererMaterial;
	class RendererMaterialInstance;

	class RendererMeshContext
	{
		friend class Renderer;
	public:
		const RendererMesh       *mesh;
		RendererMaterial         *material;
		RendererMaterialInstance *materialInstance;
		const physx::PxMat44	 *transform;
		const physx::PxF32		 *shaderData;

		// TODO: this is kind of hacky, would prefer a more generalized
		//       solution via RendererMatrialInstance.
		const physx::PxMat44	 *boneMatrices;
		PxU32                     numBones;

		enum CullMode
		{
			CLOCKWISE = 0,
			COUNTER_CLOCKWISE,
			NONE
		};

		CullMode				cullMode;
		bool					screenSpace;		//TODO: I am not sure if this is needed!

		enum FillMode
		{
			SOLID,
			LINE,
			POINT,
		};
		FillMode				fillMode;

	public:
		RendererMeshContext(void);
		~RendererMeshContext(void);

		bool isValid(void) const;
	};

} // namespace SampleRenderer

#endif
