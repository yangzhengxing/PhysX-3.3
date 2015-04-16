/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef GL_INCLUDES_H
#define GL_INCLUDES_H

#if defined(RENDERER_WINDOWS)
	#if defined(RENDERER_ENABLE_OPENGL)
		#include <windows/WindowsGLIncludes.h>
	#endif
#elif defined(RENDERER_PS3)
    #include <ps3/PS3GLIncludes.h>
#elif defined(RENDERER_MACOSX)
    #include <osx/OSXGLIncludes.h>
#elif defined(RENDERER_XBOX360)
    #include <xbox360/Xbox360GLIncludes.h>
#elif defined(RENDERER_PS4)
    #include <ps4/PS4GLIncludes.h>
#elif defined(RENDERER_LINUX)
    #include <linux/LinuxGLIncludes.h>
#elif defined(RENDERER_ANDROID)
    #include <android/AndroidGLIncludes.h>
#elif defined(RENDERER_IOS)
#else
#error Undefined platform.
#endif


#endif
