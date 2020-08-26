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

	path = TEXT("images/map/forest/Obstacle/Block_1.bmp");
	Images[MAP_OBS_1] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[MAP_OBS_1] == NULL) return false;

	path = TEXT("images/map/forest/Obstacle/Block_2.bmp");
	Images[MAP_OBS_2] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[MAP_OBS_2] == NULL) return false;

	path = TEXT("images/map/forest/Obstacle/Block_3.bmp");
	Images[MAP_OBS_3] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[MAP_OBS_3] == NULL) return false;

	path = TEXT("images/map/forest/Obstacle/Block_4.bmp");
	Images[MAP_OBS_POND] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[MAP_OBS_POND] == NULL) return false;

	path = TEXT("images/map/forest/Blocks/block_5.bmp");
	Images[MAP_BLK_1] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[MAP_BLK_1] == NULL) return false;

	path = TEXT("images/map/forest/Blocks/block_6.bmp");
	Images[MAP_BLK_2] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[MAP_BLK_2] == NULL) return false;

	path = TEXT("images/map/forest/Blocks/block_7.bmp");
	Images[MAP_BLK_3] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[MAP_BLK_3] == NULL) return false;

	path = TEXT("images/map/forest/Blocks/block_8.bmp");
	Images[MAP_BLK_4] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[MAP_BLK_4] == NULL) return false;

	path = TEXT("images/map/forest/Blocks/block_9.bmp");
	Images[MAP_BLK_5] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[MAP_BLK_5] == NULL) return false;

	path = TEXT("images/map/forest/Blocks/block_10.bmp");
	Images[MAP_BLK_6] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[MAP_BLK_6] == NULL) return false;

	path = TEXT("images/map/forest/Blocks/block_11.bmp");
	Images[MAP_BLK_7] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[MAP_BLK_7] == NULL) return false;

	path = TEXT("images/map/forest/Blocks/block_12.bmp");
	Images[MAP_BLK_8] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[MAP_BLK_8] == NULL) return false;

	path = TEXT("images/map/forest/Blocks/block_13.bmp");
	Images[MAP_BLK_9] = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (Images[MAP_BLK_9] == NULL) return false;

	return true;
}
