/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef _SAMPLE_SUBMARINE_INPUT_EVENT_IDS_H
#define _SAMPLE_SUBMARINE_INPUT_EVENT_IDS_H

#include <SampleBaseInputEventIds.h>

// InputEvents used by SampleSubmarine
enum SampleSubmarineInputEventIds
{
	SAMPLE_SUBMARINE_FIRST = NUM_SAMPLE_BASE_INPUT_EVENT_IDS,

	SUBMARINE_FORWARD,
	SUBMARINE_BACKWARD,
	SUBMARINE_FORWARD_BACKWARD,
	SUBMARINE_UP,
	SUBMARINE_DOWN,

	CRAB_FORWARD,
	CRAB_BACKWARD,
	CRAB_LEFT,
	CRAB_RIGHT,
	CRAB_FORWARD_BACKWARD,
	CRAB_LEFT_RIGHT,

	CAMERA_SWITCH ,
	SCENE_RESET ,

	NUM_SAMPLE_SUBMARINE_INPUT_EVENT_IDS,
};

#endif
