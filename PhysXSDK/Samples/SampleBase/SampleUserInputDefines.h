/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  

#ifndef SAMPLE_USER_INPUT_DEFINES_H
#define SAMPLE_UTILS_H

#if defined(RENDERER_WINDOWS) && !defined(PX_XBOXONE) 

#define DIGITAL_INPUT_EVENT_DEF(var, winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)   {\
	const SampleFramework::InputEvent* retVal = SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, false),winKey, #var); \
	if(retVal) inputEvents.push_back(retVal); } 
#define ANALOG_INPUT_EVENT_DEF(var, sensitivity, winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)  {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, true,sensitivity),winKey, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#if defined(RENDERER_TABLET)
#define TOUCH_INPUT_EVENT_DEF(var, caption, andrKey, iosKey, win8arm)   {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerTouchInputEvent(SampleFramework::InputEvent(var, false),win8arm,caption, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#else
#define TOUCH_INPUT_EVENT_DEF(var, caption, andrKey, iosKey, win8arm)
#endif


#elif defined(RENDERER_WINDOWS) && defined(PX_XBOXONE) 

#define DIGITAL_INPUT_EVENT_DEF(var, winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)   {\
	const SampleFramework::InputEvent* retVal = SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, false),xboxonekey, #var); \
	if(retVal) inputEvents.push_back(retVal); } 
#define ANALOG_INPUT_EVENT_DEF(var, sensitivity, winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)  {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, true,sensitivity),xboxonekey, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define TOUCH_INPUT_EVENT_DEF(var, caption, andrKey, iosKey, win8arm)

#elif defined (RENDERER_XBOX360) 

#define DIGITAL_INPUT_EVENT_DEF(var, winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)   {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, false),xbox360key, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define ANALOG_INPUT_EVENT_DEF(var, sensitivity,  winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)  {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, true,sensitivity),xbox360key, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define TOUCH_INPUT_EVENT_DEF(var, caption, andrKey, iosKey, win8arm)

#elif defined (RENDERER_PS4)	

#define DIGITAL_INPUT_EVENT_DEF(var, winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)   {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, false),ps4Key, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define ANALOG_INPUT_EVENT_DEF(var, sensitivity,  winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)  {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, true,sensitivity),ps4Key, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define TOUCH_INPUT_EVENT_DEF(var, caption, andrKey, iosKey, win8arm)

#elif defined (RENDERER_PSP2)	

#define DIGITAL_INPUT_EVENT_DEF(var, winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)   {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, false),psp2Key, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define ANALOG_INPUT_EVENT_DEF(var, sensitivity,  winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)  {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, true,sensitivity),psp2Key, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define TOUCH_INPUT_EVENT_DEF(var, caption, andrKey, iosKey, win8arm)

#elif defined (RENDERER_PS3)	

#define DIGITAL_INPUT_EVENT_DEF(var, winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)   {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, false),ps3Key, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define ANALOG_INPUT_EVENT_DEF(var, sensitivity,  winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)  {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, true,sensitivity),ps3Key, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define TOUCH_INPUT_EVENT_DEF(var, caption, andrKey, iosKey, win8arm)

#elif defined (RENDERER_ANDROID)	

#define DIGITAL_INPUT_EVENT_DEF(var, winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)   {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, false),andrKey, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define ANALOG_INPUT_EVENT_DEF(var, sensitivity,  winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)  {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, true,sensitivity),andrKey, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define TOUCH_INPUT_EVENT_DEF(var, caption, andrKey, iosKey, win8arm) {\
    const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerTouchInputEvent(SampleFramework::InputEvent(var, false),andrKey,caption, #var)); \
	if(retVal) inputEvents.push_back(retVal); }

#elif defined (RENDERER_MACOSX)	

#define DIGITAL_INPUT_EVENT_DEF(var, winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)   {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, false),osxKey, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define ANALOG_INPUT_EVENT_DEF(var, sensitivity,  winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)  {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, true,sensitivity),osxKey, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define TOUCH_INPUT_EVENT_DEF(var, caption, andrKey, iosKey, win8arm)

#elif defined (RENDERER_IOS)	

#define DIGITAL_INPUT_EVENT_DEF(var, winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)   {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, false),iosKey, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define ANALOG_INPUT_EVENT_DEF(var, sensitivity,  winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)  {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, true,sensitivity),iosKey, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define TOUCH_INPUT_EVENT_DEF(var, caption, andrKey, iosKey, win8arm)   {\
    const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerTouchInputEvent(SampleFramework::InputEvent(var, false),iosKey,caption, #var)); \
	if(retVal) inputEvents.push_back(retVal); }

#elif defined (RENDERER_LINUX)	

#define DIGITAL_INPUT_EVENT_DEF(var, winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)  {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, false),linuxKey, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define ANALOG_INPUT_EVENT_DEF(var, sensitivity,  winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)  {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, true,sensitivity),linuxKey, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define TOUCH_INPUT_EVENT_DEF(var, caption, andrKey, iosKey, win8arm)

#elif defined (RENDERER_WIIU)	

#define DIGITAL_INPUT_EVENT_DEF(var, winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)  {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, false), wiiuKey, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define ANALOG_INPUT_EVENT_DEF(var, sensitivity,  winKey, xbox360key, xboxonekey, ps3Key, ps4Key, andrKey, osxKey, psp2Key, iosKey, linuxKey, wiiuKey)  {\
	const SampleFramework::InputEvent* retVal = (SampleFramework::SamplePlatform::platform()->getSampleUserInput()->registerInputEvent(SampleFramework::InputEvent(var, true,sensitivity), wiiuKey, #var)); \
	if(retVal) inputEvents.push_back(retVal); }
#define TOUCH_INPUT_EVENT_DEF(var, caption, andrKey, iosKey, win8arm)

#endif
#endif
