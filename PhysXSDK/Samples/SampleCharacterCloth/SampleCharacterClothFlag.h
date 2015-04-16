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

#ifndef SAMPLE_CHARACTER_CLOTH_FLAG_H
#define SAMPLE_CHARACTER_CLOTH_FLAG_H

#include "cloth/PxCloth.h"
#include "PhysXSample.h"

class SampleCharacterCloth;
class RenderClothActor;

class SampleCharacterClothFlag
{
public:
    SampleCharacterClothFlag(SampleCharacterCloth& sample, const PxTransform &pose, PxU32 resX, PxU32 resY, PxReal sizeX, PxReal sizeY, PxReal height);

	void     setWind(const PxVec3 &dir, PxReal strength, const PxVec3& range);
    void     update(PxReal dtime);
	void     release();
	PxCloth* getCloth() { return mCloth; }
    
protected:
	RenderClothActor*		mRenderActor;
	SampleCharacterCloth&	mSample;
    PxCloth*                mCloth;
    SampleArray<PxVec2>     mUVs;
    PxVec3                  mWindDir;
    PxVec3                  mWindRange;
	PxReal                  mWindStrength;
    PxReal                  mTime;
	PxRigidDynamic*			mCapsuleActor;
private:
	SampleCharacterClothFlag& operator=(const SampleCharacterClothFlag&);
};

#endif
