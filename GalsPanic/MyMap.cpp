#include "stdafx.h"
#include "MyMap.h"

MyMap::MyMap()
{
	for (int i = 0; i < WIN_HEIGHT; i++)
		for (int j = 0; j < WIN_WIDTH; j++)
		{
			Tiles[i][j].Pos = { j , i };
			Tiles[i][j].state = NOT_FILLED;
			Tiles[i][j].color = RGB(0, 255, 0);
		}
}

void MyMap::Render(HDC front, HDC back)
{
	//FillRect(), SetBitmapBits()

	for (int i = 0; i < WIN_HEIGHT; i++)
		for (int j = 0; j < WIN_WIDTH; j++)
			switch (Tiles[i][j].state)
			{
			case FILLED :
				SetPixel(front, j, i, Tiles[i][j].color);
				break;
			case NOT_FILLED:
				break;
			case TEMP_FILLED:
				SetPixel(front, j, i, Tiles[i][j].color);
				break;
			}
}

void MyMap::Update()
{
}
