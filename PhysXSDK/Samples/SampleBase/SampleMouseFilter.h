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

#ifndef SAMPLE_MOUSE_FILTER_H
#define SAMPLE_MOUSE_FILTER_H

#include "SampleAllocator.h"

	class MouseFilter : public SampleAllocateable
	{
		public:
								MouseFilter();
								MouseFilter(PxU32 length, PxReal weightModifier);
								~MouseFilter();

		PX_INLINE	PxReal		GetWeightModifier()						const	{ return mWeightModifier;		}
		PX_INLINE	void		SetWeightModifier(PxReal modifier)				{ mWeightModifier = modifier;	}

		PX_INLINE	PxU32		GetHistoryBufferLength()				const	{ return mHistoryBufferLength;	}
					bool		SetHistoryBufferLength(PxU32 length);

					void		Apply(PxReal& deltaMouseX, PxReal& deltaMouseY);
		private:
					PxReal		mWeightModifier;
					PxU32		mHistoryBufferLength;
					PxReal*		mHistoryBufferX;
					PxReal*		mHistoryBufferY;
	};

#endif
