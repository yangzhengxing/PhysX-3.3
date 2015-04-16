/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


#ifndef SAMPLE_ACTOR_H
#define SAMPLE_ACTOR_H

#include "FrameworkFoundation.h"

namespace SampleFramework
{

	class SampleActor
	{
	public:
		SampleActor(void) {}
		virtual ~SampleActor(void) {}

		void release(void) { delete this; }

	public:
		virtual void tick(float /*dtime*/, bool /*rewriteBuffers*/ = false) {}
		virtual void render(bool /*rewriteBuffers*/ = false) {}
		//virtual void render(const PxMat44 &eyeT) { render(); } // TODO: provide a version of render() with some info about the current scene like camera pose...
		virtual int getType() { return -1; }
	};

} // namespace SampleFramework

#endif
