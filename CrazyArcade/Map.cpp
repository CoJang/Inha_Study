#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	tempTile = new Tile[MAP_SIZE];
	LoadingTiles();
}


Map::~Map()
{
}

void Map::LoadingTiles()
{
	wstring temp1 = TEXT("images/map/SandBlockYellow.bmp");
	path[0] = TEXT("images/map/SandBlockYellow.bmp");
	path[1] = TEXT("images/map/SandBlockBuff.bmp");

	int tempMap[MAP_SIZE] = { 1, 1, 0, 0, 1, 1 };

	for (int i = 0; i < MAP_SIZE; i++)
	{
		tempTile[i].InitTile(temp1, { 100, 100 + i * 44 });
	}
}

void Map::Render(HDC front, HDC back)
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		tempTile[i].Render(front, back);
	}
}
