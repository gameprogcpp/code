// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>

class BoardState
{
public:
	BoardState();
	std::vector<BoardState*> GetPossibleMoves();
	bool IsTerminal();
	float GetScore();

	enum SquareState { Empty, Red, Yellow };
	SquareState mBoard[6][7];
protected:
	bool IsFull();
	int GetFourInARow();
	float CalculateHeuristic();
};

// Try to place the player's piece
bool TryPlayerMove(class BoardState* state, int column);

// Make the next CPU move
void CPUMove(class BoardState* state);