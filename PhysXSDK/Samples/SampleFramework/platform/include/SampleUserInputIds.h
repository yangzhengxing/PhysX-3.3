/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef SAMPLE_USER_INPUT_IDS_H
#define SAMPLE_USER_INPUT_IDS_H


#if defined RENDERER_WINDOWS
#ifdef PX_XBOXONE
	#include <xboxone/XboxOneSampleUserInputIds.h>
#elif defined (RENDERER_WINMODERN)
	#include <winmodern/WinmodernSampleUserInput.h>
#else
	#include <windows/WindowsSampleUserInputIds.h>
#endif
#elif defined (RENDERER_XBOX360)
	#include <xbox360/Xbox360SampleUserInputIds.h>
#elif defined (RENDERER_PS3)
	#include <ps3/PS3SampleUserInputIds.h>
#elif defined (RENDERER_PSP2)
	#include <psp2/PSP2SampleUserInputIds.h>
#elif defined (RENDERER_PS4)
	#include <ps4/PS4SampleUserInputIds.h>
#elif defined (RENDERER_LINUX)
	#include <linux/LinuxSampleUserInputIds.h>
#elif defined (RENDERER_ANDROID)
	#include <android/AndroidSampleUserInputIds.h>
#elif defined (RENDERER_MACOSX)
	#include <osx/OSXSampleUserInputIds.h> 
#elif defined (RENDERER_IOS)
	#include <ios/IosSampleUserInputIds.h>
#elif defined (RENDERER_WIIU)
	#include <wiiu/WiiUSampleUserInputIds.h>
#else
	#error Unknown platform!
#endif

#endif
