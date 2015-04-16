/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_FOUNDATION_H
#define RENDERER_FOUNDATION_H

#include <stdio.h>
#include "foundation/PxPreprocessor.h"

namespace physx
{
#ifdef PX_WIIU
	struct FILE;
#endif

	namespace shdfnd{}

	class PxCudaContextManager;
}

namespace SampleRenderer
{
	using namespace physx;
	namespace Fnd = physx::shdfnd;

#ifdef PX_WIIU
	typedef physx::FILE File;
#else
	typedef ::FILE File;
#endif

} // namespace Renderer

#include <foundation/PxSimpleTypes.h>
#include <foundation/PxVec3.h>
#include <foundation/PxMat33.h>
#include <foundation/PxMat44.h>
#include <foundation/PxTransform.h>
#include <foundation/PxErrorCallback.h>

#endif
