// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <SDL/SDL_scancode.h>
#include "Math.h"

// The different button states
enum ButtonState
{
	ENone,
	EPressed,
	EReleased,
	EHeld
};

// Helper for keyboard input
class KeyboardState
{
public:
	// Friend so InputSystem can easily update it
	friend class InputSystem;
	// Get just the boolean true/false value of key
	bool GetKeyValue(int keyCode) const;
	// Get a state based on current and previous frame
	ButtonState GetKeyState(int keyCode) const;
private:
	const Uint8* mCurrState;
	Uint8 mPrevState[SDL_NUM_SCANCODES];
};

// Helper for mouse input
class MouseState
{
public:
	friend class InputSystem;

	// For mouse position
	const Vector2& GetPosition() const { return mMousePos; }
	const Vector2& GetScrollWheel() const { return mScrollWheel; }
	bool IsRelative() const { return mIsRelative; }

	// For buttons
	bool GetButtonValue(int button) const;
	ButtonState GetButtonState(int button) const;
private:
	// Store current mouse position
	Vector2 mMousePos;
	// Motion of scroll wheel
	Vector2 mScrollWheel;
	// Store button data
	Uint32 mCurrButtons;
	Uint32 mPrevButtons;
	// Are we in relative mouse mode
	bool mIsRelative;
};

// Wrapper that contains current state of input
struct InputState
{
	KeyboardState Keyboard;
	MouseState Mouse;
};

class InputSystem
{
public:
	bool Initialize();
	void Shutdown();

	// Called right before SDL_PollEvents loop
	void PrepareForUpdate();
	// Called after SDL_PollEvents loop
	void Update();
	// Called to process an SDL event in input system
	void ProcessEvent(union SDL_Event& event);

	const InputState& GetState() const { return mState; }

	void SetRelativeMouseMode(bool value);
private:
	InputState mState;
};
