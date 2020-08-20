#pragma once
#include "Tile.h"
#include "Block.h"

#define MAP_WIDTH 15
#define MAP_HEIGHT 13

class Map
{
private:
	Tile FrameImage;
	Tile* Tiles;
	Block* Blocks;
public:
	Map();
	~Map();

	void LoadingTiles();
	void LoadingBlocks();
	void Render(HDC front, HDC back);
};

