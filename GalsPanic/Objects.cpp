#include "stdafx.h"
#include "Objects.h"

ImageObject::ImageObject()
{
	Dir = { 0, 0 };
	Pos = { 0, 0 };
}

void ImageObject::InitImageObject(wstring Path, POINT pos)
{
	ImagePath = Path;
	Pos = pos;
	hImage = (HBITMAP)LoadImage(NULL, ImagePath.c_str(), IMAGE_BITMAP, 
				WIN_WIDTH - 50, WIN_HEIGHT - 50, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hImage, sizeof(BITMAP), &bitImage);

	Sprite_Size.x = bitImage.bmWidth;
	Sprite_Size.y = bitImage.bmHeight;
	
}

void ImageObject::Update()
{
}

void ImageObject::Render(HDC front, HDC back)
{
	HDC temp = CreateCompatibleDC(back);
	HBITMAP oldbuffer = (HBITMAP)SelectObject(back, hImage);

	TransparentBlt(back, Pos.x, Pos.y, Sprite_Size.x , Sprite_Size.y,
		temp, Pos.x, Pos.y, Sprite_Size.x, Sprite_Size.y, RGB(0, 123, 0));

	SelectObject(temp, oldbuffer);
	DeleteObject(oldbuffer);
	DeleteDC(temp);
}
