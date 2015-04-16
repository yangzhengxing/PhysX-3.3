/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef _SAMPLE_VEHICLE_INPUT_EVENT_IDS_H
#define _SAMPLE_VEHICLE_INPUT_EVENT_IDS_H

#include <SampleBaseInputEventIds.h>

// InputEvents used by SampleVehicle
enum SampleVehicleInputEventIds
{
	SAMPLE_VEHICLE_FIRST_ID = NUM_SAMPLE_BASE_INPUT_EVENT_IDS,

	CAR_ACCELERATE_BRAKE,

	//KEYBOARD (car+tank)
	VEH_ACCELERATE_KBD,
	VEH_GEAR_UP_KBD,
	VEH_GEAR_DOWN_KBD,

	VEH_SAVE_KBD,

	//KEYBOARD (car)
	CAR_BRAKE_KBD,
	CAR_HANDBRAKE_KBD,
	CAR_STEER_LEFT_KBD,
	CAR_STEER_RIGHT_KBD,

	//KEYBOARD (tank)
	TANK_THRUST_LEFT_KBD,
	TANK_THRUST_RIGHT_KBD,
	TANK_BRAKE_LEFT_KBD,
	TANK_BRAKE_RIGHT_KBD,

	//KEYBOARD (camera)
	CAMERA_ROTATE_LEFT_KBD,
	CAMERA_ROTATE_RIGHT_KBD,
	CAMERA_ROTATE_UP_KBD,
	CAMERA_ROTATE_DOWN_KBD,

	//GAMEPAD (car+tank)
	VEH_ACCELERATE_PAD,
	VEH_GEAR_UP_PAD,
	VEH_GEAR_DOWN_PAD,

	//GAMEPAD (car)
	CAR_BRAKE_PAD,
	CAR_HANDBRAKE_PAD,
	CAR_STEER_PAD,

	//GAMEPAD (tank)
	TANK_THRUST_LEFT_PAD,
	TANK_THRUST_RIGHT_PAD,
	TANK_BRAKE_LEFT_PAD,
	TANK_BRAKE_RIGHT_PAD,

	//GAMEPAD (camera)
	CAMERA_ROTATE_LEFT_RIGHT_PAD,
	CAMERA_ROTATE_UP_DOWN_PAD,

	//
	AUTOMATIC_GEAR,
	DEBUG_RENDER_FLAG,
	DEBUG_RENDER_WHEEL ,
	DEBUG_RENDER_ENGINE,
	RETRY,
	FIX_CAR,
	CAMERA_LOCK,
	W3MODE,


	NUM_SAMPLE_VEHICLE_INPUT_EVENT_IDS,
};

#endif
