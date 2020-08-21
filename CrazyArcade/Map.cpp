#include "stdafx.h"
#include "Map.h"

#define TILE_PIVOT {-26, -53}
#define OBSTACLE_PIVOT {-26, -39}
#define BLOCK_PIVOT {-18, -36}

Map::Map()
{
	Tiles = new Tile[MAP_WIDTH * MAP_HEIGHT];
	TileImages = new HBITMAP[14];
	TileBitmaps = new BITMAP[14];

	Blocks = new Block[MAP_WIDTH * MAP_HEIGHT];
	BlockImages = new HBITMAP[13];
	BlockBitmaps = new BITMAP[13];
	LoadingTiles();
	LoadingBlocks();
}


Map::~Map()
{
	delete[] Tiles;
	delete[] TileImages;
	delete[] TileBitmaps;
	delete[] Blocks;
	delete[] BlockImages;
	delete[] BlockBitmaps;
}

void Map::LoadingTiles()
{
	// BackGround Frame
	FrameImage.Init(TEXT("images/Frame/play_bg.bmp"), { 0, 0 }, { 0, 0 });

// 15 * 13  [10 kinds]
#pragma region SetTiles
	wstring Path;
	for (int i = 0; i < 13; i++)
	{
		Path = TEXT("images/map/forest/Tiles/tile_");
		Path += to_wstring(i + 1); Path += TEXT(".bmp");
		TileImages[i] = (HBITMAP)LoadImage(NULL, Path.c_str(), IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(TileImages[i], sizeof(BITMAP), &TileBitmaps[i]);
	}

	int TileSets[MAP_WIDTH * MAP_HEIGHT] = 
	{   
		5, 6, 7, 8, 9, 10,  12, 8, 12,  10, 9, 8, 7, 6, 5,
		5, 6, 7, 8, 9, 10,  13, 8, 13,  10, 9, 8, 7, 6, 5,
		5, 6, 7, 8, 9, 10,  13, 8, 13,  10, 9, 8, 7, 6, 5,
		5, 6, 7, 8, 9, 10,  13, 8, 13,  10, 9, 8, 7, 6, 5,
		5, 6, 7, 8, 9, 10,  13, 8, 13,  10, 9, 8, 7, 6, 5,
		4, 2, 2, 1, 1, 2,   1,  9,  1,  2, 2, 1, 1, 2, 3,
		6, 5, 10, 9, 7, 6,  7,  9,  7,  6, 7, 9, 10, 5, 6,
		4, 2, 2, 1, 1, 2,   1,  9,  1,  2, 2, 1, 1, 2, 3,
		5, 6, 7, 8, 9, 10,  13, 8, 13, 10, 9, 8, 7, 6, 5,
		5, 6, 7, 8, 9, 10,  13, 8, 13, 10, 9, 8, 7, 6, 5,
		5, 6, 7, 8, 9, 10,  13, 8, 13, 10, 9, 8, 7, 6, 5,
		5, 6, 7, 8, 9, 10,  13, 8, 13, 10, 9, 8, 7, 6, 5,
		5, 6, 7, 8, 9, 10,  11, 8, 11, 10, 9, 8, 7, 6, 5,
	};

	for(int x = 0; x < MAP_WIDTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			int ImageIndex = TileSets[x + (y * MAP_WIDTH)] - 1;
			Tiles[x + (y * MAP_WIDTH)].Init(Path.c_str(), { x * 52, y * 52 }, TILE_PIVOT);
			Tiles[x + (y * MAP_WIDTH)].SetImage(TileImages[ImageIndex], TileBitmaps[ImageIndex]);
		}
#pragma endregion
}

void Map::LoadingBlocks()
{
// 15 * 13  [4 kinds]
#pragma region SetBlocks
	wstring Path;
	for (int i = 0; i < 4; i++)
	{
		Path = TEXT("images/map/forest/Obstacle/Block_");
		Path += to_wstring(i + 1); Path += TEXT(".bmp");
		BlockImages[i] = (HBITMAP)LoadImage(NULL, Path.c_str() , IMAGE_BITMAP,
				0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			GetObject(BlockImages[i], sizeof(BITMAP), &BlockBitmaps[i]);
	}
	for (int i = 4; i < 13; i++)
	{
		Path = TEXT("images/map/forest/Blocks/block_");
		Path += to_wstring(i + 1); Path += TEXT(".bmp");
		BlockImages[i] = (HBITMAP)LoadImage(NULL, Path.c_str(), IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(BlockImages[i], sizeof(BITMAP), &BlockBitmaps[i]);
	}
	
	int BlockSets[MAP_WIDTH * MAP_HEIGHT] =
	{
		3,  0,  9,  0,  9,  0,   0,  8,  0,   0,  9,  0,  9,  0,  3,
		0,  0,  0,  5,  5,  0,   2, 11,  2,   0,  5,  5,  0,  0,  0,
		7,  6,  4,  0,  0,  6,  11, 12, 11,   6,  4,  0,  0,  6,  7,
		0,  6,  0,  0,  0,  6,   8,  1,  8,   6,  0,  0,  0,  6,  0,
		7,  0,  5,  5,  0,  0,   0, 12,  0,   0,  0,  5,  5,  0,  7,

		0,  2, 11,  8,  5,  0,   8,  1,  8,   0,  5,  8, 11,  2,  0,
		8, 11, 12,  1, 10,  1,  12, 13, 12,   1, 10,  1, 12, 11,  8,
		0,  2, 11,  8,  5,  0,   8,  1,  8,   0,  5,  8, 11,  2,  0,

		7,  0,  5,  5,  0,  0,   0, 12,  0,   0,  0,  5,  5,  0,  7,
		0,  6,  4,  0,  0,  6,   8,  1,  8,   6,  4,  0,  0,  6,  0,
		7,  6,  0,  0,  0,  6,  11, 12, 11,   6,  0,  0,  0,  6,  7,
		0,  0,  0,  5,  5,  0,   2, 11,  2,   0,  5,  5,  0,  0,  0,
		3,  0,  9,  0,  9,  0,   0,  8,  0,   0,  9,  0,  9,  0,  3
	};

	for (int x = 0; x < MAP_WIDTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			int ImageIndex = BlockSets[x + (y * MAP_WIDTH)] - 1;

			if (ImageIndex < 4)
			{
				if (ImageIndex == -1) continue;

				if (ImageIndex == 3)
				{
					Blocks[x + (y * MAP_WIDTH)].Init(false, false, { x * 52, y * 52 }, TILE_PIVOT);
					Blocks[x + (y * MAP_WIDTH)].SetImage(BlockImages[ImageIndex], BlockBitmaps[ImageIndex]);
				}
				else
				{
					Blocks[x + (y * MAP_WIDTH)].Init(false, false, { x * 52, y * 52 }, OBSTACLE_PIVOT);
					Blocks[x + (y * MAP_WIDTH)].SetImage(BlockImages[ImageIndex], BlockBitmaps[ImageIndex]);
				}
			}
			else
			{
				Blocks[x + (y * MAP_WIDTH)].Init(false, true, { x * 52, y * 52 }, BLOCK_PIVOT);
				Blocks[x + (y * MAP_WIDTH)].SetImage(BlockImages[ImageIndex], BlockBitmaps[ImageIndex]);
			}
		}
#pragma endregion
}

void Map::Render(HDC front, HDC back)
{
	FrameImage.Render(front, back);

	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		Tiles[i].Render(front, back);
	}

	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		Blocks[i].Render(front, back);
	}
}
