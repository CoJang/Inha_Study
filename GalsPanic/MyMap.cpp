#include "stdafx.h"
#include "MyMap.h"

MyMap::MyMap()
{
	MapSize.x = WIN_WIDTH / TILESIZE;
	MapSize.y = WIN_HEIGHT / TILESIZE;

	Tiles = new MapTile[MapSize.x * MapSize.y];

	for (int y = 0; y < MapSize.y; y++)
		for (int x = 0; x < MapSize.x; x++)
		{
			Tiles[x + (y * MapSize.x)].Pos = { x * TILESIZE + TILESIZE / 2, y * TILESIZE + TILESIZE / 2 };
			Tiles[x + (y * MapSize.x)].state = FILLED;
			Tiles[x + (y * MapSize.x)].color = 0x00FFFFFF;
			Tiles[x + (y * MapSize.x)].Rgn = {  Tiles[x + (y * MapSize.x)].Pos.x - TILESIZE / 2,
												Tiles[x + (y * MapSize.x)].Pos.y - TILESIZE / 2,
												Tiles[x + (y * MapSize.x)].Pos.x + TILESIZE / 2,
												Tiles[x + (y * MapSize.x)].Pos.y + TILESIZE / 2};
		}

	TileBitmap = CreateBitmap(WIN_WIDTH, WIN_HEIGHT, 1, 32, NULL);
}

MyMap::~MyMap()
{
	delete[] Tiles;
}

TileState MyMap::GetMapTileState(POINT pos)
{
	//if (pos.x >= MapSize.x || pos.y >= MapSize.y)
	//{
		pos.x /= TILESIZE;
		pos.y /= TILESIZE;
	//}

	return Tiles[pos.x + (pos.y * MapSize.x)].state;
}

void MyMap::SetMapTileState(POINT pos, TileState input)
{
	//if (pos.x >= MapSize.x || pos.y >= MapSize.y)
	//{
		pos.x /= TILESIZE;
		pos.y /= TILESIZE;
	//}

	Tiles[pos.x + (pos.y * MapSize.x)].state = input;
}

COLORREF MyMap::GetMapTileColor(POINT pos)
{
	//if (pos.x >= MapSize.x || pos.y >= MapSize.y)
	//{
		pos.x /= TILESIZE;
		pos.y /= TILESIZE;
	//}

	return Tiles[pos.x + (pos.y * MapSize.x)].color;
}

void MyMap::SetMapTileColor(POINT pos, COLORREF input)
{
	//if (pos.x >= MapSize.x || pos.y >= MapSize.y)
	//{
		pos.x /= TILESIZE;
		pos.y /= TILESIZE;
	//}

	Tiles[pos.x + (pos.y * MapSize.x)].color = input;
}

void MyMap::Render(HDC front, HDC back)
{
	for (int y = 0; y < MapSize.y; y++)
	{
		for (int x = 0; x < MapSize.x; x++)
		{
			//unsigned int* pattern = new unsigned int[100];
			Tiles[x + (y * MapSize.x)].Render(front, back);
			//SetBitmapBits(TileBitmap, 100 * 4, pattern);
			//delete pattern;
		}
	}
	
	COLORREF Filter = 0x00000000;
	HBITMAP oldBitmap = (HBITMAP)SelectObject(back, TileBitmap);
	TransparentBlt(front, 0, 0, WIN_WIDTH, WIN_HEIGHT, back, 0, 0, WIN_WIDTH, WIN_HEIGHT, Filter);
	(HBITMAP)SelectObject(back, oldBitmap);
}

void MyMap::Update()
{
}

void MapTile::Render(HDC front, HDC back)
{
	if (state == NOT_FILLED) return;

	hBrush = CreateSolidBrush(color);
	hPen = CreatePen(PS_INSIDEFRAME | PS_NULL, 0, color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(front, hBrush);
	HPEN oldPen = (HPEN)SelectObject(front, hPen);

	Rectangle(front, Rgn.left, Rgn.top, Rgn.right, Rgn.bottom);

	SelectObject(front, oldBrush);
	SelectObject(front, oldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}
