/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


#ifndef NX_MODULE_IOFX_H
#define NX_MODULE_IOFX_H

#include "NxApex.h"
#include "NxTestBase.h"

namespace physx
{
namespace apex
{

PX_PUSH_PACK_DEFAULT

class NxIofxAsset;
class NxIofxAssetAuthoring;
class NxApexRenderVolume;

/**
IOFX Module. This module is used to convert physical parameters of particles into visual parameters
that can be used to render particles.  NxApexRenderVolume provide the ability to partition world space
into separate renderables.
*/
class NxModuleIofx : public NxModule
{
protected:
	virtual							~NxModuleIofx() {}

public:
	/// Disable use of OGL/D3D Interop.  Must be called before emitters are created to have any effect
	virtual void                    disableCudaInterop() = 0;

	/// Disable use of CUDA IOFX modifiers. Must be called before emitters are created to have any effect
	virtual void                    disableCudaModifiers() = 0;

	/** \brief Disables deferred allocation of IOFX actors
	 *
	 * By default, IOFX actors and their render resources will not be
	 * created until it has objects to render.
	 */
	virtual void                    disableDeferredRenderableAllocation() = 0;

	/** \brief Create a new render volume
	 *
	 * Render volumes may be created at any time, unlike most other APEX
	 * asset and actor types.  Their insertion into the scene is
	 * deferred if the simulation is active.
	 */
	virtual NxApexRenderVolume*     createRenderVolume(const NxApexScene& apexScene, const PxBounds3& b, PxU32 priority, bool allIofx) = 0;

	/** \brief Release a render volume
	 *
	 * Render volumes may be released at any time, unlike most other APEX
	 * asset and actor types.  If the simulation is active, their
	 * resources are released at the end of the simulation step.
	 */
	virtual void                    releaseRenderVolume(NxApexRenderVolume& volume) = 0;

	/// Get NxTestBase implementation of Iofx scene
	virtual const NxTestBase*						getTestBase(NxApexScene* apexScene) const = 0;
};


PX_POP_PACK

}
} // namespace physx::apex

#endif // #ifndef NX_MODULE_IOFX_H
