/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_CONFIG_H
#define RENDERER_CONFIG_H

#include <RendererFoundation.h>
#include <assert.h>

#define RENDERER_TEXT(_foo)   #_foo
#define RENDERER_TEXT2(_foo)  RENDERER_TEXT(_foo)

// number of lights required before it switches from forward rendering to deferred rendering.
#define RENDERER_DEFERRED_THRESHOLD  0x7FFFFFFF // set to a big number just to disable it for now...

// Enables/Disables support for dresscode in the renderer...
#define RENDERER_ENABLE_DRESSCODE 0

// If turned on, asserts get compiled in as print statements in release mode.
#define RENDERER_ENABLE_CHECKED_RELEASE 0

// If enabled, all lights will be bound in a single pass. Requires appropriate shader support.
#define RENDERER_ENABLE_SINGLE_PASS_LIGHTING 0

// maximum number of bones per-drawcall allowed.
#if defined(__CELLOS_LV2__)
#define RENDERER_MAX_BONES 50
#else
#define RENDERER_MAX_BONES 60
#endif

#define RENDERER_TANGENT_CHANNEL            5
#define RENDERER_BONEINDEX_CHANNEL          6
#define RENDERER_BONEWEIGHT_CHANNEL         7
#define RENDERER_INSTANCE_POSITION_CHANNEL  8
#define RENDERER_INSTANCE_NORMALX_CHANNEL   9
#define RENDERER_INSTANCE_NORMALY_CHANNEL  10
#define RENDERER_INSTANCE_NORMALZ_CHANNEL  11
#define RENDERER_INSTANCE_VEL_LIFE_CHANNEL 12
#define RENDERER_INSTANCE_DENSITY_CHANNEL  13

#define RENDERER_INSTANCE_UV_CHANNEL       12
#define RENDERER_INSTANCE_LOCAL_CHANNEL    13

#define RENDERER_DISPLACEMENT_CHANNEL      14
#define RENDERER_X_DISPLACEMENT_CHANNEL    13
#define RENDERER_Y_DISPLACEMENT_CHANNEL    14
#define RENDERER_Z_DISPLACEMENT_CHANNEL    15
#define RENDERER_DISPLACEMENT_FLAGS_CHANNEL 15

// Compiler specific configuration...
#if defined(_MSC_VER)
#define RENDERER_VISUALSTUDIO
#pragma warning(disable : 4127) // conditional expression is constant
#pragma warning(disable : 4100) // unreferenced formal parameter

#elif defined(__ghs__)
	#define RENDERER_GHS
#elif defined(__GNUC__)
	#define RENDERER_GCC
#elif defined (SN_TARGET_PSP2)
	#define RENDERER_GXM
#else
#error Unknown Compiler!

#endif

// Platform specific configuration...
#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_PARTITION_APP) && !defined(PX_XBOXONE)
	#define RENDERER_WINDOWS
	#define RENDERER_ENABLE_DIRECT3D11
	#define RENDERER_ENABLE_TGA_SUPPORT
	#define RENDERER_WINMODERN

#if defined(_M_ARM)
	#define RENDERER_TABLET
#endif

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#elif defined(WIN32) || defined(WIN64) || defined(_M_ARM) || defined(PX_XBOXONE)
	#define RENDERER_WINDOWS
#ifndef PX_XBOXONE
	#define RENDERER_ENABLE_DIRECT3D9
#endif
	#define RENDERER_ENABLE_DIRECT3D11
	#define RENDERER_ENABLE_NVPERFHUD
	#define RENDERER_ENABLE_TGA_SUPPORT
	#if !defined(RENDERER_PVD) && !defined(PX_XBOXONE) && PX_SUPPORT_GPU_PHYSX
		#define RENDERER_ENABLE_CUDA_INTEROP 
	#endif
	#define	DIRECT3D9_SUPPORT_D3DUSAGE_DYNAMIC
	#if defined(WIN64)
		#define RENDERER_64BIT
	#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define NOMINMAX
#include <windows.h>
#elif defined(__APPLE__) && !defined(__arm__) && !defined(__arm64__)
#define RENDERER_MACOSX
#define RENDERER_ENABLE_OPENGL
#define RENDERER_ENABLE_CG
#if !defined(PX_PPC)
#define RENDERER_ENABLE_TGA_SUPPORT
#endif

#elif defined(_XBOX) && _XBOX_VER == 200
#define RENDERER_XBOX360
#define RENDERER_ENABLE_DIRECT3D9
#define NOMINMAX
#define RENDERER_ENABLE_TGA_SUPPORT
#define RENDERER_BIG_ENDIAN

#elif defined(__CELLOS_LV2__)
#define RENDERER_PS3
#define RENDERER_ENABLE_OPENGL
#define RENDERER_ENABLE_LIBGCM
#define RENDERER_ENABLE_CG
#define RENDERER_ENABLE_TGA_SUPPORT
#define RENDERER_BIG_ENDIAN

#elif defined(PX_PS4)
	#define RENDERER_PS4
	#define RENDERER_ENABLE_LIBGNM
	#define RENDERER_ENABLE_CG
	#define RENDERER_ENABLE_TGA_SUPPORT

#elif defined(__CYGWIN__)
#define RENDERER_LINUX
#define RENDERER_ENABLE_OPENGL
#define RENDERER_ENABLE_CG
#define RENDERER_ENABLE_TGA_SUPPORT

#elif defined(ANDROID)
	#define RENDERER_DEBUG
	#define RENDERER_ANDROID
	#define RENDERER_TABLET
	#define RENDERER_ENABLE_GLES2
	#define RENDERER_ENABLE_TGA_SUPPORT

#elif defined(__linux__)
	#define RENDERER_LINUX
	#define RENDERER_ENABLE_OPENGL
	#define RENDERER_ENABLE_CG
	#define RENDERER_ENABLE_TGA_SUPPORT

#elif defined(__APPLE__) && (defined(__arm__) || defined(__arm64__))
	#define RENDERER_DEBUG
	#define RENDERER_IOS
	#define RENDERER_TABLET
	#define RENDERER_ENABLE_GLES2
	#define RENDERER_ENABLE_TGA_SUPPORT
	#define RENDERER_ENABLE_PVR_SUPPORT

#elif defined(SN_TARGET_PSP2)
	#define RENDERER_PSP2
	#define RENDERER_ENABLE_LIBGXM
	#define RENDERER_ENABLE_TGA_SUPPORT	

#elif defined(RENDERER_GHS)
	#define RENDERER_WIIU
	#define RENDERER_ENABLE_GX2
	#define RENDERER_ENABLE_TGA_SUPPORT
	#define RENDERER_BIG_ENDIAN

#else
#error "Unknown Platform!"

#endif

#if defined(PX_DEBUG)
#define RENDERER_DEBUG
#endif

#ifdef PHYSX_PROFILE_SDK
#include "SamplePxProfileZone.h"
#define RENDERER_PERFZONE(_name) SAMPLE_PERF_SCOPE(_name)
#else
#define RENDERER_PERFZONE(_name)
#endif

#if defined(RENDERER_DEBUG)
	#if defined(RENDERER_WINDOWS) && !defined (PX_XBOXONE) && !defined(RENDERER_WINMODERN)
		#define RENDERER_ASSERT(_exp, _msg)                     \
		    if(!(_exp))                                         \
		    {                                                   \
		        MessageBoxA(0, _msg, "Renderer Assert", MB_OK); \
		        __debugbreak();                                 \
		    }
	#elif defined(RENDERER_ANDROID)
	#include <android/log.h>
	#define RENDERER_ASSERT(_exp, _msg)													\
		if(!(_exp))																		\
			__android_log_print(ANDROID_LOG_INFO, _msg, "RENDERER_ASSERT: %s\n", #_exp);\
		assert(_exp && (_msg));
	#else
		#define RENDERER_ASSERT(_exp, _msg) assert(_exp && (_msg));
	#endif
#elif RENDERER_ENABLE_CHECKED_RELEASE
#if defined(RENDERER_VISUALSTUDIO)
#define RENDERER_ASSERT(_exp, _msg)                                          \
	if(!(_exp))                                                              \
	{                                                                        \
		OutputDebugStringA("*** (" __FILE__":"RENDERER_TEXT2(__LINE__)") "); \
		OutputDebugStringA(_msg);                                            \
		OutputDebugStringA(" ***\n");                                        \
	}
#else
#define RENDERER_ASSERT(_exp, _msg) if(!(_exp)) shdfnd::printFormatted("*** (" __FILE__ ":" RENDERER_TEXT2(__LINE__)") %s ***\n", _msg);
#endif
#else
#define RENDERER_ASSERT(_exp, _msg)
#endif

#define RENDERER_OUTPUT_MESSAGE(_rendererPtr, _msg) \
	if((_rendererPtr) && (_rendererPtr)->getErrorCallback()) \
	{ \
		(_rendererPtr)->getErrorCallback()->reportError(PxErrorCode::eDEBUG_INFO, (_msg), __FILE__, __LINE__); \
	}


#if defined(RENDERER_ANDROID)
	#include <android/log.h>
	#define LOG_INFO(title, ...) ((void)__android_log_print(ANDROID_LOG_INFO, title, __VA_ARGS__))
#else

#if 0
	#include <stdio.h>
	#include <stdarg.h>

	static void printInfo(const char* title, const char* message, ...)
	{
		char buff[4096];
		
		shdfnd::printFormatted("%s ", title);
		va_list va;
		va_start(va, message);
		vsprintf(buff, message, va);
		va_end(va);
		if (strlen(buff)>=4096)
			assert(!"buffer overflow!!");
		
		shdfnd::printFormatted("%s\n", buff);
	}

	#define LOG_INFO(title, ...) (printInfo(title, __VA_ARGS__))
#else
	#define LOG_INFO(title, ...)
#endif

#endif

#if defined(RENDERER_XBOX360)
#define RENDERER_INSTANCING 0
#else
#define RENDERER_INSTANCING 1
#endif

namespace SampleRenderer
{
	// 2D and 3D Textures have identical external interfaces
	//    Using a typedef provides compatibility with legacy code that used only 2D textures
	class RendererTexture;
	class RendererTextureDesc;
	typedef RendererTexture     RendererTexture2D;
	typedef RendererTextureDesc RendererTexture2DDesc;
	typedef RendererTexture     RendererTexture3D;
	typedef RendererTextureDesc RendererTexture3DDesc;
}
#if defined(RENDERER_ANDROID) && !defined(LOGI)
#	include <android/log.h>
#	define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "RendererConfig", __VA_ARGS__))
#else
#	define LOGI(...) LOG_INFO("LOGI: ", __VA_ARGS__)
#endif

#endif
