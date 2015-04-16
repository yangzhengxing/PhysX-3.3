/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef _SAMPLE_NORTH_POLE_INPUT_EVENT_IDS_H
#define _SAMPLE_NORTH_POLE_INPUT_EVENT_IDS_H

#include <SampleBaseInputEventIds.h>

// InputEvents used by SampleNorthPole
enum SampleNorthPoleInputEventIds
{
	SAMPLE_NORTH_POLE_FIRST = NUM_SAMPLE_BASE_INPUT_EVENT_IDS,

	THROW_BALL ,
	RAYCAST_HIT,
	CROUCH ,
    CROUCH_TOGGLE ,
	RESET_SCENE ,

	NUM_SAMPLE_NORTH_POLE_INPUT_EVENT_IDS,
};

#endif
