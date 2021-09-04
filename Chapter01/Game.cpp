// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mTicksCount(0)
,mIsRunning(true)
,mPaddleDir(0)
{
	
}

bool Game::Initialize()
{
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	// Create an SDL Window
	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)", // Window title
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		1024,	// Width of window
		768,	// Height of window
		0		// Flags (0 for no flags set)
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	//// Create SDL renderer
	mRenderer = SDL_CreateRenderer(
		mWindow, // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	//
	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f/2.0f;
	mPaddle2Pos.x = 1014.0f;
	mPaddle2Pos.y = 768.0f / 2.0f;

	for (int i = 0; i < 2; ++i) {
		Ball ball;
		ball.pos.x = 1024.0f / 2.0f;
		ball.pos.y = 768 / 2.0f;

		ball.vel.x = (i%2 == 0) ? -200.0f : 200.0f;
		ball.vel.y = 235.0f;
		mBalls.push_back(ball);
	}
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// If we get an SDL_QUIT event, end loop
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// If escape is pressed, also end loop
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	
	// Update paddle direction based on W/S keys
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
	// Update paddle2 direction based on I/K keys
	mPaddle2Dir = 0;
	if (state[SDL_SCANCODE_I])
	{
		mPaddle2Dir -= 1;
	}
	if (state[SDL_SCANCODE_K])
	{
		mPaddle2Dir += 1;
	}
}

void Game::UpdateGame()
{
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	// Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	
	// Clamp maximum delta time value
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();
	
	// Update paddle position based on direction
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		// Make sure paddle doesn't move off screen!
		if (mPaddlePos.y < (paddleH/2.0f + thickness))
		{
			mPaddlePos.y = paddleH/2.0f + thickness;
		}
		else if (mPaddlePos.y > (768.0f - paddleH/2.0f - thickness))
		{
			mPaddlePos.y = 768.0f - paddleH/2.0f - thickness;
		}
	}

	// Update paddle2 position based on direction;
	if (mPaddle2Dir != 0)
	{
		mPaddle2Pos.y += mPaddle2Dir * 300.0f * deltaTime;
		// Make sure paddle2 doesn't move off screen
		if (mPaddle2Pos.y < paddleH / 2.0f + thickness)
		{
			mPaddle2Pos.y = paddleH / 2.0f + thickness;
		}
		if (mPaddle2Pos.y > (768.0f - paddleH / 2.0f - thickness))
		{
			mPaddle2Pos.y = 768.0f  - paddleH / 2.0f - thickness;
		}
	}
	
	// Update each ball 
	for (auto& ball = mBalls.begin(); ball != mBalls.end(); ++ball) {
		// Update ball position based on ball velocity
		ball->pos.x += ball->vel.x * deltaTime;
		ball->pos.y += ball->vel.y * deltaTime;

		// Bounce if needed
		// Did we intersect with the paddle1 (left)?
		float diff = mPaddlePos.y - ball->pos.y;
		// Take absolute value of difference
		diff = (diff > 0.0f) ? diff : -diff;
		if (
			// Our y-difference is small enough
			diff <= paddleH / 2.0f &&
			// We are in the correct x-position
			ball->pos.x <= 25.0f && ball->pos.x >= 20.0f &&
			// The ball is moving to the left
			ball->vel.x < 0.0f)
		{
			ball->vel.x *= -1.0f;
		}

		// Did we intersect with the paddle2 (right)?
		diff = mPaddle2Pos.y - ball->pos.y;
		// Take absolute value of diffrence
		diff = (diff > 0.0f) ? diff : -diff;
		if (
			// our y-difference is small enough
			diff < paddleH / 2.0f &&
			// We are in the correct x-position
			ball->pos.x <= 1014 + thickness / 2.0f && ball->pos.x >= 1014 - thickness / 2.0f &&
			// The ball is moving to the right
			ball->vel.x > 0.0f)
		{
			ball->vel.x *= -1.0f;
		}

		// Did the ball go off the screen? (if so, end game)
		else if (ball->pos.x <= 0.0f)
		{
			mIsRunning = false;
		}
		// Did the ball go off the screen? (if so, end game)
		else if (ball->pos.x >= (1024.0f - thickness))
		{
			mIsRunning = false;
		}

		// Did the ball collide with the top wall?
		if (ball->pos.y <= thickness && ball->vel.y < 0.0f)
		{
			ball->vel.y *= -1;
		}
		// Did the ball collide with the bottom wall?
		else if (ball->pos.y >= (768 - thickness) &&
			ball->vel.y > 0.0f)
		{
			ball->vel.y *= -1;
		}
	}


}

void Game::GenerateOutput()
{
	// Set draw color to blue
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G 
		255,	// B
		255		// A
	);
	
	// Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw walls
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	
	// Draw top wall
	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		1024,		// Width
		thickness	// Height
	};
	SDL_RenderFillRect(mRenderer, &wall);
	
	// Draw bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);
	
	//// Draw right wall
	//wall.x = 1024 - thickness;
	//wall.y = 0;
	//wall.w = thickness;
	//wall.h = 1024;
	//SDL_RenderFillRect(mRenderer, &wall);
	
	// Draw paddle
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH/2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	// Draw paddle2
	SDL_Rect paddle2{
		static_cast<int>(mPaddle2Pos.x),
		static_cast<int>(mPaddle2Pos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle2);

	// Draw balls
	for (auto iter = mBalls.begin(); iter != mBalls.end(); ++iter) 
	{
		const auto& ball = *iter;
		SDL_Rect b{
			static_cast<int>(ball.pos.x - thickness / 2),
			static_cast<int>(ball.pos.y - thickness / 2),
			thickness,
			thickness
		};
		SDL_RenderFillRect(mRenderer, &b);
	}

	
	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
