#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	Pos = { 0, 0 }; Dir = { 0, 0 }; Speed = 10;
	
	ImagePath = TEXT("images/character.bmp");
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
	CharSize = 2;

	prevPos = Pos;
	Max_Print = 99;
	PrintDist = 15;
}

Player::~Player(){}

void Player::Render(HDC front, HDC back)
{
	for (int i = 0; i < Max_Print; i++)
		if (FootPrints[i].IsActived())
			 FootPrints[i].SetPixelsRgn(map, FILLED, RGB(255, 0, 255)); // BGR¼ø¼­ÀÓ
		//else 
		//	 FootPrints[i].SetPixelsRgn(map, NOT_FILLED, RGB(255, 255, 255));

	//FootPrints[0].SetPixels(map, FILLED, RGB(255, 0, 0));

	if (prevPos.x + PrintDist < Pos.x || prevPos.x - PrintDist > Pos.x ||
		prevPos.y + PrintDist < Pos.y || prevPos.y - PrintDist > Pos.y)
	{
		for (int i = 0; i < Max_Print; i++)
		{
			if (!FootPrints[i].IsActived())
			{
				FootPrints[i].SetState(true);
				FootPrints[i].SetPos(prevPos);
				break;
			}
		}
	}

	HBITMAP oldbuffer;
	COLORREF Filter = RGB(255, 0, 255);

	oldbuffer = (HBITMAP)SelectObject(back, hImage);

	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;

	TransparentBlt(front, Pos.x, Pos.y, Sprite_Size.x * CharSize, Sprite_Size.y * CharSize,
		back, Start.x, Start.y, Sprite_Size.x, Sprite_Size.y, Filter);

	SelectObject(back, oldbuffer);
}


void Player::UpdateFrame()
{
	Anim_Frame_Cur++;

	if (Anim_Frame_Cur > Anim_Frame_Max)
		Anim_Frame_Cur = Anim_Frame_Min;
}

void Player::Update()
{
	UpdateFrame();

	if(prevPos.x + PrintDist < Pos.x || prevPos.x - PrintDist > Pos.x ||
		prevPos.y + PrintDist < Pos.y || prevPos.y - PrintDist > Pos.y)
		prevPos = Pos;

	Pos.x = Pos.x + (Dir.x * Speed);
	Pos.y = Pos.y + (Dir.y * Speed);

	for (int i = 0; i < Max_Print; i++)
		if (FootPrints[i].IsActived())
			 FootPrints[i].Update();
}

void Player::SetPlayerDir(POINT input)
{
	Dir = input;

	if (Dir.y == 1)
	{
		Anim_Frame_Flag = 0;
	}
	else if (Dir.x == -1)
	{
		Anim_Frame_Flag = 1;
	}
	else if (Dir.x == 1)
	{
		Anim_Frame_Flag = 2;
	}
	else if(Dir.y == -1)
	{
		Anim_Frame_Flag = 3;
	}
	else
	{
		Anim_Frame_Cur = Anim_Frame_Min;
		Dir.x = 0; Dir.y = 0;
	}
}

FootPrint::FootPrint()
{
	Pivot.x = 33; Pivot.y = 60; r = 10;
	Rgn = { Pos.x + Pivot.x - r, Pos.y + Pivot.y - r, Pos.x + Pivot.x + r, Pos.y + Pivot.y + r };
	LifeTime = 4000; IsActive = false; Life = LifeTime;
}

void FootPrint::Update()
{
	if (Life <= 0)
	{
		IsActive = false;
		Life = LifeTime;
		Pos = { 0, 0 };
	}
	else
	{
		Life -= ElapseTime;
	}

	Rgn = { Pos.x + Pivot.x - r, Pos.y + Pivot.y - r, Pos.x + Pivot.x + r, Pos.y + Pivot.y + r };

}

void FootPrint::SetPixelsRgn(MyMap* map, TileState state, COLORREF color)
{
	for(int y = Rgn.top; y < Rgn.bottom; y++)
		for (int x = Rgn.left; x < Rgn.right; x++)
		{
			map->SetMapTileState({ x, y }, state);
			map->SetMapTileColor({ x, y }, color);
		}
}
