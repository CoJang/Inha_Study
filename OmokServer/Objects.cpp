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
				0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hImage, sizeof(BITMAP), &bitImage);

	Sprite_Size.x = bitImage.bmWidth;
	Sprite_Size.y = bitImage.bmHeight;
}

void ImageObject::Update()
{
}

void ImageObject::Render(HDC front, HDC back)
{
	HBITMAP oldbuffer = (HBITMAP)SelectObject(back, hImage);

	TransparentBlt(front, Pos.x, Pos.y, Sprite_Size.x , Sprite_Size.y,
		back, Pos.x, Pos.y, Sprite_Size.x, Sprite_Size.y, RGB(0, 255, 255));

	SelectObject(back, oldbuffer);
	DeleteObject(oldbuffer);
}
