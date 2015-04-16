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

#ifndef TEST_CLOTH_READ_DATA_LOCK
#define TEST_CLOTH_READ_DATA_LOCK

#include "PxStrideIterator.h"

#include "cloth/PxCloth.h"
#include "cloth/PxClothReadData.h"

namespace Test
{
	class ClothReadDataLock
	{
	public:
		ClothReadDataLock(PxCloth& cloth)	{ mReadData = cloth.lockClothReadData(); }
		~ClothReadDataLock()				{ mReadData->unlock(); }
		PxClothReadData* get()			{ return mReadData; }
	private:
		PxClothReadData* mReadData;
	};
};

#endif // TEST_CLOTH_READ_DATA_LOCK
