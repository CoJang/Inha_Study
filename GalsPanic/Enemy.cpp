#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	Pos = { 0, 0 }; Dir = { 0, 0 }; Speed = 10;

	ImagePath = TEXT("images/Pac-Man_Sprites.bmp");
	hImage = (HBITMAP)LoadImage(NULL, ImagePath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hImage, sizeof(BITMAP), &bitImage);

	Sprite_Size.x = bitImage.bmWidth / 6;
	Sprite_Size.y = bitImage.bmHeight / 8;

	Anim_Frame_Max = bitImage.bmWidth / Sprite_Size.x - 1;
	Anim_Frame_Min = 0;
	Anim_Frame_Cur = Anim_Frame_Min;
	Anim_Frame_Flag = 0;

	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;
}

Enemy::~Enemy()
{
}
