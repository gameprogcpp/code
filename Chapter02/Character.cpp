#include "Character.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Character::Character(Game* game)
	:Actor(game),
	mCurrAnim()
{
	// Create an animated sprite component
	mASC = new AnimSpriteComponent(this);
	mASC->SetAnimFPS(8);
	std::vector<SDL_Texture*> walk = {
		game->GetTexture("Assets/Character01.png"),
		game->GetTexture("Assets/Character02.png"),
		game->GetTexture("Assets/Character03.png"),
		game->GetTexture("Assets/Character04.png"),
		game->GetTexture("Assets/Character05.png"),
		game->GetTexture("Assets/Character06.png")
	};
	mASC->SetAnimTextures(walk, "walk", true);
	mCurrAnim = "walk";
	std::vector<SDL_Texture*> jump = {
		game->GetTexture("Assets/Character07.png"),
		game->GetTexture("Assets/Character08.png"),
		game->GetTexture("Assets/Character09.png"),
		game->GetTexture("Assets/Character10.png"),
		game->GetTexture("Assets/Character11.png"),
		game->GetTexture("Assets/Character12.png"),
		game->GetTexture("Assets/Character13.png"),
		game->GetTexture("Assets/Character14.png"),
		game->GetTexture("Assets/Character15.png")
	};
	mASC->AddAnimTextures(jump, "jump", false);

	std::vector<SDL_Texture*> punch = {
		game->GetTexture("Assets/Character16.png"),
		game->GetTexture("Assets/Character17.png"),
		game->GetTexture("Assets/Character18.png")
	};
	mASC->AddAnimTextures(punch, "punch", false);

	
}

void Character::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// 
	mASC->runAnimation(mCurrAnim);

}

void Character::ProcessKeyboard(const uint8_t* state)
{
	if (state[SDL_SCANCODE_U])
	{
		mCurrAnim = "walk";
		mASC->SetAnimFPS(8);
	}
	if (state[SDL_SCANCODE_J])
	{
		mCurrAnim = "jump";
		mASC->SetAnimFPS(8);
	}
	if (state[SDL_SCANCODE_M])
	{
		mCurrAnim = "punch";
		mASC->SetAnimFPS(3);
	}
}