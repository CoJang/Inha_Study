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
	oldDir = Dir;
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
	HBITMAP oldbuffer;
	COLORREF Filter = RGB(255, 0, 255);

	oldbuffer = (HBITMAP)SelectObject(back, hImage);

	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;

	TransparentBlt(front, Pos.x, Pos.y, Sprite_Size.x * CharSize, Sprite_Size.y * CharSize,
		back, Start.x, Start.y, Sprite_Size.x, Sprite_Size.y, Filter);

	SelectObject(back, oldbuffer);
	DeleteObject(oldbuffer);
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
	if (Pos.y > WIN_HEIGHT - 70)
		Pos.y = WIN_HEIGHT - 70;
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
		if (oldDir.x != Dir.x || oldDir.y != Dir.y)
		{
			SetPixel(TEMP_FILLED, 0x000000FF);

		}
		else
		{
			SetPixel(TEMP_FILLED, TEMPFILL);
		}
	}

	oldDir = Dir;
}
void Player::SetPixelsRgn(TileState state, COLORREF color, RECT Region)
{
	for (int y = Region.top; y < Region.bottom; y++)
		for (int x = Region.left; x < Region.right; x++)
		{
			map->SetMapTileColor({ x, y }, color);
			map->SetMapTileState({ x, y }, state);
		}
}

void Player::SetPixel(TileState state, COLORREF color)
{
	POINT Pivot = {33, 60};
	map->SetMapTileColor({ Pos.x + Pivot.x, Pos.y + Pivot.y }, color);
	map->SetMapTileState({ Pos.x + Pivot.x, Pos.y + Pivot.y }, state);
}


