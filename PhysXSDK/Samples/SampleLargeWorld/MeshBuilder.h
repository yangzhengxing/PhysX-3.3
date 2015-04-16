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

#ifndef MESHBUILDER_H
#define MESHBUILDER_H

#include "PhysXSample.h"

class SampleLargeWorld;
class MeshBuilder : public SampleAllocateable
{
public:
	MeshBuilder(SampleLargeWorld& sample, const char* filename);
	~MeshBuilder() {}
	
	void			addRepXToPxCollection(
												const PxTransform&		pose, 
												const PxVec3&			scale, 
												PxCollection&			collection,
												const char*				name = NULL);

	static void		addObjMeshToPxCollection(
												PxPhysics&				physics,
												PxCooking&				cooking,
												PxMaterial&				material,
												const char*				filename,
												const char*				filenameCooked,
												const PxTransform&		pose, 
												const PxVec3&			scale, 
												PxCollection&			collection,
												const char*				name = NULL);

private:
	MeshBuilder& operator=(const MeshBuilder&);
	SampleLargeWorld*	mSampleLargeWorld;

	PxPhysics&			mPhysics;
	PxScene&			mScene;
	PxCooking&			mCooking;
	PxMaterial&			mMaterial;
	PxRigidStatic*		mStaticActor;
	PxStringTable*		mStringTable;

	std::vector<PxConvexMesh*>		mConvexMeshes;
	std::vector<PxTriangleMesh*>	mTriMeshes;
};


#endif
