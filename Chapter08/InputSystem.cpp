// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "InputSystem.h"
#include <SDL/SDL.h>
#include <cstring>

bool KeyboardState::GetKeyValue(int keyCode) const
{
	return mCurrState[keyCode] == 1;
}

ButtonState KeyboardState::GetKeyState(int keyCode) const
{
	if (mCurrState[keyCode] == 0)
	{
		if (mPrevState[keyCode] == 0)
		{
			return ENone;
		}
		else
		{
			return EReleased;
		}
	}
	else // must be 1
	{
		if (mPrevState[keyCode] == 0)
		{
			return EPressed;
		}
		else
		{
			return EHeld;
		}
	}
}

bool InputSystem::Initialize()
{
	// Assign current state pointer
	mState.Keyboard.mCurrState = SDL_GetKeyboardState(NULL);
	// Clear previous state memory
	memset(mState.Keyboard.mPrevState, 0,
		SDL_NUM_SCANCODES);

	return true;
}

void InputSystem::Shutdown()
{
}

void InputSystem::PrepareForUpdate()
{
	// Copy current state to previous
	// Keyboard
	memcpy(mState.Keyboard.mPrevState,
		mState.Keyboard.mCurrState,
		SDL_NUM_SCANCODES);
}

void InputSystem::Update()
{
}
