#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	Pos = { 0, 0 }; Dir = { 0, 0 }; Speed = 10;


}

Enemy::~Enemy()
{
}

void Enemy::InitEnemy(wstring filepath, POINT pos)
{
	Pos = pos;
	ImagePath = filepath;
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

void Enemy::Render(HDC front, HDC back)
{
}

void Enemy::UpdateFrame()
{
	Anim_Frame_Cur++;

	if (Anim_Frame_Cur > Anim_Frame_Max)
		Anim_Frame_Cur = Anim_Frame_Min;
}

void Enemy::Update()
{
	UpdateFrame();

	if (Pos.x < 0) Pos.x = 0;
	if (Pos.x > WIN_WIDTH - 50)
		Pos.x = WIN_WIDTH - 50;
	if (Pos.y < 0) Pos.y = 0;
	if (Pos.y > WIN_HEIGHT - 70)
		Pos.y = WIN_HEIGHT - 70;
}
