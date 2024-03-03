// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SDL/SDL.h"
#include <vector>

// Vector2 struct just stores x/y coordinates
// (for now)
struct Vector2
{
	Vector2() : x(), y() {};
	Vector2(float px, float py) : x(px), y(py) {};
	Vector2(const Vector2& other) {
		x = other.x;
		y = other.y;
	};
	float x;
	float y;
};

struct Paddle
{
	Paddle(Vector2 vector2, int paddleDir, short player)
		: m_paddle(vector2), m_paddleDir(paddleDir), m_player(player) {};
	Vector2 m_paddle;
	int m_paddleDir;
	short m_player;
};

enum class PLAYER {
	FIRST = 0,
	SECOND = 1
};

// Game class
class Game
{
public:
	Game();
	// Initialize the game
	bool Initialize();
	// Runs the game loop until the game is over
	void RunLoop();
	// Shutdown the game
	void Shutdown();
private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// Window created by SDL
	SDL_Window* mWindow;
	// Renderer for 2D drawing
	SDL_Renderer* mRenderer;
	// Number of ticks since start of game
	Uint32 mTicksCount;
	// Game should continue to run
	bool mIsRunning;
	
	// Pong specific
	// Direction of paddle
	//int mPaddleDir;

	// Position of paddle
	//Vector2 mPaddlePos;
	std::vector<Paddle> mPaddlesPos; // paddle, paddle info

	// Position of ball
	Vector2 mBallPos;


	// Velocity of ball
	Vector2 mBallVel;
};
