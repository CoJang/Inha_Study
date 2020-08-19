#pragma once
#include "Tile.h"

#define MAP_SIZE 6

class Map
{
private:
	HBITMAP hTiles[33];
	BITMAP bitTiles[33];
	Tile* tempTile;
	wstring path[33];
public:
	Map();
	~Map();

	void LoadingTiles();
	void Render(HDC front, HDC back);
};

