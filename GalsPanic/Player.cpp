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
}

Player::~Player(){}

void Player::InitPlayer(MyMap * input)
{
	map = input;
	RECT temp = { 250, 250, 350, 350 };
	SetPixelsRgn(FILLED, RGB(0, 0, 0), temp);
}

void Player::Render(HDC front, HDC back)
{
	//bool IsMeet = false;
	//int index = -1;
	//for (int i = 0; i < Max_Print; i++)
	//	if (FootPrints[i].IsActived())
	//	{
	//		if (FootPrints[i].SetPixelsRgn(map, TEMP_FILLED, 0xFFFF0000))
	//		{
	//			IsMeet = true;
	//			index = i;
	//		}
	//	}

	//if (IsMeet)
	//	for (int i = 0; i < index; i++)
	//		FootPrints[i].SetPixelsRgn(map, FILLED, 0x00000000);

	//if (prevPos.x + PrintDist < Pos.x || prevPos.x - PrintDist > Pos.x ||
	//	prevPos.y + PrintDist < Pos.y || prevPos.y - PrintDist > Pos.y)
	//{
	//	for (int i = 0; i < Max_Print; i++)
	//	{
	//		if (!FootPrints[i].IsActived())
	//		{
	//			FootPrints[i].SetState(true);
	//			FootPrints[i].SetPos(prevPos);
	//			break;
	//		}
	//	}
	//}

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

	Pos.x = Pos.x + (Dir.x * Speed);
	Pos.y = Pos.y + (Dir.y * Speed);

	if (Pos.x < 0) Pos.x = 0;
	if (Pos.x > WIN_WIDTH - 50)
		Pos.x = WIN_WIDTH - 50;
	if (Pos.y < 0) Pos.y = 0;
	if (Pos.y > WIN_HEIGHT - 80)
		Pos.y = WIN_HEIGHT - 80;
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

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		SetPixel(FILLED, 0x00000000);
	}
}
void Player::SetPixelsRgn(TileState state, COLORREF color, RECT Region)
{
	for (int y = Region.top; y < Region.bottom; y++)
		for (int x = Region.left; x < Region.right; x++)
		{
			map->SetMapTileState({ x, y }, state);
			map->SetMapTileColor({ x, y }, color);
		}
}

void Player::SetPixel(TileState state, COLORREF color)
{
	POINT Pivot = {33, 60};
	map->SetMapTileState({ Pos.x + Pivot.x, Pos.y + Pivot.y }, state);
	map->SetMapTileColor({ Pos.x + Pivot.x, Pos.y + Pivot.y }, color);
}


