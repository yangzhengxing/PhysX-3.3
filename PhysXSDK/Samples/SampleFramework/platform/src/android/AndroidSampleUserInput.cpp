/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#include <android/AndroidSampleUserInput.h>
#include <android/keycodes.h>
#include <android/input.h>

#include <SampleApplication.h>
#include <RendererWindow.h>
#include <Renderer.h>
#include <SamplePlatform.h>
#include <android/AndroidSamplePlatform.h>

using namespace SampleFramework;

//this is relative to the smaller screen dimension
static const float	gControlMoveLimitRadius = 0.07f;
static PxReal 		g_siscreenWidth = 1.0f, g_siscreenHeight = 1.0f;


static PxVec3 PxVec2ToPxVec3(const PxVec2& v)
{
	return PxVec3(v.x, v.y, 0.0f);
}

static PxVec2 toAbsoluteCoords(const PxVec2& v)
{
	return PxVec2((v.x + 1.0f) * (g_siscreenWidth * 0.5f), -(v.y - 1.0f) * (g_siscreenHeight * 0.5f));
}

static PxVec2 toRelativeCoords(const PxVec2& v)
{
	return PxVec2(v.x / (g_siscreenWidth * 0.5f) - 1.0f,  -v.y / (g_siscreenHeight * 0.5f) + 1.0f);
}

static inline int32_t getMotionEventActionPointerIndex(int32_t action) {
	return (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
		>> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
}


AndroidSampleUserInput::AndroidSampleUserInput()
: mRenderer(NULL)
, mButtonController(*this)
, mGamePadController(*this)
{
	registerUserInput(AKEY_1,"KEY_1", "1");
	registerUserInput(AKEY_2,"KEY_2", "2");
	registerUserInput(AKEY_3,"KEY_3", "3");
	registerUserInput(AKEY_4,"KEY_4", "4");
	registerUserInput(AKEY_5,"KEY_5", "5");
	registerUserInput(AKEY_6,"KEY_6", "6");
	registerUserInput(AKEY_7,"KEY_7", "7");
	registerUserInput(AKEY_8,"KEY_8", "8");
	registerUserInput(AKEY_9,"KEY_9", "9");
	registerUserInput(AKEY_0,"KEY_0", "0");

	registerUserInput(AKEY_A,"KEY_A", "A");
	registerUserInput(AKEY_B,"KEY_B", "B");
	registerUserInput(AKEY_C,"KEY_C", "C");
	registerUserInput(AKEY_D,"KEY_D", "D");
	registerUserInput(AKEY_E,"KEY_E", "E");
	registerUserInput(AKEY_F,"KEY_F", "F");
	registerUserInput(AKEY_G,"KEY_G", "G");
	registerUserInput(AKEY_H,"KEY_H", "H");
	registerUserInput(AKEY_I,"KEY_I", "I");
	registerUserInput(AKEY_J,"KEY_J", "J");
	registerUserInput(AKEY_K,"KEY_K", "K");
	registerUserInput(AKEY_L,"KEY_L", "L");
	registerUserInput(AKEY_M,"KEY_M", "M");
	registerUserInput(AKEY_N,"KEY_N", "N");
	registerUserInput(AKEY_O,"KEY_O", "O");
	registerUserInput(AKEY_P,"KEY_P", "P");
	registerUserInput(AKEY_Q,"KEY_Q", "Q");
	registerUserInput(AKEY_R,"KEY_R", "R");
	registerUserInput(AKEY_S,"KEY_S", "S");
	registerUserInput(AKEY_T,"KEY_T", "T");
	registerUserInput(AKEY_U,"KEY_U", "U");
	registerUserInput(AKEY_V,"KEY_V", "V");
	registerUserInput(AKEY_W,"KEY_W", "W");
	registerUserInput(AKEY_X,"KEY_X", "X");
	registerUserInput(AKEY_Y,"KEY_Y", "Y");
	registerUserInput(AKEY_Z,"KEY_Z", "Z");

	registerUserInput(AKEY_SPACE  ,"KEY_SPACE","SPACE");
	registerUserInput(AKEY_RETURN ,"KEY_RETURN","ENTER");
	registerUserInput(AKEY_SHIFT ,"KEY_SHIFT","SHIFT");
	registerUserInput(AKEY_ESCAPE ,"KEY_ESCAPE","ESCAPE");
	registerUserInput(AKEY_COMMA ,"KEY_COMMA","comma");
	registerUserInput(AKEY_MULTIPLY ,"KEY_MULTIPLY","multiply");
	registerUserInput(AKEY_ADD ,"KEY_ADD","add");
	registerUserInput(AKEY_SEPARATOR ,"KEY_SEPARATOR","separator");
	registerUserInput(AKEY_SUBTRACT ,"KEY_SUBTRACT","subtract");
	registerUserInput(AKEY_DIVIDE ,"KEY_DIVIDE","divide");

	registerUserInput(AKEY_TAB ,"KEY_TAB","TAB");
	registerUserInput(AKEY_PRIOR ,"KEY_PRIOR","PRIOR");
	registerUserInput(AKEY_NEXT ,"KEY_NEXT","NEXT");
	registerUserInput(AKEY_UP ,"KEY_UP","UP");
	registerUserInput(AKEY_DOWN ,"KEY_DOWN","DOWN");
	registerUserInput(AKEY_LEFT ,"KEY_LEFT","LEFT");
	registerUserInput(AKEY_RIGHT ,"KEY_RIGHT","RIGHT");

	registerUserInput(GAMEPAD_RIGHT_STICK_X,"GAMEPAD_RIGHT_STICK_X", "gpad RSTICK");
	registerUserInput(GAMEPAD_RIGHT_STICK_Y,"GAMEPAD_RIGHT_STICK_Y", "gpad RSTICK");
	registerUserInput(GAMEPAD_LEFT_STICK_X,"GAMEPAD_LEFT_STICK_X", "gpad LSTICK");
	registerUserInput(GAMEPAD_LEFT_STICK_Y,"GAMEPAD_LEFT_STICK_Y", "gpad LSTICK");

	registerUserInput(ABUTTON_1,"BUTTON_1","BUTTON_1");
	registerUserInput(ABUTTON_2,"BUTTON_2","BUTTON_2");
	registerUserInput(ABUTTON_3,"BUTTON_3","BUTTON_3");
	registerUserInput(ABUTTON_4,"BUTTON_4","BUTTON_4");
	registerUserInput(ABUTTON_5,"BUTTON_5","BUTTON_5");
	registerUserInput(ABUTTON_6,"BUTTON_6","BUTTON_6");
	registerUserInput(ABUTTON_7,"BUTTON_7","BUTTON_7");
	registerUserInput(ABUTTON_8,"BUTTON_8","BUTTON_8");

	registerUserInput(AQUICK_BUTTON_1,"QUICK_BUTTON_1","QUICK_BUTTON_1");

	registerUserInput(ASELECTOR_BUTTON1,"SELECTOR_BUTTON_1","SELECTOR_BUTTON_1");
	registerUserInput(ASELECTOR_BUTTON2,"SELECTOR_BUTTON_2","SELECTOR_BUTTON_2");
	registerUserInput(AFREETAP,"FREETAP","FREETAP");
}

AndroidSampleUserInput::~AndroidSampleUserInput()
{
}

InputType AndroidSampleUserInput::getInputType(PxU16 inputId)
{
    if (inputId >= ABUTTON_1 && inputId < ALAST_BUTTON)
        return TOUCH_BUTTON_INPUT;

    if (inputId > AKEY_DEFINITION_START && inputId < AKEY_DEFINITION_END)
        return KEYBOARD_INPUT;

    if (inputId > GAMEPAD_DEFINITION_START && inputId < GAMEPAD_DEFINITION_END)
        return GAMEPAD_INPUT;

    return UNDEFINED_INPUT;
}

InputType AndroidSampleUserInput::getInputType(const UserInput& ui) const
{
    return getInputType(ui.m_Id);
}

const InputEvent* AndroidSampleUserInput::registerInputEvent(const InputEvent& inputEvent, PxU16 userInputId, const char* name)
{
    PX_ASSERT(getInputType(userInputId) != TOUCH_BUTTON_INPUT);
	return SampleUserInput::registerInputEvent(inputEvent, userInputId, name);
}

const InputEvent* AndroidSampleUserInput::registerTouchInputEvent(const InputEvent& inputEvent, PxU16 userInputId, const char* caption, const char* name)
{
    PX_ASSERT(getInputType(userInputId) == TOUCH_BUTTON_INPUT);
	const InputEvent* retVal = SampleUserInput::registerInputEvent(inputEvent, userInputId, name);
    mRenderer->bindButtonToUserInput(userInputId - ABUTTON_1, userInputId, caption);
	return retVal;
}

void AndroidSampleUserInput::unregisterInputEvent(PxU16 inputEventId)
{
	const std::vector<size_t>* userInputs = getUserInputs(inputEventId);

	if(userInputs)
	{
		for (size_t j = userInputs->size(); j--;)
		{
			const UserInput& ui = mUserInputs[(*userInputs)[j]];
			const std::vector<size_t>* events = getInputEvents(ui.m_Id);
			if(!events)
				continue;

			const InputEvent* newMap = NULL;
			const InputEventName* newName = NULL;

			if(events->size() > 1)
			{
				for (size_t i = events->size(); i--;)
				{
					const InputEvent& ie = mInputEvents[(*events)[i]];
					if(ie.m_Id != inputEventId)
					{
						newMap = &ie;
						newName = &mInputEventNames[(*events)[i]];
						break;
					}
				}

				if(newMap && newName)
				{
					if(ui.m_Id >= ABUTTON_1 && ui.m_Id < ALAST_BUTTON)
					{
						mRenderer->bindButtonToUserInput(ui.m_Id - ABUTTON_1, ui.m_Id, newName->m_Name);
					}
				}
				else
				{
					if(ui.m_Id >= ABUTTON_1 && ui.m_Id < ALAST_BUTTON)
					{
						mRenderer->bindButtonToUserInput(ui.m_Id - ABUTTON_1, AKEY_UNKNOWN, "Empty");
					}
				}
			}
			else
			{
				if(ui.m_Id >= ABUTTON_1 && ui.m_Id < ALAST_BUTTON)
				{
					mRenderer->bindButtonToUserInput(ui.m_Id - ABUTTON_1, AKEY_UNKNOWN, "Empty");
				}
			}
		}
	}

	SampleUserInput::unregisterInputEvent(inputEventId);
}

void AndroidSampleUserInput::registerInputEvent(const SampleInputMapping& mapping)
{
	SampleUserInput::registerInputEvent(mapping);

	if(mapping.m_UserInputId >= ABUTTON_1 && mapping.m_UserInputId < ALAST_BUTTON)
	{
		mRenderer->bindButtonToUserInput(mapping.m_UserInputId - ABUTTON_1,mapping.m_UserInputId, mInputEventNames[mapping.m_InputEventIndex].m_Name);
	}
}


void AndroidSampleUserInput::setHeight(PxReal height)
{
	g_siscreenHeight = height;
}

void AndroidSampleUserInput::setWidth(PxReal width)
{
	g_siscreenWidth = width;
}

AndroidSampleUserInputIds AndroidSampleUserInput::GetKeyCode(int32_t keyparam) const
{
	AndroidSampleUserInputIds keyCode = AKEY_UNKNOWN;
	//	LOGI("keyCode = %d", keyparam);

	if(keyparam >= AKEYCODE_A && keyparam <= AKEYCODE_Z)			keyCode = (AndroidSampleUserInputIds)((keyparam - AKEYCODE_A) + AKEY_A);
	else if(keyparam >= AKEYCODE_0 && keyparam <= AKEYCODE_9)	keyCode = (AndroidSampleUserInputIds)((keyparam - AKEYCODE_0)+AKEY_0);
	else if(keyparam == AKEYCODE_SHIFT_LEFT || keyparam == AKEYCODE_SHIFT_RIGHT)	keyCode = AKEY_SHIFT;
	else if(keyparam == AKEYCODE_SPACE)											keyCode = AKEY_SPACE;
	else if(keyparam == AKEYCODE_ENTER)											keyCode = AKEY_RETURN;
	else if(keyparam == AKEYCODE_COMMA)											keyCode = AKEY_COMMA;
	else if(keyparam == AKEYCODE_SLASH)											keyCode = AKEY_DIVIDE;
	else if(keyparam == AKEYCODE_MINUS)											keyCode = AKEY_SUBTRACT;
	else if(keyparam == AKEYCODE_PLUS)											keyCode = AKEY_ADD;
	else if(keyparam == AKEYCODE_PAGE_UP)										keyCode = AKEY_PRIOR;
	else if(keyparam == AKEYCODE_PAGE_DOWN)										keyCode = AKEY_NEXT;

	//
	else if(keyparam == AKEYCODE_TAB)											keyCode = AKEY_TAB;
	/* Escape */
	else if(keyparam ==     AKEYCODE_BACKSLASH)									keyCode = AKEY_ESCAPE;
	/* DPAD */
	else if(keyparam == AKEYCODE_DPAD_UP)										keyCode = AKEY_UP;
	else if(keyparam == AKEYCODE_DPAD_DOWN)										keyCode = AKEY_DOWN;
	else if(keyparam == AKEYCODE_DPAD_LEFT)										keyCode = AKEY_LEFT;
	else if(keyparam == AKEYCODE_DPAD_RIGHT)									keyCode = AKEY_RIGHT;


	return keyCode;
}

SampleUserInput::KeyCode AndroidSampleUserInput::GetSampleUserInputKeyCode(int32_t wParam) const
{
	SampleUserInput::KeyCode keyCode = KEY_UNKNOWN;
	const int keyparam = (int)wParam;
	if(keyparam >= AKEYCODE_A && keyparam <= AKEYCODE_Z)			keyCode = (SampleUserInput::KeyCode)((keyparam - AKEYCODE_A) + KEY_A);
	else if(keyparam >= AKEYCODE_0 && keyparam <= AKEYCODE_9)	keyCode = (SampleUserInput::KeyCode)((keyparam - AKEYCODE_0)+KEY_0);
	else if(keyparam == AKEYCODE_SHIFT_LEFT || keyparam == AKEYCODE_SHIFT_RIGHT)	keyCode = KEY_SHIFT;
	else if(keyparam == AKEYCODE_SPACE)											keyCode = KEY_SPACE;
	else if(keyparam == AKEYCODE_ENTER)											keyCode = KEY_RETURN;
	else if(keyparam == AKEYCODE_COMMA)											keyCode = KEY_COMMA;
	else if(keyparam == AKEYCODE_SLASH)											keyCode = KEY_DIVIDE;
	else if(keyparam == AKEYCODE_MINUS)											keyCode = KEY_SUBTRACT;
	else if(keyparam == AKEYCODE_PLUS)											keyCode = KEY_ADD;
	else if(keyparam == AKEYCODE_PAGE_UP)										keyCode = KEY_PRIOR;
	else if(keyparam == AKEYCODE_PAGE_DOWN)										keyCode = KEY_NEXT;

	//
	else if(keyparam == AKEYCODE_TAB)											keyCode = KEY_TAB;
	/* Escape */
	else if(keyparam ==     AKEYCODE_BACKSLASH)									keyCode = KEY_ESCAPE;
	/* DPAD */
	else if(keyparam == AKEYCODE_DPAD_UP)										keyCode = KEY_UP;
	else if(keyparam == AKEYCODE_DPAD_DOWN)										keyCode = KEY_DOWN;
	else if(keyparam == AKEYCODE_DPAD_LEFT)										keyCode = KEY_LEFT;
	else if(keyparam == AKEYCODE_DPAD_RIGHT)									keyCode = KEY_RIGHT;


	return keyCode;
}

void AndroidSampleUserInput::onKeyDownEx(int32_t wParam)
{
	if(getInputEventListener())
	{
		KeyCode keyCode = GetSampleUserInputKeyCode(wParam);

		getInputEventListener()->onKeyDownEx(keyCode, (PxU32)wParam);
	}
}

void AndroidSampleUserInput::onUserInput(AndroidSampleUserInputIds uiId, bool pressed)
{
	if(!uiId)
		return;

	const std::vector<size_t>* events = getInputEvents(uiId);

	if(!events || !getInputEventListener())
		return;

	for (size_t i = events->size(); i--;)
	{
		const InputEvent& ie = mInputEvents[(*events)[i]];
		if(mDigitalStates[ie.m_Id] != pressed)
		{
			mDigitalStates[ie.m_Id] = pressed;
			getInputEventListener()->onDigitalInputEvent(ie, pressed);
		}
	}
}


void AndroidSampleUserInput::onKeyDown(int32_t wParam, int32_t lParam)
{
	PxU16 scanCode = lParam;
	const std::vector<size_t>* events = NULL;
	std::map<PxU16, PxU16>::iterator fit = mScanCodesMap.find(scanCode);
	if(fit != mScanCodesMap.end())
	{
		events = getInputEvents(fit->second);
	}

	if(!events)
	{
		AndroidSampleUserInputIds keyCode = GetKeyCode(wParam);
		events = getInputEvents(keyCode);
	}

	if(!events || !getInputEventListener())
		return;

	for (size_t i = events->size(); i--;)
	{
		const InputEvent& ie = mInputEvents[(*events)[i]];
		mDigitalStates[ie.m_Id] = true;
		getInputEventListener()->onDigitalInputEvent(ie, true);
	}
}

void AndroidSampleUserInput::onKeyUp(int32_t wParam, int32_t lParam)
{
	PxU16 scanCode = lParam;
	const std::vector<size_t>* events = NULL;
	std::map<PxU16, PxU16>::iterator fit = mScanCodesMap.find(scanCode);
	if(fit != mScanCodesMap.end())
	{
		events = getInputEvents(fit->second);
	}
	if(!events)
	{
		AndroidSampleUserInputIds keyCode = GetKeyCode(wParam);
		events = getInputEvents(keyCode);
	}

	if(!events || !getInputEventListener())
		return;

	for (size_t i = events->size(); i--;)
	{
		const InputEvent& ie = mInputEvents[(*events)[i]];
		mDigitalStates[ie.m_Id] = false;
		getInputEventListener()->onDigitalInputEvent(ie, false);
	}
}


void AndroidSampleUserInput::onGamepadAxis(PxU32 axis, PxReal val)
{
	PxU16 userInput = GAMEPAD_RIGHT_STICK_X + axis;

	//LOGI("UserInput: %d, value: %f",userInput,val);
	const std::vector<size_t>* events = getInputEvents(userInput);

	if(!events || !getInputEventListener())
		return;

	for (size_t i = events->size(); i--;)
	{
		const InputEvent& ie = mInputEvents[(*events)[i]];
		mAnalogStates[ie.m_Id] = val*ie.m_Sensitivity;
		//LOGI("Axis: %s, value: %f",ie.m_Name,val);
		getInputEventListener()->onAnalogInputEvent(ie, val*ie.m_Sensitivity);
	}
}


/**
 * Process input events here.
 */
int32_t AndroidSampleUserInput::engine_handle_input(struct android_app* app, AInputEvent* event)
{
	AndroidSampleUserInput* sampleInput = static_cast<AndroidSampleUserInput*>(SamplePlatform::platform()->getSampleUserInput());

	 int32_t eventType = AInputEvent_getType(event);
	 /* Handle external keyboard (not on-screen one) */
     if (eventType == AINPUT_EVENT_TYPE_KEY)
	 {
			const int32_t action = AKeyEvent_getAction(event);
			if(action == AKEY_EVENT_ACTION_DOWN)
			{
				int32_t keyCode = AKeyEvent_getKeyCode(event);
				/* Send onKeyDown */
				sampleInput->onKeyDown(AKeyEvent_getKeyCode(event),AKeyEvent_getScanCode(event));
				sampleInput->onKeyDownEx(AKeyEvent_getKeyCode(event));
			}
			else if(action == AKEY_EVENT_ACTION_UP)
			{
				int32_t keyCode = AKeyEvent_getKeyCode(event);
				/* Send onKeyUp */
				sampleInput->onKeyUp(AKeyEvent_getKeyCode(event),AKeyEvent_getScanCode(event));
			}
	 }
     /* Handle touch screen events */
	 if (eventType == AINPUT_EVENT_TYPE_MOTION)
	 {
		const int32_t action = AMotionEvent_getAction(event);
		const int32_t maskedAction = action & AMOTION_EVENT_ACTION_MASK;
		/* All fingers up OR 2-nd or more finger up */
		if(maskedAction == AMOTION_EVENT_ACTION_UP || maskedAction == AMOTION_EVENT_ACTION_POINTER_UP || maskedAction == AMOTION_EVENT_ACTION_CANCEL)
		{
			int32_t idx = getMotionEventActionPointerIndex(action);
			int32_t id = AMotionEvent_getPointerId(event, idx);
			PxVec2 pos = PxVec2(AMotionEvent_getX(event, idx), AMotionEvent_getY(event, idx));
			sampleInput->onTouchEnd(pos, id);
		}
		/* 1-st finger down OR 2-nd or more finger down */
		else if(maskedAction == AMOTION_EVENT_ACTION_DOWN || maskedAction == AMOTION_EVENT_ACTION_POINTER_DOWN)
		{
			int32_t idx = getMotionEventActionPointerIndex(action);
			int32_t id = AMotionEvent_getPointerId(event, idx);
			PxVec2 pos = PxVec2(AMotionEvent_getX(event, idx), AMotionEvent_getY(event, idx));
			sampleInput->onTouchBegin(pos, id);
		}
		/* some finger moving */
		else if(maskedAction == AMOTION_EVENT_ACTION_MOVE)
		{
			int32_t touchCount = AMotionEvent_getPointerCount(event);
			for(int i = 0; i < touchCount; ++i)
			{
				int32_t id = AMotionEvent_getPointerId(event, i);
				PxVec2 pos = PxVec2(AMotionEvent_getX(event, i), AMotionEvent_getY(event, i));
				sampleInput->onTouchMove(pos, id);
			}
		}
        return 1;
     }
    return 0;
}

void AndroidSampleUserInput::onTouchBegin(const PxVec2& pos, PxU32 id)
{
	//this touch better not exist already
	PX_ASSERT(mTouches.find(id) == mTouches.end());

	Touch& touch = mTouches[id];
	touch = Touch(id);
		
	// process buttons
	if(mButtonController.onTouchBegin(pos, touch))
		return;
		
	// process gamepad
	if(mGamePadController.onTouchBegin(pos, touch))
		return;

	// didn't tap on button or gamepad, so it should be just freetap
	const std::vector<size_t>* events = getInputEvents(AFREETAP);
	if(events)
	{
		for (size_t i = events->size(); i--;)
		{
			InputEvent& ie = mInputEvents[(*events)[i]];
			mDigitalStates[ie.m_Id] = true;

			if(getInputEventListener())
			{		
				getInputEventListener()->onPointerInputEvent(ie, (PxU32)pos.x, (PxU32)(g_siscreenHeight - pos.y), (PxReal)0.0f, (PxReal)0.0f, true);
			}
		}
	}
}

void AndroidSampleUserInput::onTouchEnd(const PxVec2& pos, PxU32 id)
{
	std::map<PxU32, Touch>::iterator tIt = mTouches.find(id);
	PX_ASSERT(tIt != mTouches.end());
	Touch& touch = tIt->second;
	
	if (touch.buttonIndex != -1)
	{
		//release button
		PX_ASSERT(touch.stickIndex == -1);
		mButtonController.onTouchEnd(pos, touch);
	}
	else if (touch.stickIndex != -1)
	{
		//release stick
		mGamePadController.onTouchEnd(pos, touch);
	}

	mTouches.erase(id);
}

void AndroidSampleUserInput::onTouchMove(const PxVec2& pos, PxU32 id)
{
	std::map<PxU32, Touch>::iterator tIt = mTouches.find(id);
	PX_ASSERT(tIt != mTouches.end());
	Touch& touch = tIt->second;
		
	// process buttons
	if(mButtonController.onTouchMove(pos, touch))
		return;
		
	// process gamepad
	if(mGamePadController.onTouchMove(pos, touch))
		return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ButtonController::ButtonController(AndroidSampleUserInput& parent)
: mSampleInput(parent)
{
}

bool ButtonController::onTouchBegin(const PxVec2& pos, Touch& touch)
{
	PxVec2 touchPosView = toRelativeCoords(pos);
	
	std::vector<SampleRenderer::Renderer::TabletButton>& buttons = mSampleInput.getRenderer()->screenButtons();
	for (PxI16 i = 0; i < buttons.size(); ++i)
	{
		SampleRenderer::Renderer::TabletButton& button = buttons[i];
		PxBounds3 buttonBounds(PxVec3(button.leftBottom.x, button.rightTop.y, -1.0f),
							   PxVec3(button.rightTop.x, button.leftBottom.y, 1.0f));

		if (buttonBounds.contains(PxVec3(touchPosView.x, touchPosView.y, 0.0f)))
		{
			button.incPressed();
			if(button.pressedCount == 1)
			{
				mSampleInput.onUserInput(AndroidSampleUserInputIds(button.emulatedKeyCode), true);
				if(button.callback)
				{
					button.callback();
				}
			}
			touch.buttonIndex = i;
			return true;
		}
	}
	touch.buttonIndex = -1;
	return false;
}

void ButtonController::onTouchEnd(const PxVec2& pos, Touch& touch)
{
	//release button
	SampleRenderer::Renderer::TabletButton& button = mSampleInput.getRenderer()->screenButtons()[touch.buttonIndex];
	button.decPressed();
	if(button.pressedCount == 0)
		mSampleInput.onUserInput(AndroidSampleUserInputIds(button.emulatedKeyCode), false);
	touch.buttonIndex = -1;
}

bool ButtonController::onTouchMove(const PxVec2& pos, Touch& touch)
{
	// check if we entered a button with move
	if(touch.buttonIndex != -1)
	{
		//stop touching button, when leaving its area
		SampleRenderer::Renderer::TabletButton& button = mSampleInput.getRenderer()->screenButtons()[touch.buttonIndex];
		PxVec2 touchPosView = toRelativeCoords(pos);

		PxBounds3 buttonBounds(PxVec3(button.leftBottom.x, button.rightTop.y, -1.0f),
							   PxVec3(button.rightTop.x, button.leftBottom.y, 1.0f));

		if (!buttonBounds.contains(PxVec3(touchPosView.x, touchPosView.y, 0.0f)))
		{
			touch.buttonIndex != -1;
			button.decPressed();
			if(button.pressedCount == 0)
				mSampleInput.onUserInput(AndroidSampleUserInputIds(button.emulatedKeyCode), false);
			return onTouchBegin(pos, touch); // check if we entered another button instead
		}
		else
			return true;

	}
	// check if we entered a button with move
	else
		return onTouchBegin(pos, touch);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GamePadController::GamePadController(AndroidSampleUserInput& parent)
: mSampleInput(parent)
{
}

bool GamePadController::onTouchBegin(const PxVec2& pos, Touch& touch)
{
	PxVec2 touchPosView = toRelativeCoords(pos);
	//grab onscreen pad controls
	for (PxI16 i = 0; i < 2; ++i)
	{
		if (mSampleInput.getRenderer()->getCenteredControlBounds(i).contains(PxVec3(touchPosView.x, touchPosView.y, 0.0f)))
		{
			//remember element and no further touching possible
			touch.stickIndex = i;
			touch.startPos = pos;
			return true;
		}
	}
	touch.stickIndex = -1;
	return false;
}

void GamePadController::onTouchEnd(const PxVec2& pos, Touch& touch)
{	
	mSampleInput.getRenderer()->setControlDefaultPosition(touch.stickIndex);
	mSampleInput.onGamepadAxis(2 - 2*touch.stickIndex, 0.0f);
	mSampleInput.onGamepadAxis(2 - 2*touch.stickIndex + 1, 0.0f);
	touch.stickIndex = -1;
}

bool GamePadController::onTouchMove(const PxVec2& pos, Touch& touch)
{
	if(touch.stickIndex == -1)
		return onTouchBegin(pos, touch);
	
	float limitInScreen = gControlMoveLimitRadius * ((g_siscreenWidth > g_siscreenHeight) ? g_siscreenHeight : g_siscreenWidth);
	PxVec2 centeredPosScreen = toAbsoluteCoords(mSampleInput.getRenderer()->getCenteredControlPosition(touch.stickIndex));
	PxVec2 diffScreen = pos - touch.startPos;
	PxReal diffLen = diffScreen.magnitude();
	if(diffLen > limitInScreen)
	{
		diffScreen *= limitInScreen/diffLen;
	}

	mSampleInput.getRenderer()->setControlPosition(touch.stickIndex, toRelativeCoords(centeredPosScreen + diffScreen));
	PxVec2 gamepadVec = diffScreen*(1.0f/limitInScreen);
	gamepadVec.y = -gamepadVec.y;

	mSampleInput.onGamepadAxis(2 - 2 * touch.stickIndex, gamepadVec.x);
	mSampleInput.onGamepadAxis(2 - 2 * touch.stickIndex + 1, gamepadVec.y);
	
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AndroidSampleUserInput::updateInput()
{
}

void AndroidSampleUserInput::shutdown()
{
	mAnalogStates.clear();
	mDigitalStates.clear();

	SampleUserInput::shutdown();
}

bool AndroidSampleUserInput::getDigitalInputEventState(PxU16 inputEventId ) const
{
	return false;
}

float AndroidSampleUserInput::getAnalogInputEventState(PxU16 inputEventId ) const
{
	return 0.0f;
}


