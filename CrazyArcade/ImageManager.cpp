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

	{ // DAO
		path = TEXT("images/char/Role3.bmp");
		Images[CHAR_DAO] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[CHAR_DAO] == NULL) return false;

		path = TEXT("images/char/Role3Trap.bmp");
		Images[CHAR_DAO_TRAP] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[CHAR_DAO_TRAP] == NULL) return false;

		path = TEXT("images/char/Role3Die.bmp");
		Images[CHAR_DAO_DIE] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[CHAR_DAO_DIE] == NULL) return false;
	}

// LOBBY
	{
		path = TEXT("images/Frame/Waiting.bmp");
		Images[LOBBY_FRAME] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[LOBBY_FRAME] == NULL) return false;

		path = TEXT("images/map/forest/minimap.bmp");
		Images[LOBBY_MINIMAP_FOREST] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[LOBBY_MINIMAP_FOREST] == NULL) return false;

		path = TEXT("images/Frame/check.bmp");
		Images[LOBBY_CHECK1] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[LOBBY_CHECK1] == NULL) return false;

		path = TEXT("images/Frame/check2.bmp");
		Images[LOBBY_CHECK2] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[LOBBY_CHECK2] == NULL) return false;

		path = TEXT("images/Frame/start.bmp");
		Images[LOBBY_START] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[LOBBY_START] == NULL) return false;

		path = TEXT("images/Frame/face01.bmp");
		Images[LOBBY_BAZZY_FACE] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[LOBBY_BAZZY_FACE] == NULL) return false;

		path = TEXT("images/Frame/face02.bmp");
		Images[LOBBY_DAO_FACE] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[LOBBY_DAO_FACE] == NULL) return false;

		path = TEXT("images/Frame/friend_01.bmp");
		Images[LOBBY_BAZZY_CHAR] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[LOBBY_BAZZY_CHAR] == NULL) return false;

		path = TEXT("images/Frame/friend_03.bmp");
		Images[LOBBY_DAO_CHAR] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[LOBBY_DAO_CHAR] == NULL) return false;
	}
	
// IN GAME
	{
		path = TEXT("images/Frame/win.bmp");
		Images[GAME_WIN] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[GAME_WIN] == NULL) return false;
		
		path = TEXT("images/Frame/lose.bmp");
		Images[GAME_LOSE] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[GAME_LOSE] == NULL) return false;
		
		path = TEXT("images/Frame/draw.bmp");
		Images[GAME_DRAW] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (Images[GAME_DRAW] == NULL) return false;
	}

	return true;
}
