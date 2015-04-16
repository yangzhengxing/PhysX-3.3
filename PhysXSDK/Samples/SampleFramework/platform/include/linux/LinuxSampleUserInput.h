/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef LINUX_SAMPLE_USER_INPUT_H
#define LINUX_SAMPLE_USER_INPUT_H

#include <X11/Xlib.h>
#include <SampleUserInput.h>
#include <linux/LinuxSampleUserInputIds.h>
#include <set>


namespace SampleFramework
{
	class LinuxSampleUserInput: public SampleUserInput
	{
	public:

		LinuxSampleUserInput();
		~LinuxSampleUserInput();
		
		void doOnMouseMove( physx::PxU32 x, physx::PxU32 y, physx::PxReal dx, physx::PxReal dy, physx::PxU16 button);
		void doOnMouseDown( physx::PxU32 x, physx::PxU32 y, physx::PxU16 button);
		void doOnMouseUp( physx::PxU32 x, physx::PxU32 y, physx::PxU16 button);
		void doOnKeyDown( KeySym keySym, physx::PxU16 keyCode, physx::PxU8 ascii);
		void doOnKeyUp( KeySym keySym, physx::PxU16 keyCode, physx::PxU8 ascii);
		
		virtual void updateInput();

		virtual void shutdown();

		virtual bool keyboardSupported() const { return true; }
		virtual bool gamepadSupported() const { return false; }
		virtual bool mouseSupported() const { return true; }

		virtual bool	getDigitalInputEventState(physx::PxU16 inputEventId) const;
		virtual float	getAnalogInputEventState(physx::PxU16 inputEventId) const;

	protected:

		void registerScanCode(LinuxSampleUserInputIds scanCodeId, physx::PxU16 scanCode, LinuxSampleUserInputIds nameId, const char* name);
		LinuxSampleUserInputIds getInputIdFromKeySym(const KeySym keySym) const;
		LinuxSampleUserInputIds getInputIdFromMouseButton(const physx::PxU16 button) const;
		const UserInput* getUserInputFromId(LinuxSampleUserInputIds id) const;		

		std::map<physx::PxU16, physx::PxU16>	m_ScanCodesMap;
		std::map<physx::PxU16,float>			m_AnalogStates;
		std::map<physx::PxU16,bool>				m_DigitalStates;
	};
}

#endif
