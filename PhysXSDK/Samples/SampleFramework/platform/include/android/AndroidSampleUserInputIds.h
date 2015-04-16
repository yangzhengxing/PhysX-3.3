/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef ANDROID_SAMPLE_USER_INPUT_IDS_H
#define ANDROID_SAMPLE_USER_INPUT_IDS_H

namespace SampleFramework
{
	enum AndroidSampleUserInputIds
	{
		AKEY_UNKNOWN = 0,
		
		AKEY_DEFINITION_START,

		AKEY_A,
		AKEY_B,
		AKEY_C,
		AKEY_D,
		AKEY_E,
		AKEY_F,
		AKEY_G,
		AKEY_H,
		AKEY_I,
		AKEY_J,
		AKEY_K,
		AKEY_L,
		AKEY_M,
		AKEY_N,
		AKEY_O,
		AKEY_P,
		AKEY_Q,
		AKEY_R,
		AKEY_S,
		AKEY_T,
		AKEY_U,
		AKEY_V,
		AKEY_W,
		AKEY_X,
		AKEY_Y,
		AKEY_Z,

		AKEY_0,
		AKEY_1,
		AKEY_2,
		AKEY_3,
		AKEY_4,
		AKEY_5,
		AKEY_6, 
		AKEY_7,
		AKEY_8,
		AKEY_9,

		AKEY_SPACE,
		AKEY_RETURN,
		AKEY_SHIFT,		
		AKEY_ESCAPE,
		AKEY_COMMA, 
		AKEY_MULTIPLY,
		AKEY_ADD,
		AKEY_SEPARATOR,
		AKEY_SUBTRACT,
		AKEY_DIVIDE,

		AKEY_TAB,
		AKEY_PRIOR,
		AKEY_NEXT,
		AKEY_UP,
		AKEY_DOWN,
		AKEY_LEFT,
		AKEY_RIGHT,
		
		AKEY_DEFINITION_END,
		
		GAMEPAD_DEFINITION_START,

		GAMEPAD_RIGHT_STICK_X , 
		GAMEPAD_RIGHT_STICK_Y ,
		GAMEPAD_LEFT_STICK_X , 
		GAMEPAD_LEFT_STICK_Y ,
		
		GAMEPAD_DEFINITION_END,

		ABUTTON_1,
		ABUTTON_2,
		ABUTTON_3,
		ABUTTON_4,
		ABUTTON_5,
		ABUTTON_6,
		ABUTTON_7,
		ABUTTON_8,
		ABUTTON_9,

		AQUICK_BUTTON_1,

		ASELECTOR_BUTTON1,
		ASELECTOR_BUTTON2,

		ALAST_BUTTON,

		AFREETAP,

		NUM_KEY_CODES,
	};
	
}

#endif
