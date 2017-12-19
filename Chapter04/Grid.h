// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
#include <vector>

class Grid : public Actor
{
public:
	Grid(class Game* game);
	
	// Handle a mouse click at the x/y screen locations
	void ProcessClick(int x, int y);
	
	// Use A* to find a path
	bool FindPath(class Tile* start, class Tile* goal);
	
	// Try to build a tower
	void BuildTower();
	
	// Get start/end tile
	class Tile* GetStartTile();
	class Tile* GetEndTile();

	void UpdateActor(float deltaTime) override;
private:
	// Select a specific tile
	void SelectTile(size_t row, size_t col);
	
	// Update textures for tiles on path
	void UpdatePathTiles(class Tile* start);
	
	// Currently selected tile
	class Tile* mSelectedTile;
	
	// 2D vector of tiles in grid
	std::vector<std::vector<class Tile*>> mTiles;
	
	// Time until next enemy
	float mNextEnemy;
	
	// Rows/columns in grid
	const size_t NumRows = 7;
	const size_t NumCols = 16;
	// Start y position of top left corner
	const float StartY = 192.0f;
	// Width/height of each tile
	const float TileSize = 64.0f;
	// Time between enemies
	const float EnemyTime = 1.5f;
};
