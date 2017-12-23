// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "UIScreen.h"

class DialogBox : public UIScreen
{
public:
	// (Lower draw order corresponds with further back)
	DialogBox(class Game* game, const std::string& text,
		std::function<void()> onOK);
	~DialogBox();
};
