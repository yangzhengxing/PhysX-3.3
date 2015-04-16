/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef OSX_SAMPLE_USER_INPUT_H
#define OSX_SAMPLE_USER_INPUT_H


#include <SampleUserInput.h>
#include <osx/OSXSampleUserInputIds.h>
#include <set>


namespace SampleFramework
{
	class OSXSampleUserInput: public SampleUserInput
	{
	public:

		OSXSampleUserInput();
		~OSXSampleUserInput();
		
		void doOnMouseMove( physx::PxU32 x, physx::PxU32 y, physx::PxReal dx, physx::PxReal dy, OSXSampleUserInputIds button);
		void doOnMouseDown( physx::PxU32 x, physx::PxU32 y, OSXSampleUserInputIds button);
		void doOnMouseUp( physx::PxU32 x, physx::PxU32 y, OSXSampleUserInputIds button);
		void doOnKeyDown( physx::PxU16 osxCode, physx::PxU8 ascii);
		void doOnKeyUp( physx::PxU16 osxCode, physx::PxU8 ascii);
		
		virtual void updateInput();

		virtual void shutdown();

		virtual bool keyboardSupported() const { return true; }
		virtual bool gamepadSupported() const { return false; }
		virtual bool mouseSupported() const { return true; }

		virtual bool	getDigitalInputEventState(physx::PxU16 inputEventId ) const;
		virtual float	getAnalogInputEventState(physx::PxU16 inputEventId ) const;

	protected:

		OSXSampleUserInputIds getInputId(const physx::PxU16 osxCode, const physx::PxU8 ascii) const;
		const UserInput* getUserInputFromId(OSXSampleUserInputIds id) const;		

		std::map<physx::PxU16, physx::PxU16>	m_ScanCodesMap;
		std::map<physx::PxU16,float>			m_AnalogStates;
		std::map<physx::PxU16,bool>				m_DigitalStates;
		std::set<physx::PxU16>					m_AnsiOsxCodeSet;

				
	};
}

#endif
