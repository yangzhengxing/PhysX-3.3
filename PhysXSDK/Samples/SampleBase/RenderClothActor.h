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

#ifndef RENDER_CLOTH_ACTOR_H
#define RENDER_CLOTH_ACTOR_H

#include "RenderBaseActor.h"
#include "RenderPhysX3Debug.h"

#include "SampleAllocator.h"
#include "SampleArray.h"

#include "cloth/PxCloth.h"
#include "extensions/PxClothMeshDesc.h"
#include "RenderMaterial.h"

namespace SampleRenderer
{
	class Renderer;
    class RendererClothShape;
}

class RenderCapsuleActor;
class RenderSphereActor;
class RenderMeshActor;

class RenderClothActor : public RenderBaseActor
{
public:
	RenderClothActor( SampleRenderer::Renderer& renderer, const PxCloth& cloth, const PxClothMeshDesc &desc, const PxVec2* uvs = NULL, PxReal capsuleScale = 1.0f);

	virtual								~RenderClothActor();

	virtual void						update(float deltaTime);
	virtual	void						render(SampleRenderer::Renderer& renderer, RenderMaterial* material, bool wireFrame);
	void								setConvexMaterial(RenderMaterial* material);

	virtual SampleRenderer::RendererClothShape*	getRenderClothShape() const { return mClothRenderShape; }
	virtual const PxCloth*				getCloth() const { return &mCloth; }

private:
	void								updateRenderShape();

private:

	RenderClothActor& operator=(const RenderClothActor&);

	void								freeCollisionRenderSpheres();
	void								freeCollisionRenderCapsules();

	SampleRenderer::Renderer&			mRenderer;
	const PxCloth&                      mCloth; 

	// copied mesh structure 
	PxU32                               mNumFaces;
	PxU16*                              mFaces;

	// collision data used for debug rendering
	PxClothCollisionSphere*             mSpheres;
	PxU32*                              mCapsules;
	PxClothCollisionPlane*				mPlanes;
	PxU32*								mConvexes;
	PxClothCollisionTriangle*			mTriangles;
	PxU32                               mNumSpheres, mNumCapsules, mNumPlanes, mNumConvexes, mNumTriangles;

	// texture uv (used only for render)
	PxReal*								mUV;

	PxVec3								mRendererColor;
	PxReal                              mCapsuleScale;

    SampleRenderer::RendererClothShape* mClothRenderShape;
	RenderMaterial*						mConvexMaterial;

	// collision shapes render actors
	shdfnd::Array<RenderSphereActor*>	mSphereActors;
	shdfnd::Array<RenderCapsuleActor*>	mCapsuleActors;

	RenderMeshActor*					mMeshActor;
	shdfnd::Array<PxU16>				mMeshIndices;

	RenderMeshActor*					mConvexActor;
	shdfnd::Array<PxVec3>				mConvexVertices;
	shdfnd::Array<PxU16>				mConvexIndices;

	shdfnd::Array<PxVec3>				mClothVertices;
	shdfnd::Array<PxVec3>				mClothNormals;

};

#endif
