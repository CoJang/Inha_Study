#include "stdafx.h"
#include "Bomb.h"

Bomb::Bomb(int Owner, POINT pos, int power)
{
	hImage = (HBITMAP)LoadImage(NULL, TEXT("images/effect/Popo.bmp"), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hImage, sizeof(BITMAP), &bitImage);
	
	Sprite_Size.x = bitImage.bmWidth / 3;
	Sprite_Size.y = bitImage.bmHeight;
	BombSize = 1.2f;

	Anim_Frame_Max = bitImage.bmWidth / Sprite_Size.x - 1;
	Anim_Frame_Min = 0;
	Anim_Frame_Cur = Anim_Frame_Min;
	Anim_Frame_Flag = 0;
	Anim_Timer = 0;
	Anim_Speed = 180;

	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;

	Pos = pos;
	Pivot = { 0, -18 };
	ColPivot = { 26, 36 };
	BombColliderSize = 36;

	Pos.x -= Pivot.x;
	Pos.y -= Pivot.y;

	Power = power;
	PlayerNum = Owner;
}

Bomb::~Bomb()
{
}

void Bomb::Update()
{
	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;

	UpdateFrame();
}

void Bomb::UpdateFrame()
{
	if (Anim_Timer > Anim_Speed)
	{
		// To Avoid Trap in Bomb, Set Collider in Hear
		Collider = { Pos.x - BombColliderSize / 2 + ColPivot.x,
					 Pos.y - BombColliderSize / 2 + ColPivot.y,
					 Pos.x + BombColliderSize / 2 + ColPivot.x,
					 Pos.y + BombColliderSize / 2 + ColPivot.y };

		Anim_Frame_Cur++;
		Anim_Timer = 0;
	}
	else
	{
		Anim_Timer += ElapseTime;
	}

	if (Anim_Frame_Cur > Anim_Frame_Max)
		Anim_Frame_Cur = Anim_Frame_Min;
}

void Bomb::Render(HDC front, HDC back, bool ColliderDraw)
{
	HBITMAP oldbuffer = (HBITMAP)SelectObject(back, hImage);

	TransparentBlt(front, Pos.x, Pos.y, 
					Sprite_Size.x * BombSize,
					Sprite_Size.y * BombSize,
					back, Start.x, Start.y,
					Sprite_Size.x, Sprite_Size.y, FILTER);

	if (ColliderDraw)
		Rectangle(front, Collider.left, Collider.top,
						 Collider.right, Collider.bottom);

	SelectObject(back, oldbuffer);
	DeleteObject(oldbuffer);
}
