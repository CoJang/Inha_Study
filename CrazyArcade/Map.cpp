#include "stdafx.h"
#include "CollisionManager.h"
#include "Map.h"

#define TILE_PIVOT {-26, -53}
#define OBSTACLE_PIVOT {-26, -39}
#define BLOCK_PIVOT {-18, -36}

extern Singleton* singleton;

Map::Map()
{
	Blocks = new Block[MAP_WIDTH * MAP_HEIGHT];
	BlockImages = new HBITMAP[13];
	BlockBitmaps = new BITMAP[13];
	LoadingBackground();
	LoadingBlocks();

	singleton->GetCollisionManager()->SetMap(this);
}


Map::~Map()
{
	delete[] Blocks;
	delete[] BlockImages;
	delete[] BlockBitmaps;
}

void Map::LoadingBackground()
{
	// BackGround Frame
	FrameImage.Init(TEXT("images/Frame/play_bg.bmp"), { 0, 0 }, { 0, 0 });
	BackTiles.Init(TEXT("images/map/forest/Tiles/BackTile.bmp"), { 0, 0 }, TILE_PIVOT);
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
	
	// 여유있을 때 파일 입/출력으로 뺄 것
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

			if (ImageIndex == -1) continue;

			if (ImageIndex < 4) // UnDestructable & Only Collision
			{
				if (ImageIndex == 3) // pond
				{
					Blocks[x + (y * MAP_WIDTH)].Init({ x * 52, y * 52 }, TILE_PIVOT);
					Blocks[x + (y * MAP_WIDTH)].InitCollider({ 78, 48 }, 128, 94);
					Blocks[x + (y * MAP_WIDTH)].SetImage(BlockImages[ImageIndex], BlockBitmaps[ImageIndex]);
				}
				else
				{
					Blocks[x + (y * MAP_WIDTH)].Init({ x * 52, y * 52 }, OBSTACLE_PIVOT);
					Blocks[x + (y * MAP_WIDTH)].InitCollider({ -1, -1 }, -1);
					Blocks[x + (y * MAP_WIDTH)].SetImage(BlockImages[ImageIndex], BlockBitmaps[ImageIndex]);
				}

				OBSTACLE_VECTOR.push_back(&Blocks[x + (y * MAP_WIDTH)]);
			}
			else
			{
				Blocks[x + (y * MAP_WIDTH)].Init({ x * 52, y * 52 }, BLOCK_PIVOT);
				Blocks[x + (y * MAP_WIDTH)].SetImage(BlockImages[ImageIndex], BlockBitmaps[ImageIndex]);
				Blocks[x + (y * MAP_WIDTH)].InitCollider({ 34, 36 }, -1);
				Blocks[x + (y * MAP_WIDTH)].InitAnimation();
				Blocks[x + (y * MAP_WIDTH)].SetDestructible(true);

				BLOCK_VECTOR.push_back(&Blocks[x + (y * MAP_WIDTH)]);
			}
		}
#pragma endregion
}

void Map::Update()
{
	for (Block* B : BLOCK_VECTOR)
	{
		B->Update();
	}

	for (Item* I : ITEM_VECTOR)
	{
		I->Update();
	}
}

void Map::FrontRender(HDC front, HDC back, bool ColliderDraw)
{
	FrameImage.Render(front, back, ColliderDraw);
	BackTiles.Render(front, back, ColliderDraw);
}

void Map::BackRender(HDC front, HDC back, bool ColliderDraw)
{
	for (Block* B : OBSTACLE_VECTOR)
	{
		B->Render(front, back, ColliderDraw);
	}
	for (Block* B : BLOCK_VECTOR)
	{
		B->Render(front, back, ColliderDraw);
	}

	//for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	//{
	//	Blocks[i].Render(front, back, ColliderDraw);
	//}

	for (Item* I : ITEM_VECTOR)
	{
		I->Render(front, back, ColliderDraw);
	}
}
