#include "stdafx.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
	Images = new HBITMAP[TOTAL_SIZE];

	if (!LoadingImages())
		cout << "ImageManager Loading Failed!" << endl;
}


ImageManager::~ImageManager()
{
	for (int i = 0; i < TOTAL_SIZE; i++)
	{
		DeleteObject(Images[i]);
	}
	delete[] Images;
}

bool ImageManager::LoadingImages()
{
	wstring path = TEXT("images/Frame/play_bg.bmp");
	Images[BG_FRAME] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP,	0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[BG_FRAME] == NULL) return false;

	path = TEXT("images/map/forest/Tiles/BackTile.bmp");
	Images[MAP_TILE] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP,	0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[MAP_TILE] == NULL) return false;

// Obstacle Blocks
	for (int i = 1; i <= 4; i++)
	{
		path = TEXT("images/map/forest/Obstacle/Block_"); 
		path += to_wstring(i);
		path += TEXT(".bmp");

		Images[MAP_TILE + i] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[MAP_TILE + i] == NULL) return false;
	}

// Breakable Blocks
	for (int i = 5; i <= 13; i++)
	{
		path = TEXT("images/map/forest/Blocks/block_"); 
		path += to_wstring(i);
		path += TEXT(".bmp");

		Images[i + 1] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[i + 1] == NULL) return false;
	}

// Items
	for (int i = 1; i <= 4; i++)
	{
		path = TEXT("images/items/Gift"); path += to_wstring(i);
		path += TEXT(".bmp");

		Images[MAP_BLK_9 + i] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[MAP_BLK_9 + i] == NULL) return false;
	}

	path = TEXT("images/effect/Explosion.bmp");
	Images[EFX_EXPLOSION] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[EFX_EXPLOSION] == NULL) return false;

	path = TEXT("images/effect/Popo.bmp");
	Images[WATER_BOMB] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[WATER_BOMB] == NULL) return false;

// char

	{ // BAZZY
		path = TEXT("images/char/Role1.bmp");
		Images[CHAR_BAZZY] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[CHAR_BAZZY] == NULL) return false;

		path = TEXT("images/char/Role1Trap2.bmp");
		Images[CHAR_BAZZY_TRAP] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[CHAR_BAZZY_TRAP] == NULL) return false;

		path = TEXT("images/char/Role1Die2.bmp");
		Images[CHAR_BAZZY_DIE] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[CHAR_BAZZY_DIE] == NULL) return false;
	}

	path = TEXT("images/char/Role2.bmp");
	Images[CHAR_HOOCU] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[CHAR_HOOCU] == NULL) return false;

// LOBBY
	path = TEXT("images/Frame/Waiting.bmp");
	Images[LOBBY_FRAME] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[LOBBY_FRAME] == NULL) return false;

	return true;
}
