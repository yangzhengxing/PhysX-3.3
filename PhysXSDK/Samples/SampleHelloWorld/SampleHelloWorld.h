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


#ifndef SAMPLE_HELLO_WORLD_H
#define SAMPLE_HELLO_WORLD_H

#include "PhysXSample.h"

	class SampleHelloWorld : public PhysXSample
	{
		public:
												SampleHelloWorld(PhysXSampleApplication& app);
		virtual									~SampleHelloWorld();

		virtual	void							onTickPreRender(float dtime);
		virtual	void							onTickPostRender(float dtime);
		virtual	void							customizeSceneDesc(PxSceneDesc&);

		virtual	void							newMesh(const RAWMesh&);
		virtual	void							onInit();
        virtual	void						    onInit(bool restart) { onInit(); }

		virtual void							collectInputEvents(std::vector<const SampleFramework::InputEvent*>& inputEvents);
		virtual void							helpRender(PxU32 x, PxU32 y, PxU8 textAlpha);
		virtual	void							descriptionRender(PxU32 x, PxU32 y, PxU8 textAlpha);
		virtual PxU32							getDebugObjectTypes() const;
	};

#endif
