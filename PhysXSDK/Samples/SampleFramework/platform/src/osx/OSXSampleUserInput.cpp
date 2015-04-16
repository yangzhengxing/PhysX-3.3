/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#include <osx/OSXSampleUserInput.h>
#include <Carbon/Carbon.h>
#include <stdio.h>

using namespace SampleFramework;
using namespace physx;

OSXSampleUserInput::OSXSampleUserInput()
{	
	// register all user inputs for windows platform
	registerUserInput(OSXKEY_1,"KEY_1", "1");
	registerUserInput(OSXKEY_2,"KEY_2", "2");	
	registerUserInput(OSXKEY_3,"KEY_3", "3");	
	registerUserInput(OSXKEY_4,"KEY_4", "4");	
	registerUserInput(OSXKEY_5,"KEY_5", "5");	
	registerUserInput(OSXKEY_6,"KEY_6", "6");	
	registerUserInput(OSXKEY_7,"KEY_7", "7");	
	registerUserInput(OSXKEY_8,"KEY_8", "8");	
	registerUserInput(OSXKEY_9,"KEY_9", "9");	
	registerUserInput(OSXKEY_0,"KEY_0", "0");	

	registerUserInput(OSXKEY_A,"KEY_A", "A");	
	registerUserInput(OSXKEY_B,"KEY_B", "B");	
	registerUserInput(OSXKEY_C,"KEY_C", "C");	
	registerUserInput(OSXKEY_D,"KEY_D", "D");	
	registerUserInput(OSXKEY_E,"KEY_E", "E");	
	registerUserInput(OSXKEY_F,"KEY_F", "F");	
	registerUserInput(OSXKEY_G,"KEY_G", "G");	
	registerUserInput(OSXKEY_H,"KEY_H", "H");	
	registerUserInput(OSXKEY_I,"KEY_I", "I");	
	registerUserInput(OSXKEY_J,"KEY_J", "J");	
	registerUserInput(OSXKEY_K,"KEY_K", "K");	
	registerUserInput(OSXKEY_L,"KEY_L", "L");	
	registerUserInput(OSXKEY_M,"KEY_M", "M");	
	registerUserInput(OSXKEY_N,"KEY_N", "N");	
	registerUserInput(OSXKEY_O,"KEY_O", "O");	
	registerUserInput(OSXKEY_P,"KEY_P", "P");	
	registerUserInput(OSXKEY_Q,"KEY_Q", "Q");	
	registerUserInput(OSXKEY_R,"KEY_R", "R");	
	registerUserInput(OSXKEY_S,"KEY_S", "S");	
	registerUserInput(OSXKEY_T,"KEY_T", "T");	
	registerUserInput(OSXKEY_U,"KEY_U", "U");	
	registerUserInput(OSXKEY_V,"KEY_V", "V");	
	registerUserInput(OSXKEY_W,"KEY_W", "W");	
	registerUserInput(OSXKEY_X,"KEY_X", "X");	
	registerUserInput(OSXKEY_Y,"KEY_Y", "Y");	
	registerUserInput(OSXKEY_Z,"KEY_Z", "Z");	
	
	registerUserInput(OSXKEY_EQUAL,			"KEY_EQUAL",			"=");	
	registerUserInput(OSXKEY_SUBTRACT,		"KEY_SUBTRACT",			"-");	
	registerUserInput(OSXKEY_RIGHT_BRACKET,	"KEY_RIGHT_BRACKET",	"]");
	registerUserInput(OSXKEY_LEFT_BRACKET,	"KEY_LEFT_BRACKET",		"[");
	registerUserInput(OSXKEY_QUOTE,			"KEY_QUOTE",			"'");
	registerUserInput(OSXKEY_SEMICOLON,		"KEY_SEMICOLON",		";");
	registerUserInput(OSXKEY_BACKSLASH,		"KEY_BACKSLASH",		"\\");
	registerUserInput(OSXKEY_COMMA,			"KEY_COMMA",			",");
	registerUserInput(OSXKEY_SLASH,			"KEY_SLASH",			"/");
	registerUserInput(OSXKEY_DECIMAL,		"KEY_DECIMAL",			".");
	registerUserInput(OSXKEY_GRAVE,			"KEY_GRAVE",			"`");
	registerUserInput(OSXKEY_MULTIPLY,		"KEY_MULTIPLY",			"*");
	registerUserInput(OSXKEY_ADD,			"KEY_ADD",				"+");

	registerUserInput(OSXKEY_RETURN,		"KEY_RETURN",			"RETURN");
	registerUserInput(OSXKEY_TAB,			"KEY_TAB",				"TAB");
	registerUserInput(OSXKEY_SPACE,			"KEY_SPACE",			"SPACE");
    registerUserInput(OSXKEY_BACKSPACE,		"KEY_BACKSPACE",		"BACKSPACE");
	registerUserInput(OSXKEY_DELETE,		"KEY_DELETE",			"DELETE");
	registerUserInput(OSXKEY_ESCAPE,		"KEY_ESCAPE",			"ESC");
	registerUserInput(OSXKEY_COMMAND,		"KEY_COMMAND",			"COMMAND");
	registerUserInput(OSXKEY_SHIFT,			"KEY_SHIFT",			"SHIFT");
	registerUserInput(OSXKEY_CAPSLOCK,		"KEY_CAPSLOCK",			"CAPSLOCK");		
	registerUserInput(OSXKEY_OPTION,		"KEY_OPTION",			"OPTION");		
	registerUserInput(OSXKEY_CONTROL,		"KEY_CONTROL",			"CONTROL");		
	registerUserInput(OSXKEY_RIGHTSHIFT,	"KEY_RIGHTSHIFT",		"RIGHT SHIFT");
	registerUserInput(OSXKEY_RIGHTOPTION,	"KEY_RIGHTOPTION",		"RIGHT OPTION");	
	registerUserInput(OSXKEY_RIGHTCONTROL,	"KEY_RIGHTCONTROL",		"RIGHT CONTROL");	
	registerUserInput(OSXKEY_FUNCTION,		"KEY_FUNCTION",			"FUNCTION");		
	registerUserInput(OSXKEY_F17,			"KEY_F17",				"F17");			
	registerUserInput(OSXKEY_VOLUMEUP,		"KEY_VOLUMEUP",			"VOLUME UP");		
	registerUserInput(OSXKEY_VOLUMEDOWN,	"KEY_VOLUMEDOWN",		"VOLUME DOWN");	
	registerUserInput(OSXKEY_MUTE,			"KEY_MUTE",				"MUTE");		
	registerUserInput(OSXKEY_F18,			"KEY_F18",				"F18");
	registerUserInput(OSXKEY_F19,			"KEY_F19",				"F19");
	registerUserInput(OSXKEY_F20,			"KEY_F20",				"F20");
	registerUserInput(OSXKEY_F5,			"KEY_F5",				"F5");			
	registerUserInput(OSXKEY_F6,			"KEY_F6",				"F6");			
	registerUserInput(OSXKEY_F7,			"KEY_F7",				"F7");			
	registerUserInput(OSXKEY_F3,			"KEY_F3",				"F3");			
	registerUserInput(OSXKEY_F8,			"KEY_F8",				"F8");			
	registerUserInput(OSXKEY_F9,			"KEY_F9",				"F9");			
	registerUserInput(OSXKEY_F11,			"KEY_F11",				"F11");			
	registerUserInput(OSXKEY_F13,			"KEY_F13",				"F13");			
	registerUserInput(OSXKEY_F16,			"KEY_F16",				"F16");			
	registerUserInput(OSXKEY_F14,			"KEY_F14",				"F14");			
	registerUserInput(OSXKEY_F10,			"KEY_F10",				"F10");			
	registerUserInput(OSXKEY_F12,			"KEY_F12",				"F12");			
	registerUserInput(OSXKEY_F15,			"KEY_F15",				"F15");			
	registerUserInput(OSXKEY_HELP,			"KEY_HELP",				"HELP");			
	registerUserInput(OSXKEY_HOME,			"KEY_HOME",				"HOME");		
	registerUserInput(OSXKEY_PRIOR,			"KEY_PRIOR",			"PRIOR");		
	registerUserInput(OSXKEY_F4,			"KEY_F4",				"F4");
	registerUserInput(OSXKEY_END,			"KEY_END",				"END");			
	registerUserInput(OSXKEY_F2,			"KEY_F2",				"F2");		
	registerUserInput(OSXKEY_NEXT,			"KEY_NEXT",				"NEXT");		
	registerUserInput(OSXKEY_F1,			"KEY_F1",				"F1");	
	registerUserInput(OSXKEY_LEFT,			"KEY_LEFT",				"LEFT ARROW");	
	registerUserInput(OSXKEY_RIGHT,			"KEY_RIGHT",			"RIGHT ARROW");	
	registerUserInput(OSXKEY_DOWN,			"KEY_DOWN",				"DOWN ARROW");	
	registerUserInput(OSXKEY_UP,			"KEY_UP",				"UP ARROW");
	registerUserInput(OSXKEY_NUMPAD0,		"KEY_NUMPAD0",			"NUMPAD 0");
	registerUserInput(OSXKEY_NUMPAD1,		"KEY_NUMPAD1",			"NUMPAD 1");
	registerUserInput(OSXKEY_NUMPAD2,		"KEY_NUMPAD2",			"NUMPAD 2");
	registerUserInput(OSXKEY_NUMPAD3,		"KEY_NUMPAD3",			"NUMPAD 3");
	registerUserInput(OSXKEY_NUMPAD4,		"KEY_NUMPAD4",			"NUMPAD 4");
	registerUserInput(OSXKEY_NUMPAD5,		"KEY_NUMPAD5",			"NUMPAD 5");
	registerUserInput(OSXKEY_NUMPAD6,		"KEY_NUMPAD6",			"NUMPAD 6");
	registerUserInput(OSXKEY_NUMPAD7,		"KEY_NUMPAD7",			"NUMPAD 7");
	registerUserInput(OSXKEY_NUMPAD8,		"KEY_NUMPAD8",			"NUMPAD 8");
	registerUserInput(OSXKEY_NUMPAD9,		"KEY_NUMPAD9",			"NUMPAD 9");
					  
	// mouse
	registerUserInput(MOUSE_BUTTON_LEFT ,"MOUSE_BUTTON_LEFT","left mouse button");
	registerUserInput(MOUSE_BUTTON_RIGHT ,"MOUSE_BUTTON_RIGHT","right mouse button");
	registerUserInput(MOUSE_BUTTON_CENTER ,"MOUSE_BUTTON_CENTER","middle mouse button");
	registerUserInput(MOUSE_MOVE,"MOUSE_MOVE", "mouse move");	

	//prepare ansi set (layout dependent codes)	HIToolbox.framework, Events.h
	//not adding numpad keys here to distinguish them from number keys 
	m_AnsiOsxCodeSet.insert(kVK_ANSI_A);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_S);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_D);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_F);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_H);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_G);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_Z);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_X);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_C);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_V);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_B);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_Q);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_W);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_E);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_R);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_Y);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_T);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_1);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_2);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_3);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_4);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_6);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_5);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_Equal);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_9);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_7);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_Minus);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_8);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_0);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_RightBracket);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_O);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_U);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_LeftBracket);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_I);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_P);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_L);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_J);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_Quote);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_K);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_Semicolon);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_Backslash);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_Comma);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_Slash);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_N);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_M);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_Period);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_Grave);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_KeypadDecimal);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_KeypadMultiply);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_KeypadPlus);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_KeypadClear);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_KeypadDivide);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_KeypadEnter);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_KeypadMinus);
	m_AnsiOsxCodeSet.insert(kVK_ANSI_KeypadEquals);

	// use scan codes for movement
	const UserInput* ui = getUserInputFromId(OSXKEY_E);
	if(ui)
	{
		registerUserInput(SCAN_CODE_UP,"SCAN_CODE_E", ui->m_Name);
		m_ScanCodesMap[kVK_ANSI_E] = SCAN_CODE_UP;
	}

	ui = getUserInputFromId(OSXKEY_C);
	if(ui)
	{
		registerUserInput(SCAN_CODE_DOWN,"SCAN_CODE_C", ui->m_Name);
		m_ScanCodesMap[kVK_ANSI_C] = SCAN_CODE_DOWN;
	}

	ui = getUserInputFromId(OSXKEY_A);
	if(ui)
	{
		registerUserInput(SCAN_CODE_LEFT,"SCAN_CODE_A", ui->m_Name);
		m_ScanCodesMap[kVK_ANSI_A] = SCAN_CODE_LEFT;
	}

	ui = getUserInputFromId(OSXKEY_D);
	if(ui)
	{
		registerUserInput(SCAN_CODE_RIGHT,"SCAN_CODE_D", ui->m_Name);
		m_ScanCodesMap[kVK_ANSI_D] = SCAN_CODE_RIGHT;
	}
	
	ui = getUserInputFromId(OSXKEY_W);
	if(ui)
	{
		registerUserInput(SCAN_CODE_FORWARD,"SCAN_CODE_W", ui->m_Name);
		m_ScanCodesMap[kVK_ANSI_W] = SCAN_CODE_FORWARD;
	}

	ui = getUserInputFromId(OSXKEY_S);
	if(ui)
	{
		registerUserInput(SCAN_CODE_BACKWARD,"SCAN_CODE_S", ui->m_Name);
		m_ScanCodesMap[kVK_ANSI_S] = SCAN_CODE_BACKWARD;
	}

	ui = getUserInputFromId(OSXKEY_L);
	if(ui)
	{
		registerUserInput(SCAN_CODE_L,"SCAN_CODE_L", ui->m_Name);
		m_ScanCodesMap[kVK_ANSI_L] = SCAN_CODE_L;
	}

	ui = getUserInputFromId(OSXKEY_9);
	if(ui)
	{
		registerUserInput(SCAN_CODE_9,"SCAN_CODE_9", ui->m_Name);
		m_ScanCodesMap[kVK_ANSI_9] = SCAN_CODE_9;
	}

	ui = getUserInputFromId(OSXKEY_0);
	if(ui)
	{
		registerUserInput(SCAN_CODE_0,"SCAN_CODE_0", ui->m_Name);
		m_ScanCodesMap[kVK_ANSI_0] = SCAN_CODE_0;
	}

}

const UserInput* OSXSampleUserInput::getUserInputFromId(OSXSampleUserInputIds id) const
{
	for (size_t i = mUserInputs.size(); i--;)
	{
		if(mUserInputs[i].m_Id == id)
		{
			return &mUserInputs[i];
		}
	}

	return NULL;
}

OSXSampleUserInput::~OSXSampleUserInput()
{
	m_ScanCodesMap.clear();
	m_AnalogStates.clear();
	m_DigitalStates.clear();

}

OSXSampleUserInputIds OSXSampleUserInput::getInputId(const PxU16 osxCode, const PxU8 asciiKey) const
{
	OSXSampleUserInputIds id = OSXKEY_UNKNOWN;
	
	if (m_AnsiOsxCodeSet.find(osxCode) != m_AnsiOsxCodeSet.end())
	{
		if (asciiKey >= 'A' && asciiKey <= 'Z')			id = (OSXSampleUserInputIds)((asciiKey - 'A')+OSXKEY_A);
		else if (asciiKey >= 'a' && asciiKey <= 'z')	id = (OSXSampleUserInputIds)((asciiKey - 'a')+OSXKEY_A);
		else if (asciiKey >= '0' && asciiKey <= '9')	id= (OSXSampleUserInputIds)((asciiKey - '0')+OSXKEY_0);
		else if (asciiKey == '=')						id = OSXKEY_EQUAL;
		else if (asciiKey == '-')						id = OSXKEY_SUBTRACT;
		else if (asciiKey == '[')						id = OSXKEY_RIGHT_BRACKET;
		else if (asciiKey == ']')						id = OSXKEY_LEFT_BRACKET;
		else if (asciiKey == '\'')						id = OSXKEY_QUOTE;
		else if (asciiKey == ';')						id = OSXKEY_SEMICOLON;
		else if (asciiKey == '\\')						id = OSXKEY_BACKSLASH;
		else if (asciiKey == ',')						id = OSXKEY_COMMA;	
		else if (asciiKey == '/')						id = OSXKEY_SLASH;
		else if (asciiKey == '.')						id = OSXKEY_DECIMAL;
		else if (asciiKey == '`')						id = OSXKEY_GRAVE;
		else if (asciiKey == '*')						id = OSXKEY_MULTIPLY;
		else if (asciiKey == '+')						id = OSXKEY_ADD;
	}
	else 
	{
		if (osxCode == kVK_Return)						id = OSXKEY_RETURN;
		else if (osxCode == kVK_Tab)					id = OSXKEY_TAB;        
       	else if (osxCode == kVK_Delete)                 id = OSXKEY_BACKSPACE;
		else if (osxCode == kVK_Space)					id = OSXKEY_SPACE;
		else if (osxCode == kVK_Escape)					id = OSXKEY_ESCAPE;
		else if (osxCode == kVK_Command)				id = OSXKEY_COMMAND;
		else if (osxCode == kVK_Shift)					id = OSXKEY_SHIFT;
		else if (osxCode == kVK_CapsLock)				id = OSXKEY_CAPSLOCK;
		else if (osxCode == kVK_Option)					id = OSXKEY_OPTION;
		else if (osxCode == kVK_Control)				id = OSXKEY_CONTROL;
		else if (osxCode == kVK_RightShift)				id = OSXKEY_RIGHTSHIFT;
		else if (osxCode == kVK_RightOption)			id = OSXKEY_RIGHTOPTION;
		else if (osxCode == kVK_RightControl)			id = OSXKEY_RIGHTCONTROL;
		else if (osxCode == kVK_Function)				id = OSXKEY_FUNCTION;
		else if (osxCode == kVK_F17)					id = OSXKEY_F17;
		else if (osxCode == kVK_VolumeUp)				id = OSXKEY_VOLUMEUP;
		else if (osxCode == kVK_VolumeDown)				id = OSXKEY_VOLUMEDOWN;
		else if (osxCode == kVK_Mute)					id = OSXKEY_MUTE;
		else if (osxCode == kVK_F18)					id = OSXKEY_F18;
		else if (osxCode == kVK_F19)					id = OSXKEY_F19;
		else if (osxCode == kVK_F20)					id = OSXKEY_F20;
		else if (osxCode == kVK_F5)						id = OSXKEY_F5;
		else if (osxCode == kVK_F6)						id = OSXKEY_F6;
		else if (osxCode == kVK_F7)						id = OSXKEY_F7;
		else if (osxCode == kVK_F3)						id = OSXKEY_F3;
		else if (osxCode == kVK_F8)						id = OSXKEY_F8;
		else if (osxCode == kVK_F9)						id = OSXKEY_F9;
		else if (osxCode == kVK_F11)					id = OSXKEY_F11;
		else if (osxCode == kVK_F13)					id = OSXKEY_F13;
		else if (osxCode == kVK_F16)					id = OSXKEY_F16;
		else if (osxCode == kVK_F14)					id = OSXKEY_F14;
		else if (osxCode == kVK_F10)					id = OSXKEY_F10;
		else if (osxCode == kVK_F12)					id = OSXKEY_F12;
		else if (osxCode == kVK_F15)					id = OSXKEY_F15;
		else if (osxCode == kVK_Help)					id = OSXKEY_HELP;
		else if (osxCode == kVK_Home)					id = OSXKEY_HOME;
		else if (osxCode == kVK_PageUp)					id = OSXKEY_PRIOR;
		else if (osxCode == kVK_ForwardDelete)			id = OSXKEY_DELETE;
		else if (osxCode == kVK_F4)						id = OSXKEY_F4;
		else if (osxCode == kVK_End)					id = OSXKEY_END;
		else if (osxCode == kVK_F2)						id = OSXKEY_F2;
		else if (osxCode == kVK_PageDown)				id = OSXKEY_NEXT;
		else if (osxCode == kVK_F1)						id = OSXKEY_F1;
		else if (osxCode == kVK_LeftArrow)				id = OSXKEY_LEFT;
		else if (osxCode == kVK_RightArrow)				id = OSXKEY_RIGHT;
		else if (osxCode == kVK_DownArrow)				id = OSXKEY_DOWN;
		else if (osxCode == kVK_UpArrow)				id = OSXKEY_UP;
		else if (osxCode == kVK_ANSI_Keypad0)			id = OSXKEY_NUMPAD0;
		else if (osxCode == kVK_ANSI_Keypad1)			id = OSXKEY_NUMPAD1;
		else if (osxCode == kVK_ANSI_Keypad2)			id = OSXKEY_NUMPAD2;
		else if (osxCode == kVK_ANSI_Keypad3)			id = OSXKEY_NUMPAD3;
		else if (osxCode == kVK_ANSI_Keypad4)			id = OSXKEY_NUMPAD4;
		else if (osxCode == kVK_ANSI_Keypad5)			id = OSXKEY_NUMPAD5;
		else if (osxCode == kVK_ANSI_Keypad6)			id = OSXKEY_NUMPAD6;
		else if (osxCode == kVK_ANSI_Keypad7)			id = OSXKEY_NUMPAD7;
		else if (osxCode == kVK_ANSI_Keypad8)			id = OSXKEY_NUMPAD8;
		else if (osxCode == kVK_ANSI_Keypad9)			id = OSXKEY_NUMPAD9;
	}
	
	return id;
}

void OSXSampleUserInput::doOnMouseMove(physx::PxU32 x, physx::PxU32 y, physx::PxReal dx, physx::PxReal dy, OSXSampleUserInputIds button)
{	
	const std::vector<size_t>* events = getInputEvents(button);

	if(events)
	{
		for (size_t i = events->size(); i--;)
		{
			const InputEvent& ie = mInputEvents[(*events)[i]];
			if(getInputEventListener())
			{		
				getInputEventListener()->onPointerInputEvent(ie, x, y, dx, dy, false);
			}
		}
	}

}


void OSXSampleUserInput::doOnMouseDown(physx::PxU32 x, physx::PxU32 y , OSXSampleUserInputIds button)
{	
	const std::vector<size_t>* events = getInputEvents(button);

	if(events)
	{
		for (size_t i = events->size(); i--;)
		{
			const InputEvent& ie = mInputEvents[(*events)[i]];
			m_DigitalStates[ie.m_Id] = true;

			if(getInputEventListener())
			{		
				getInputEventListener()->onPointerInputEvent(ie, x, y, 0, 0, true);
			}
		}
	}

}

void OSXSampleUserInput::doOnMouseUp(physx::PxU32 x, physx::PxU32 y, OSXSampleUserInputIds button)
{
	const std::vector<size_t>* events = getInputEvents(button);
	if(events)
	{
		for (size_t i = events->size(); i--;)
		{
			const InputEvent& ie = mInputEvents[(*events)[i]];
			m_DigitalStates[ie.m_Id] = false;

			if(getInputEventListener())
			{		
				getInputEventListener()->onPointerInputEvent(ie, x, y, 0, 0, false);
			}
		}
	}

}

void OSXSampleUserInput::doOnKeyDown( PxU16 osxCode, PxU8 ascii)
{
	const std::vector<size_t>* events = NULL;
	
    
    if(getInputEventListener())
    {
        //raw ASCII printable characters get sent to the console
        if (ascii >= 'a' && ascii <= 'z')
        {
            getInputEventListener()->onKeyDownEx(static_cast<KeyCode>(ascii - 'a' + KEY_A), ascii);
        }
        else if (ascii >= 'A' && ascii <= 'Z')
        {
            getInputEventListener()->onKeyDownEx(static_cast<KeyCode>(ascii - 'A' + KEY_A), ascii);
        }
        else if (ascii >= '0' && ascii <= '9')
        {
            getInputEventListener()->onKeyDownEx(static_cast<KeyCode>(ascii - 'A' + KEY_A), ascii);
        }
        else if (ascii == ' ')
        {
            getInputEventListener()->onKeyDownEx(static_cast<KeyCode>(ascii - ' ' + KEY_SPACE), ascii);
        }
        else if (ascii == '.')
        {
            getInputEventListener()->onKeyDownEx(static_cast<KeyCode>(ascii - '.' + KEY_DECIMAL), ascii);
        }
                
        std::map<physx::PxU16, physx::PxU16>::iterator fit = m_ScanCodesMap.find(osxCode);
        if(fit != m_ScanCodesMap.end())
        {
            events = getInputEvents(fit->second);
        }
	
        if(!events)
        {
            OSXSampleUserInputIds keyCode = getInputId(osxCode, ascii);
            events = getInputEvents(keyCode);
        }
	
        if(!events || !getInputEventListener())
            return;
	
        for (size_t i = events->size(); i--;)
        {
            const InputEvent& ie = mInputEvents[(*events)[i]];
            m_DigitalStates[ie.m_Id] = true;
			getInputEventListener()->onDigitalInputEvent(ie, true);
        }	
    }
}

void OSXSampleUserInput::doOnKeyUp(PxU16 osxCode, PxU8 ascii)
{
	const std::vector<size_t>* events = NULL;
	std::map<physx::PxU16, physx::PxU16>::iterator fit = m_ScanCodesMap.find(osxCode);
	if(fit != m_ScanCodesMap.end())
	{
		events = getInputEvents(fit->second);
	}
	if(!events)
	{
		OSXSampleUserInputIds keyCode = getInputId(osxCode, ascii);
		events = getInputEvents(keyCode);
	}

	if(!events || !getInputEventListener())
		return;

	for (size_t i = events->size(); i--;)
	{
		const InputEvent& ie = mInputEvents[(*events)[i]];
		m_DigitalStates[ie.m_Id] = false;
		getInputEventListener()->onDigitalInputEvent(ie, false);
	}		
}

bool OSXSampleUserInput::getDigitalInputEventState(physx::PxU16 inputEventId ) const
{
	std::map<physx::PxU16,bool>::const_iterator fit = m_DigitalStates.find(inputEventId);
	if(fit != m_DigitalStates.end())
	{
		return fit->second;
	}
	else
	{
		return false;
	}
}
float OSXSampleUserInput::getAnalogInputEventState(physx::PxU16 inputEventId ) const
{
	std::map<physx::PxU16,float>::const_iterator fit = m_AnalogStates.find(inputEventId);
	if(fit != m_AnalogStates.end())
	{
		return fit->second;
	}
	else
	{
		return 0.0f;
	}
}

void OSXSampleUserInput::shutdown()
{	
	m_AnalogStates.clear();
	m_DigitalStates.clear();

	SampleUserInput::shutdown();
}

void OSXSampleUserInput::updateInput()
{
	SampleUserInput::updateInput();

	processGamepads();
}


