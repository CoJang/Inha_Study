#include "stdafx.h"
#include "Bomb.h"

Bomb::Bomb(int Owner, POINT pos, int power)
{
	AnimObject::Init(TEXT("images/effect/Popo.bmp"), RePosition(pos), { -26, -52 });

	Sprite_Size.x = bitImage.bmWidth / 3;
	Sprite_Size.y = bitImage.bmHeight;
	ImageScale = 1.2f;

	AnimObject::InitAnimation();
	Anim_Speed = 180;

	AnimObject::InitCollider({ 26, 24 }, 36);
	IsColliderActive = false;

	Power = power;
	PlayerNum = Owner;
	IsDetonated = false;
	Timer = 0;
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
		Anim_Frame_Cur++;
		Anim_Timer = 0;
		IsColliderActive = true;
	}

	if (Anim_Frame_Cur > Anim_Frame_Max)
		Anim_Frame_Cur = Anim_Frame_Min;
}

// Set In Tile
POINT Bomb::RePosition(POINT pos)
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		if (i * 52 < pos.x && pos.x < (i + 1) * 52)
		{
			pos.x = i * 52;
			break;
		}
	}

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		if (i * 52 < pos.y && pos.y < (i + 1) * 52)
		{
			pos.y = i * 52;
			break;
		}
	}

	return pos;
}
