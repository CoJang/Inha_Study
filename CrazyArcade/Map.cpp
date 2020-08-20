#include "stdafx.h"
#include "Map.h"

#define TILE_PIVOT {-26, -53}
#define OBS_BLOCK_PIVOT {-25, -50}

Map::Map()
{
	Tiles = new Tile[MAP_WIDTH * MAP_HEIGHT];
	LoadingTiles();
}


Map::~Map()
{
	delete[] Tiles;
}

void Map::LoadingTiles()
{
	FrameImage.Init(TEXT("images/Frame/play_bg.bmp"), { 0, 0 }, { 0, 0 });

// 14 * 12  [10 kinds]
#pragma region SetTiles
	int TileSets[MAP_WIDTH * MAP_HEIGHT] = 
	{   
		5, 6, 7, 8, 9, 10,  12, 12, 12,  10, 9, 8, 7, 6, 5,
		5, 6, 7, 8, 9, 10,  13, 14, 13,  10, 9, 8, 7, 6, 5,
		5, 6, 7, 8, 9, 10,  13, 14, 13,  10, 9, 8, 7, 6, 5,
		5, 6, 7, 8, 9, 10,  13, 14, 13,  10, 9, 8, 7, 6, 5,
		5, 6, 7, 8, 9, 10,  13, 14, 13,  10, 9, 8, 7, 6, 5,
		4, 2, 2, 1, 1, 2,   1,  1,  1,   2, 2, 1, 1, 2, 3,
		4, 2, 2, 1, 1, 2,   1,  1,  1,   2, 2, 1, 1, 2, 3,
		4, 2, 2, 1, 1, 2,   1,  1,  1,   2, 2, 1, 1, 2, 3,
		5, 6, 7, 8, 9, 10,  13, 14, 13,   10, 9, 8, 7, 6, 5,
		5, 6, 7, 8, 9, 10,  13, 14, 13,   10, 9, 8, 7, 6, 5,
		5, 6, 7, 8, 9, 10,  13, 14, 13,   10, 9, 8, 7, 6, 5,
		5, 6, 7, 8, 9, 10,  13, 14, 13,   10, 9, 8, 7, 6, 5,
		5, 6, 7, 8, 9, 10,  11, 11, 11,   10, 9, 8, 7, 6, 5,
	};

	for(int x = 0; x < MAP_WIDTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			int tileNum = TileSets[x + (y * MAP_WIDTH)];
			wstring Path = TEXT("images/map/forest/Tiles/tile_");
			Path += to_wstring(tileNum); Path += TEXT(".bmp");

			Tiles[x + (y * MAP_WIDTH)].Init(Path.c_str(), { x * 52, y * 52 }, TILE_PIVOT);
		}
#pragma endregion

// 14 * 12  [10 kinds]
#pragma region SetBlocks
	//Tiles[6].InitTile(TEXT("images/map/forest/Obstacle/object_1.bmp"), false, false, OBS_BLOCK_PIVOT);
	//Tiles[6].SetPos({ 0, 0 });

	//Tiles[7].InitTile(TEXT("images/map/forest/Obstacle/object_2.bmp"), false, false, OBS_BLOCK_PIVOT);
	//Tiles[7].SetPos({ 52, 0 });

	//Tiles[8].InitTile(TEXT("images/map/forest/Obstacle/object_3.bmp"), false, false, OBS_BLOCK_PIVOT);
	//Tiles[8].SetPos({ 104, 0 });
#pragma endregion



}

void Map::Render(HDC front, HDC back)
{
	FrameImage.Render(front, back);

	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		Tiles[i].Render(front, back);
	}
}
