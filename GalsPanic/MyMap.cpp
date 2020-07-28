#include "stdafx.h"
#include "MyMap.h"

MyMap::MyMap()
{
	for (int i = 0; i < WIN_HEIGHT; i++)
		for (int j = 0; j < WIN_WIDTH; j++)
		{
			Tiles[i][j].Pos = { j , i };
			Tiles[i][j].state = NOT_FILLED;
			Tiles[i][j].color = RGB(255, 255, 255);
			Tiles[i][j].Prevcolor = RGB(255, 255, 255);
		}

	Tile = CreateBitmap(WIN_WIDTH, WIN_HEIGHT, 1, 32, NULL);
	p_pattern = new unsigned int[WIN_WIDTH * WIN_HEIGHT];

	for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
		*(p_pattern + i) = RGB(255, 255, 255);
}

MyMap::~MyMap()
{
	delete[] p_pattern;
}

void MyMap::Render(HDC front, HDC back)
{
	for (int i = 0; i < WIN_HEIGHT; i++)
		for (int j = 0; j < WIN_WIDTH; j++)
			*(p_pattern + (j + (i * WIN_WIDTH))) = Tiles[i][j].color;
			//switch (Tiles[i][j].state)
			//{
			//case FILLED :
			//	*(p_pattern + (j + (i * WIN_WIDTH))) = Tiles[i][j].color;
			//	break;
			//case NOT_FILLED:
			//	*(p_pattern + (j + (i * WIN_WIDTH))) = Tiles[i][j].color;
			//	break;
			//case TEMP_FILLED:
			//	*(p_pattern + (j + (i * WIN_WIDTH))) = Tiles[i][j].color;
			//	break;
			//}

	HBITMAP oldBitmap = (HBITMAP)SelectObject(back, Tile);
	SetBitmapBits(Tile, WIN_WIDTH * WIN_HEIGHT * 4, p_pattern);
	//BitBlt(front, 0, 0, WIN_WIDTH, WIN_HEIGHT, back, 0, 0, SRCCOPY);
	COLORREF Filter = RGB(0, 0, 0);
	TransparentBlt(front, 0, 0, WIN_WIDTH, WIN_HEIGHT, back, 0, 0, WIN_WIDTH, WIN_HEIGHT, Filter);
	(HBITMAP)SelectObject(back, oldBitmap);
}

void MyMap::Update()
{
}
