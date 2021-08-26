// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <string>
#include "Math.h"

class SoundEvent
{
public:
	SoundEvent();
	// Returns true if associated FMOD event still exists
	bool IsValid();
	// Restart event from beginning
	void Restart();
	// Stop this event
	void Stop(bool allowFadeOut = true);
	// Setters
	void SetPaused(bool pause);
	void SetVolume(float value);
	void SetPitch(float value);
	void SetParameter(const std::string& name, float value);
	// Getters
	bool GetPaused() const;
	float GetVolume() const;
	float GetPitch() const;
	float GetParameter(const std::string& name);
	// Positional
	bool Is3D() const;
	void Set3DAttributes(const Matrix4& worldTrans);
protected:
	// Make this constructor protected and AudioSystem a friend
	// so that only AudioSystem can access this constructor.
	friend class AudioSystem;
	SoundEvent(class AudioSystem* system, unsigned int id);
private:
	class AudioSystem* mSystem;
	unsigned int mID;
};