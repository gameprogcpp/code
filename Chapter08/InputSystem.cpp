// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "InputSystem.h"

bool KeyboardState::GetKeyValue(SDL_Scancode code) const
{
	return mCurrState[code] == 1;
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode code) const
{
	if (mCurrState[code] == 0)
	{
		if (mPrevState[code] == 0)
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
		if (mPrevState[code] == 0)
		{
			return EPressed;
		}
		else
		{
			return EHeld;
		}
	}
}

InputSystem::InputSystem()
{
}

bool InputSystem::Initialize()
{
	return true;
}

void InputSystem::Shutdown()
{
}

void InputSystem::PrepareForUpdate()
{
}

void InputSystem::Update()
{
}
