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
	HBITMAP oldbuffer;
	COLORREF Filter = RGB(255, 0, 255);

	oldbuffer = (HBITMAP)SelectObject(back, hImage);

	TransparentBlt(front, Pos.x, Pos.y, Sprite_Size.x , Sprite_Size.y,
		back, 0, 0, Sprite_Size.x, Sprite_Size.y, Filter);

	SelectObject(back, oldbuffer);
}
