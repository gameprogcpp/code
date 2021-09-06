#pragma once
#include "Actor.h"
#include "AnimSpriteComponent.h"
#include <string>
class Character : public Actor
{
public:
	Character(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
private:
	// name of current animation
	std::string mCurrAnim;
	AnimSpriteComponent* mASC;

};