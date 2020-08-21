#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	hImage = (HBITMAP)LoadImage(NULL, TEXT("images/char/Role1.bmp"), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hImage, sizeof(BITMAP), &bitImage);

	Sprite_Size.x = bitImage.bmWidth / 6;
	Sprite_Size.y = bitImage.bmHeight / 4;

	Anim_Frame_Max = bitImage.bmWidth / Sprite_Size.x - 1;
	Anim_Frame_Min = 0;
	Anim_Frame_Cur = Anim_Frame_Min;
	Anim_Frame_Flag = 1;

	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;
	Dir = { 0, 0 }; Speed = 10;
}


Player::~Player()
{
}

void Player::InitPlayer(POINT pos, POINT pivot)
{
	Pivot = pivot;
	Pos = pos;

	Pos.x -= Pivot.x;
	Pos.y -= Pivot.y;
}

void Player::SetPlayerDir(POINT dir)
{
	Dir = dir;

	// Left
	if (Dir.x == 1)
	{
		Anim_Frame_Flag = 3;
	} // Right
	else if (Dir.x == -1)
	{
		Anim_Frame_Flag = 2;
	}// Up
	else if (Dir.y == -1)
	{
		Anim_Frame_Flag = 0;
	}// Down
	else if (Dir.y == 1)
	{
		Anim_Frame_Flag = 1;
	}
	else // idle
	{
		Anim_Frame_Cur = Anim_Frame_Min;
		Dir.x = 0, Dir.y = 0;
	}
}

void Player::Update()
{
	UpdateFrame();

	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;

	Pos.x += Speed * Dir.x;
	Pos.y += Speed * Dir.y;
}

void Player::UpdateFrame()
{
	Anim_Frame_Cur++;

	if (Anim_Frame_Cur > Anim_Frame_Max)
		Anim_Frame_Cur = Anim_Frame_Min;
}

void Player::Render(HDC front, HDC back)
{
	HBITMAP oldbuffer = (HBITMAP)SelectObject(back, hImage);

	TransparentBlt(front, Pos.x, Pos.y, Sprite_Size.x, Sprite_Size.y,
		back, Start.x, Start.y, Sprite_Size.x, Sprite_Size.y, FILTER);

	SelectObject(back, oldbuffer);
	DeleteObject(oldbuffer);
}
