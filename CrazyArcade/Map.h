#pragma once
#include "Tile.h"
#include "Block.h"

#define MAP_WIDTH 15
#define MAP_HEIGHT 13

class Map
{
private:
	Tile FrameImage;
	
	Block* Blocks;
	HBITMAP* BlockImages;
	BITMAP* BlockBitmaps;

	Tile* Tiles;
	HBITMAP* TileImages;
	BITMAP* TileBitmaps;
public:
	Map();
	~Map();

	void LoadingTiles();
	void LoadingBlocks();
	void Render(HDC front, HDC back);
};

