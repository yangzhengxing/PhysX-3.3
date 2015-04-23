/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


#ifndef NX_IOFX_ACTOR_H
#define NX_IOFX_ACTOR_H

#include "NxApex.h"
#include "NxIofxAsset.h"

namespace physx
{
namespace apex
{

PX_PUSH_PACK_DEFAULT

/**
IOFX actor public interface
*/
class NxIofxActor : public NxApexActor, public NxApexRenderable
{
public:
	///get the radius of the partice
	virtual physx::PxF32				getObjectRadius() const = 0;
	///get the number of particles
	virtual physx::PxU32				getObjectCount() const = 0;
	///get the number of visible particles (if sprite depth sorting is enabled, returns only number of particles in front of camera)
	virtual physx::PxU32				getVisibleCount() const = 0;
	///get the name of the IOS asset used to feed partices to the IOFX
	virtual const char*                 getIosAssetName() const = 0;
};

PX_POP_PACK

}
} // namespace physx::apex

#endif // NX_IOFX_ACTOR_H
