/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef _SAMPLE_BRIDGES_INPUT_EVENT_IDS_H
#define _SAMPLE_BRIDGES_INPUT_EVENT_IDS_H

#include <SampleBaseInputEventIds.h>

// InputEvents used by SampleBridges
enum SampleBridgesInputEventIds
{
	SAMPLE_BRIDGES_FIRST_ID = NUM_SAMPLE_BASE_INPUT_EVENT_IDS,

	RETRY,
	CAMERA_LINK,
	TELEPORT,
	DEBUG_RENDER,

	NUM_SAMPLE_BRIDGS_INPUT_EVENT_IDS

};

#endif
