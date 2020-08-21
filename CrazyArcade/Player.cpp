#include "stdafx.h"
#include "Block.h"
#include "MyMath.h"
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

	ColPivot = { 26, 48 };
	PlayerColliderSize = 36;
	CharSize = 1.1f;

	MaxBomb = 1;
	BombPower = 1;
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
	}
}

void Player::Collision(Block * Blocks)
{
	RECT BlockArea;

	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		if (Blocks[i].GetPassable() || Blocks[i].GetDestructible() == false)
			continue;

		BlockArea = Blocks[i].GetArea();

		if (RRCollision(&Collider, &BlockArea))
		{
			Pos.x -= Speed * Dir.x;
			Pos.y -= Speed * Dir.y;

			Collider = { Pos.x - PlayerColliderSize / 2 + ColPivot.x,
						 Pos.y - PlayerColliderSize / 2 + ColPivot.y,
						 Pos.x + PlayerColliderSize / 2 + ColPivot.x,
						 Pos.y + PlayerColliderSize / 2 + ColPivot.y };
		}
	}
}

void Player::Update()
{
	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;

	UpdateFrame();

	Pos.x += Speed * Dir.x;
	Pos.y += Speed * Dir.y;

	Collider = { Pos.x - PlayerColliderSize / 2 + ColPivot.x,
				 Pos.y - PlayerColliderSize / 2 + ColPivot.y,
				 Pos.x + PlayerColliderSize / 2 + ColPivot.x,
				 Pos.y + PlayerColliderSize / 2 + ColPivot.y };
}

void Player::UpdateFrame()
{
	Anim_Frame_Cur++;

	if (Anim_Frame_Cur > Anim_Frame_Max)
		Anim_Frame_Cur = Anim_Frame_Min;
}

void Player::Render(HDC front, HDC back, bool ColliderDraw)
{
	HBITMAP oldbuffer = (HBITMAP)SelectObject(back, hImage);

	TransparentBlt(front, Pos.x, Pos.y, 
		Sprite_Size.x * CharSize,
		Sprite_Size.y * CharSize,
		back, Start.x, Start.y, Sprite_Size.x, Sprite_Size.y, FILTER);

	if(ColliderDraw)
		Rectangle(front, Collider.left, Collider.top, 
						 Collider.right, Collider.bottom);

	SelectObject(back, oldbuffer);
	DeleteObject(oldbuffer);
}
