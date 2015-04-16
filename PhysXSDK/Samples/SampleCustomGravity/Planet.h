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

#ifndef PLANET_H
#define PLANET_H

#include "SampleAllocator.h"
#include "foundation/PxVec3.h"

	class PlanetMesh
	{
		public:
											PlanetMesh();
											~PlanetMesh();

							void			generate(const PxVec3& center, PxF32 radius, PxU32 nbX, PxU32 nbY);

			PX_FORCE_INLINE	PxU32			getNbVerts()	const	{ return mNbVerts;	}
			PX_FORCE_INLINE	PxU32			getNbTris()		const	{ return mNbTris;	}
			PX_FORCE_INLINE	const PxVec3*	getVerts()		const	{ return mVerts;	}
			PX_FORCE_INLINE	const PxU32*	getIndices()	const	{ return mIndices;	}

		protected:
							PxU32			mNbVerts;
							PxU32			mNbTris;
							PxVec3*			mVerts;
							PxU32*			mIndices;

							PxU8			checkCulling(const PxVec3& center, PxU32 index0, PxU32 index1, PxU32 index2)	const;
	};

#endif
