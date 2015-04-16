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

#ifndef TEST_GEOMETRY_HELPERS_H
#define TEST_GEOMETRY_HELPERS_H

#include "PxShape.h"
#include "extensions/PxShapeExt.h"
#include "geometry/PxGeometryQuery.h"
#include "Test.h"

namespace Test
{
	class GeometryHelpers
	{
	public:
		static bool testForOverlap(const PxShape& s0, const PxShape& s1);
		static bool testForOverlap(const PxShape& s0, const PxGeometry& g1, const PxTransform& globalPose1);
	};
}


#endif
