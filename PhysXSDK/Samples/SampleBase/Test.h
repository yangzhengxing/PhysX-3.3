/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#include "Ps.h"

//! \file top level test include file

/* namespace trickery */
namespace physx
{
	// alias shared foundation to something usable
	namespace Ps = shdfnd;
}
// we need this until all our code lives in physx namespace
using namespace physx;
