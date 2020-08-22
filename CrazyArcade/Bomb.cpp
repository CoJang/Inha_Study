#include "stdafx.h"
#include "Bomb.h"

Bomb::Bomb(int Owner, POINT pos, int power)
{
	hImage = (HBITMAP)LoadImage(NULL, TEXT("images/effect/Popo.bmp"), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hImage, sizeof(BITMAP), &bitImage);
	
	Sprite_Size.x = bitImage.bmWidth / 3;
	Sprite_Size.y = bitImage.bmHeight;
	ImageScale = 1.2f;

	Anim_Frame_Max = bitImage.bmWidth / Sprite_Size.x - 1;
	Anim_Frame_Min = 0;
	Anim_Frame_Cur = Anim_Frame_Min;
	Anim_Frame_Flag = 0;
	Anim_Timer = 0;
	Anim_Speed = 180;

	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;

	Pos = pos;
	ImagePivot = { 0, -18 };
	ColPivot = { 26, 24 };
	ColliderSize = { 36, 36 };

	Pos.x -= ImagePivot.x;
	Pos.y -= ImagePivot.y;

	Power = power;
	PlayerNum = Owner;
	IsDetonated = false;
}

Bomb::~Bomb()
{
}

void Bomb::Update()
{
	Timer += ElapseTime;

	if (Timer > DETONATE_TIME)
		IsDetonated = true;

	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;

	UpdateFrame();
}

void Bomb::UpdateFrame()
{
	Anim_Timer += ElapseTime;

	if (Anim_Timer > Anim_Speed)
	{
		// To Avoid Trap in Bomb, Set Collider in Hear
		ColliderBox = { Pos.x - ColliderSize.x / 2 + ColPivot.x,
						Pos.y - ColliderSize.y / 2 + ColPivot.y,
						Pos.x + ColliderSize.x / 2 + ColPivot.x,
						Pos.y + ColliderSize.y / 2 + ColPivot.y };

		Anim_Frame_Cur++;
		Anim_Timer = 0;
	}

	if (Anim_Frame_Cur > Anim_Frame_Max)
		Anim_Frame_Cur = Anim_Frame_Min;
}
