/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef ANDROID_SAMPLE_USER_INPUT_H
#define ANDROID_SAMPLE_USER_INPUT_H


#include <SampleUserInput.h>
#include <android/AndroidSampleUserInputIds.h>
#include <foundation/PxVec2.h>

/**
 * Shared state for our app.
 */
struct android_app;
class AInputEvent;

namespace SampleRenderer
{
	class Renderer;
}

namespace SampleFramework
{
	class AndroidSampleUserInput;
	class Touch;
	
	class ButtonController
	{
	public:
		ButtonController(AndroidSampleUserInput& parent);
		bool onTouchBegin(const physx::PxVec2& pos, Touch& touch);
		void onTouchEnd(const physx::PxVec2& pos, Touch& touch);
		bool onTouchMove(const physx::PxVec2& pos, Touch& touch);
	private:
		AndroidSampleUserInput& mSampleInput;
	};
	
	class GamePadController
	{
	public:
		GamePadController(AndroidSampleUserInput& parent);
		bool onTouchBegin(const physx::PxVec2& pos, Touch& touch);
		void onTouchEnd(const physx::PxVec2& pos, Touch& touch);
		bool onTouchMove(const physx::PxVec2& pos, Touch& touch);
	private:
		AndroidSampleUserInput& mSampleInput;
	};
	
	/* Touch information id and on screen element (stickIndex or buttonIndex)*/
	struct Touch
	{
		Touch() 					: id(0), stickIndex(-1), buttonIndex(-1), startPos(0.0f) {}
		Touch(physx::PxU32 _id) 	: id(_id), stickIndex(-1), buttonIndex(-1), startPos(0.0f) {}
		
		physx::PxU32 id;
		physx::PxI16 stickIndex;
		physx::PxI16 buttonIndex;
		physx::PxVec2 startPos;
	};

	class AndroidSampleUserInput: public SampleUserInput
	{
	public:
		AndroidSampleUserInput();
		~AndroidSampleUserInput();

		virtual void updateInput();
		virtual void shutdown();
		virtual void setRenderer(SampleRenderer::Renderer* renderer) { mRenderer = renderer; }
		SampleRenderer::Renderer* getRenderer()						 { return mRenderer; }

		virtual const InputEvent* registerInputEvent(const InputEvent& inputEvent, physx::PxU16 userInputId, const char* name);
		virtual const InputEvent* registerTouchInputEvent(const InputEvent& inputEvent, physx::PxU16 userInputId, const char* caption, const char* name);
		virtual void unregisterInputEvent(physx::PxU16 inputEventId);
		virtual void registerInputEvent(const SampleInputMapping& mapping);

		void onKeyDownEx(int32_t wParam);
		void onKeyDown(int32_t wParam, int32_t lParam);
		void onKeyUp(int32_t wParam, int32_t lParam);	
		void onUserInput(AndroidSampleUserInputIds uiId, bool pressed);
		void onGamepadAxis(physx::PxU32 axis, physx::PxReal val);
		
		void onTouchBegin(const physx::PxVec2& pos, physx::PxU32 id);
		void onTouchEnd(const physx::PxVec2& pos, physx::PxU32 id);
		void onTouchMove(const physx::PxVec2& pos, physx::PxU32 id);

		virtual InputType getInputType(const UserInput& ) const;

		virtual bool	getDigitalInputEventState(physx::PxU16 inputEventId ) const;
		virtual float	getAnalogInputEventState(physx::PxU16 inputEventId ) const;

		static int32_t engine_handle_input(struct android_app* app, AInputEvent* event);

		void	setHeight(physx::PxReal height);
		void	setWidth(physx::PxReal height);

	protected:
		static InputType getInputType(physx::PxU16 inputId);
			
		AndroidSampleUserInputIds GetKeyCode(int32_t keyparam) const;
		KeyCode GetSampleUserInputKeyCode(int32_t wParam) const;

		std::map<physx::PxU16, physx::PxU16>	mScanCodesMap;
		std::map<physx::PxU16,float>			mAnalogStates;
		std::map<physx::PxU16,bool>				mDigitalStates;

		SampleRenderer::Renderer*				mRenderer;
		
		std::map<physx::PxU32, Touch>			mTouches;
		
		ButtonController						mButtonController;
		GamePadController						mGamePadController;
	};
}

#endif
