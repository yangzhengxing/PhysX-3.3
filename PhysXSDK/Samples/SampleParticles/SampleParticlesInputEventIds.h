/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef _SAMPLE_PARTICLES_INPUT_EVENT_IDS_H
#define _SAMPLE_PARTICLES_INPUT_EVENT_IDS_H

#include <SampleBaseInputEventIds.h>

// InputEvents used by SampleParticles
enum SampleParticlesInputEventIds
{
	SAMPLE_PARTICLES_FIRST = NUM_SAMPLE_BASE_INPUT_EVENT_IDS,

	RAYGUN_SHOT ,
	CHANGE_PARTICLE_CONTENT ,

	NUM_SAMPLE_PARTICLES_INPUT_EVENT_IDS,
};

#endif
