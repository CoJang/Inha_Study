#include "stdafx.h"
#include "Tile.h"


Tile::Tile()
{
	Pos = { -1, -1 };
	Pivot = { 0, 0 };
}


Tile::~Tile()
{
}

void Tile::Init(wstring path, POINT pos, POINT pivot)
{
	hImage = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hImage, sizeof(BITMAP), &bitImage);

	Sprite_Size.x = bitImage.bmWidth;
	Sprite_Size.y = bitImage.bmHeight;

	Pivot = pivot;
	Pos = pos;
	Pos.x -= Pivot.x;
	Pos.y -= Pivot.y;
}

void Tile::Init(POINT pos, POINT pivot)
{
	Pivot = pivot;
	Pos = pos;
	Pos.x -= Pivot.x; 
	Pos.y -= Pivot.y;
}

void Tile::SetImage(HBITMAP & image, BITMAP & bitmap)
{
	hImage = image;
	bitImage = bitmap;
	Sprite_Size.x = bitImage.bmWidth;
	Sprite_Size.y = bitImage.bmHeight;
}

void Tile::Render(HDC front, HDC back)
{
	HBITMAP oldbuffer = (HBITMAP)SelectObject(back, hImage);

	TransparentBlt(front, Pos.x, Pos.y, Sprite_Size.x, Sprite_Size.y,
		back, 0, 0, Sprite_Size.x, Sprite_Size.y, FILTER);

	SelectObject(back, oldbuffer);
	DeleteObject(oldbuffer);
}
