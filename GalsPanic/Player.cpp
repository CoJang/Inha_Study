#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	Pos = { 0, 0 }; Dir = { 0, 0 }; Speed = 5;
	
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
}

Player::~Player()
{
}

void Player::Render(HDC hdc)
{
	if (prevPos.x != Pos.x || prevPos.y != Pos.y)
	{
		int PivotX = 33; int PivotY = 60; int r = 10;
		RECT tempRgn = { prevPos.x + PivotX - r, prevPos.y + PivotY - r, prevPos.x + PivotX + r, prevPos.y + PivotY + r };
		FootPrints.push_back(tempRgn);
	}
	for (int i = 0; i < FootPrints.size(); i++)
	{
		//SetRgnPixels(hdc, FootPrints[i], RGB(255, 0, 0));
		Rectangle(hdc, FootPrints[i].left, FootPrints[i].top, FootPrints[i].right, FootPrints[i].bottom);
	}

	HDC buffer;
	HBITMAP oldbuffer;
	COLORREF Filter = RGB(255, 0, 255);

	buffer = CreateCompatibleDC(hdc);
	oldbuffer = (HBITMAP)SelectObject(buffer, hImage);

	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;

	TransparentBlt(hdc, Pos.x, Pos.y, Sprite_Size.x * CharSize, Sprite_Size.y * CharSize,
		buffer, Start.x, Start.y, Sprite_Size.x, Sprite_Size.y, Filter);

	SelectObject(buffer, oldbuffer);
	DeleteDC(buffer);
}

void Player::SetRgnPixels(HDC hdc, RECT region, COLORREF color)
{
	for(int i = region.left; i <= region.right; i++)
		for(int j = region.top; j <= region.bottom; j++)
			SetPixel(hdc, i, j, color);
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
	prevPos = Pos;
	Pos.x = Pos.x + (Dir.x * Speed);
	Pos.y = Pos.y + (Dir.y * Speed);
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
		Dir.x = 0;
		Dir.y = 0;
	}
}
