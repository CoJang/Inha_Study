#include "stdafx.h"
#include "Objects.h"

ImageObject::ImageObject()
{
	Pos = { 0, 0 }; Dir = { 0, 0 };

	ImagePath = TEXT("images/¼öÁö.bmp");
	hImage = (HBITMAP)LoadImage(NULL, ImagePath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
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
		temp, 0, 0, Sprite_Size.x, Sprite_Size.y, RGB(0, 123, 0));

	SelectObject(temp, oldbuffer);
	DeleteObject(oldbuffer);
	DeleteDC(temp);
}
