#pragma once
#include "Tile.h"

#define MAP_WIDTH 14
#define MAP_HEIGHT 12

class Map
{
private:
	Tile FrameImage;
	Tile* Tiles;
public:
	Map();
	~Map();

	void LoadingTiles();
	void Render(HDC front, HDC back);
};

