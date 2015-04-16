/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef _SAMPLE_LARGE_WORLD_INPUT_EVENT_IDS_H
#define _SAMPLE_LARGE_WORLD_INPUT_EVENT_IDS_H

#include <SampleBaseInputEventIds.h>

// InputEvents used by SampleCharacterController
enum SampleLargeWorldInputEventIds
{
	SAMPLE_LARGE_WORLD_FIRST = NUM_SAMPLE_BASE_INPUT_EVENT_IDS,
	
	RETRY,
	THROW_IMPORTANTOBJECT,
	THROW_UNIMPORTANCTOBJECT,
	PICK_NEARSETOBJECT,
	FLY_CAMERA, 
	NUM_SAMPLE_LARGE_WORLD_INPUT_EVENT_IDS,
};

#endif
