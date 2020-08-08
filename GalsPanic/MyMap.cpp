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
			Tiles[x + (y * MapSize.x)].state = NOT_FILLED;
			Tiles[x + (y * MapSize.x)].IsChecked = false;
			Tiles[x + (y * MapSize.x)].color = NOTFILL;
			Tiles[x + (y * MapSize.x)].Rgn = {  Tiles[x + (y * MapSize.x)].Pos.x - TILESIZE / 2,
												Tiles[x + (y * MapSize.x)].Pos.y - TILESIZE / 2,
												Tiles[x + (y * MapSize.x)].Pos.x + TILESIZE / 2,
												Tiles[x + (y * MapSize.x)].Pos.y + TILESIZE / 2 };
		}

	StartEnd[0] = { -1, -1 };
	StartEnd[1] = { -1, -1 };
	Min = { -1, -1 }; Max = { -1, -1 };

	RECT StartRegion = { 250, 250, 350, 350 };
	SetPixelsRgn(FILL, FILLED, StartRegion);

	SaveVertex({ StartRegion.left,   StartRegion.top });
	SaveVertex({ StartRegion.right,  StartRegion.top });
	SaveVertex({ StartRegion.right,  StartRegion.bottom });
	SaveVertex({ StartRegion.left,   StartRegion.bottom });
}

MyMap::~MyMap()
{
	delete[] Tiles;
}

void MyMap::SaveVertex(POINT pos)
{
	pos.x /= TILESIZE;
	pos.y /= TILESIZE;

	VertexContainer.push_back(pos);
}

TileState MyMap::GetMapTileState(POINT pos)
{
	pos.x /= TILESIZE;
	pos.y /= TILESIZE;

	return Tiles[pos.x + (pos.y * MapSize.x)].state;
}

void MyMap::SetMapTileState(POINT pos, TileState input)
{
	pos.x /= TILESIZE;
	pos.y /= TILESIZE;

	if(Tiles[pos.x + (pos.y * MapSize.x)].state != FILLED)
		Tiles[pos.x + (pos.y * MapSize.x)].state = input;

	CheckTileState(pos);
}

COLORREF MyMap::GetMapTileColor(POINT pos)
{
	pos.x /= TILESIZE;
	pos.y /= TILESIZE;

	return Tiles[pos.x + (pos.y * MapSize.x)].color;
}

void MyMap::SetMapTileColor(POINT pos, COLORREF input)
{
	pos.x /= TILESIZE;
	pos.y /= TILESIZE;

	if (Tiles[pos.x + (pos.y * MapSize.x)].state != FILLED)
		Tiles[pos.x + (pos.y * MapSize.x)].color = input;
}

void MyMap::SetPixelsRgn(COLORREF color, TileState state, RECT Rgn)
{
	for (int y = Rgn.top; y < Rgn.bottom; y++)
		for (int x = Rgn.left; x < Rgn.right; x++)
		{
			SetMapTileColor({ x, y }, color);
			SetMapTileState({ x, y }, state);
		}
}

void MyMap::Render(HDC front, HDC back)
{
	for (int y = 0; y < MapSize.y; y++)
		for (int x = 0; x < MapSize.x; x++)
			Tiles[x + (y * MapSize.x)].Render(front, back);
}

void MapTile::Render(HDC front, HDC back)
{
	if (state == NOT_FILLED) return;

	hBrush = CreateSolidBrush(color);
	hPen = CreatePen(PS_INSIDEFRAME | PS_NULL, 0, color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(back, hBrush);
	HPEN oldPen = (HPEN)SelectObject(back, hPen);

	Rectangle(back, Rgn.left, Rgn.top, Rgn.right, Rgn.bottom);

	SelectObject(back, oldBrush);
	DeleteObject(oldBrush);

	SelectObject(back, oldPen);
	DeleteObject(oldPen);

	DeleteObject(hBrush);
	DeleteObject(hPen);
}
// Position, SrcState, destColor, destState
void MyMap::NonRecursiveFloodFill(POINT pos, TileState SrcState, COLORREF Color, TileState destState)
{
	if (pos.x < 0 || pos.y < 0 ||
		pos.x >= MapSize.x || pos.y >= MapSize.y) return;

	FloodFillContainer.push(pos);

	while (FloodFillContainer.size() > 0)
	{
		POINT p = FloodFillContainer.top();
		FloodFillContainer.pop();
		int x = p.x; int y = p.y;

		if (Tiles[x + (y * MapSize.x)].IsChecked) continue;
		if (x < 0 || y < 0 || x >= MapSize.x || y >= MapSize.y) continue;

		if (Tiles[x + (y * MapSize.x)].state == SrcState ||
			Tiles[x + (y * MapSize.x)].state == FILLED)
		{
			Tiles[x + (y * MapSize.x)].color = Color;
			Tiles[x + (y * MapSize.x)].state = destState;
			Tiles[x + (y * MapSize.x)].IsChecked = true;

			FloodFillContainer.push({x + 1, y});
			FloodFillContainer.push({x, y + 1});
			FloodFillContainer.push({x - 1, y});
			FloodFillContainer.push({x, y - 1});
		}
	}
}

void MyMap::CheckTileState(POINT pos)
{
	if (Tiles[pos.x + (pos.y * MapSize.x)].state == TEMP_FILLED)
	{
		if (TempFillContainer.empty())
			TempFillContainer.push_back({ pos.x, pos.y });

		bool IsNotExist = true; // To avoid Overlapping(Duplication)
		for (int i = 0; i < TempFillContainer.size(); i++)
		{
			if (TempFillContainer[i].x == pos.x && TempFillContainer[i].y == pos.y)
				IsNotExist = false;
		}

		if (IsNotExist)
			TempFillContainer.push_back({ pos.x, pos.y });
	}
	else if (Tiles[pos.x + (pos.y * MapSize.x)].state == FILLED)
	{
		if (StartEnd[0].x == -1)
		{
			StartEnd[0] = pos;
		}
		else if (StartEnd[1].x == -1)
		{
			StartEnd[1] = { pos.x, pos.y };
			FillRegion();
		}
	}
}

void MyMap::FillRegion()
{
	if (TempFillContainer.size() > 1)
	{
		POINT tempPos = TempFillContainer[1];
		
		// Fill Line
		NonRecursiveFloodFill(tempPos, TEMP_FILLED, FILL, FILLED);

		Min = GetVertex(0);
		Min.x -= 25; Min.y -= 25;
		Max = GetVertex(1);
		Max.x += 25; Max.y += 25;

		FillRectLine(Min, Max, RECT_REGION);

		// Fill Rectangle's inner
		NonRecursiveFloodFill({ (Min.x + 10) / TILESIZE, (Min.y + 10) / TILESIZE }, 
								 NOT_FILLED,	RGB(125, 125, 125), RECT_REGION);
		CheckRegion(Min, Max);

		TempFillContainer.clear();
		UnCheckAll();
	}

	StartEnd[0] = { -1, -1 };
	StartEnd[1] = { -1, -1 };
}

// Make Temporary Rectangle
void MyMap::FillRectLine(POINT Min, POINT Max, TileState state)
{
	Min.x /= TILESIZE; Min.y /= TILESIZE;
	Max.x /= TILESIZE; Max.y /= TILESIZE;

	COLORREF Color = RGB(125, 125, 125);

	for (int x = Min.x; x <= Max.x; x++)
	{
		Tiles[x + (Min.y * MapSize.x)].color = Color;
		Tiles[x + (Min.y * MapSize.x)].state = state;

		Tiles[x + (Max.y * MapSize.x)].color = Color;
		Tiles[x + (Max.y * MapSize.x)].state = state;
	}

	for (int y = Min.y; y <= Max.y; y++)
	{
		Tiles[Min.x + (y * MapSize.x)].color = Color;
		Tiles[Min.x + (y * MapSize.x)].state = state;

		Tiles[Max.x + (y * MapSize.x)].color = Color;
		Tiles[Max.x + (y * MapSize.x)].state = state;
	}
}

// Reverse Color & Tile State
void MyMap::CheckRegion(POINT Min, POINT Max)
{
	Min.x /= TILESIZE; Min.y /= TILESIZE;
	Max.x /= TILESIZE; Max.y /= TILESIZE;

	for (int y = Min.y; y <= Max.y; y++)
		for (int x = Min.x; x <= Max.x; x++)
		{
			if (Tiles[x + (y * MapSize.x)].state == RECT_REGION)
			{
				Tiles[x + (y * MapSize.x)].color = NOTFILL;
				Tiles[x + (y * MapSize.x)].state = NOT_FILLED;
			}

			else if (Tiles[x + (y * MapSize.x)].state != RECT_REGION)
			{
				Tiles[x + (y * MapSize.x)].color = FILL;
				Tiles[x + (y * MapSize.x)].state = FILLED;
			}
		}
}

// flag 0 : Min
// flag 1 : Max
// return Real-Position [ Not a Index ]
POINT MyMap::GetVertex(int flag)
{
	if (VertexContainer.empty()) return{ -1, -1 };

	if (flag == 0)
	{
		POINT Min = { WIN_WIDTH, WIN_HEIGHT };
		for (POINT i : VertexContainer)
		{
			if (Min.x > Tiles[i.x + (i.y * MapSize.x)].Pos.x)
				Min.x = Tiles[i.x + (i.y * MapSize.x)].Pos.x;
			if (Min.y > Tiles[i.x + (i.y * MapSize.x)].Pos.y)
				Min.y = Tiles[i.x + (i.y * MapSize.x)].Pos.y;
		}
		return Min;
	}
	else //if(flag == 1)
	{
		POINT Max = { -1, -1 };
		for (POINT i : VertexContainer)
		{
			if (Max.x < Tiles[i.x + (i.y * MapSize.x)].Pos.x)
				Max.x = Tiles[i.x + (i.y * MapSize.x)].Pos.x;
			if (Max.y < Tiles[i.x + (i.y * MapSize.x)].Pos.y)
				Max.y = Tiles[i.x + (i.y * MapSize.x)].Pos.y;
		}
		return Max;
	}
}

void MyMap::UnCheckAll()
{
	for (int y = 0; y < MapSize.y; y++)
		for (int x = 0; x < MapSize.x; x++)
			Tiles[x + (y * MapSize.x)].IsChecked = false;
}


