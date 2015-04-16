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

#ifndef SAMPLE_ALLOCATOR_SDK_CLASSES_H
#define SAMPLE_ALLOCATOR_SDK_CLASSES_H

#include "SampleAllocator.h"
#include "foundation/PxVec3.h"
#include "PsSync.h"
#include "geometry/PxBoxGeometry.h"
#include "RendererColor.h"
#include "vehicle/PxVehicleSDK.h"

	// PT: this is used to allocate SDK classes through the SampleAllocator

	class PxVec3Alloc				: public PxVec3,								public SampleAllocateable	{ public:	};
	class PsSyncAlloc				: public Ps::Sync,								public SampleAllocateable	{ public:	};
	class PxBoxGeometryAlloc		: public PxBoxGeometry,							public SampleAllocateable	{ public:	};
	class RendererColorAlloc		: public SampleRenderer::RendererColor,			public SampleAllocateable	{ public:	};

#endif
