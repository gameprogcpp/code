// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE.txt for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
#include <vector>

class Grid : public Actor
{
public:
	Grid(class Game* game);
	void ProcessClick(int x, int y);
	bool FindPath(class Tile* start, class Tile* goal);
	void BuildTower();
	class Tile* GetStartTile();
	class Tile* GetEndTile();
	void UpdateActor(float deltaTime) override;
private:
	void SelectTile(size_t row, size_t col);
	void UpdatePathTiles(class Tile* start);
	class Tile* mSelectedTile;
	std::vector<std::vector<class Tile*>> mTiles;
	float mNextEnemy;
	
	const size_t NumRows = 7;
	const size_t NumCols = 16;
	const float StartY = 192.0f;
	const float TileSize = 64.0f;
	const float EnemyTime = 1.5f;
};
