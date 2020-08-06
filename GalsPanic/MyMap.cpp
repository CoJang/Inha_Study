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
												Tiles[x + (y * MapSize.x)].Pos.y + TILESIZE / 2};
		}

	StartEnd[0] = { -1, -1 };
	StartEnd[1] = { -1, -1 };
}

MyMap::~MyMap()
{
	delete[] Tiles;
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

void MyMap::FloodFill(POINT pos, TileState check)
{
	if (pos.x < 0 || pos.y < 0 ||
		pos.x >= MapSize.x || pos.y >= MapSize.y ) return;

	if (Tiles[pos.x + (pos.y * MapSize.x)].state == check)
	{
		Tiles[pos.x + (pos.y * MapSize.x)].color = FILL;
		Tiles[pos.x + (pos.y * MapSize.x)].state = FILLED;
		FilledContainer.push_back(pos);

		FloodFill({ pos.x + 1, pos.y }, check);
		FloodFill({ pos.x, pos.y + 1 }, check);
		FloodFill({ pos.x - 1, pos.y }, check);
		FloodFill({ pos.x, pos.y - 1 }, check);
	}
}

void MyMap::NonRecursiveFloodFill(POINT pos, TileState check)
{
	if (pos.x < 0 || pos.y < 0 ||
		pos.x >= MapSize.x || pos.y >= MapSize.y) return;

	FloodFillContainer.push(pos);

	while (FloodFillContainer.size() > 0)
	{
		POINT p = FloodFillContainer.top();
		FloodFillContainer.pop();
		int x = p.x;
		int y = p.y;

		if (Tiles[x + (y * MapSize.x)].IsChecked) continue;
		if (x < 0 || y < 0 || x >= MapSize.x || y >= MapSize.y) continue;

		if (Tiles[x + (y * MapSize.x)].state == check ||
			Tiles[x + (y * MapSize.x)].state == FILLED)
		{
			Tiles[x + (y * MapSize.x)].color = FILL;
			Tiles[x + (y * MapSize.x)].state = FILLED;
			Tiles[x + (y * MapSize.x)].IsChecked = true;
			FilledContainer.push_back({x, y});

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

		bool IsNotExist = true; // For avoid Overlapping(Duplication)
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
			FillLine();
		}

		if (FilledContainer.empty())
			FilledContainer.push_back({ pos.x, pos.y });

		bool IsNotExist = true; 
		for (int i = 0; i < FilledContainer.size(); i++)
		{
			if (FilledContainer[i].x == pos.x && FilledContainer[i].y == pos.y)
				IsNotExist = false;
		}

		if (IsNotExist)
			FilledContainer.push_back({ pos.x, pos.y });
	}
}

void MyMap::FillLine()
{
	if (!TempFillContainer.empty())
	{
		int halfPoint = TempFillContainer.size() / 2;
		POINT tempPos = TempFillContainer[1];

		string str;
		DWORD dwWrite;
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		
		// Fill Line
		NonRecursiveFloodFill(tempPos, TEMP_FILLED);

		if (IsIn({ tempPos.x + 1, tempPos.y + 1 }, FILLED))
		{
			NonRecursiveFloodFill({ tempPos.x + 1, tempPos.y + 1 }, NOT_FILLED);
		}
		else if (IsIn({ tempPos.x + 1, tempPos.y - 1 }, FILLED))
		{
			NonRecursiveFloodFill({ tempPos.x + 1, tempPos.y - 1 }, NOT_FILLED);
		}
		else if (IsIn({ tempPos.x - 1, tempPos.y + 1 }, FILLED))
		{
			NonRecursiveFloodFill({ tempPos.x - 1, tempPos.y + 1 }, NOT_FILLED);
		}
		else if (IsIn({ tempPos.x - 1, tempPos.y - 1 }, FILLED))
		{
			NonRecursiveFloodFill({ tempPos.x - 1, tempPos.y - 1 }, NOT_FILLED);
		}


		TempFillContainer.clear();
		UnCheckAll();
	}

	StartEnd[0] = { -1, -1 };
	StartEnd[1] = { -1, -1 };
}

bool MyMap::IsIn(POINT pos, TileState check)
{
	//if(Tiles[pos.x + (pos.y * MapSize.x)].state == FILLED) return false;

	int MeetCnt = 0;
	bool IsMeet = false;
	POINT First, Last;
	First = { -1, -1 }; Last = { -1, -1 };

	for (int x = pos.x; x < MapSize.x; x++)
	{
		if (x + 1 < MapSize.x && IsMeet &&
			Tiles[(x + 1) + (pos.y * MapSize.x)].state != check)
		{
			IsMeet = false;
		}
		if (Tiles[x + (pos.y * MapSize.x)].state == check && !IsMeet)
		{
			MeetCnt++;
			IsMeet = true;

			if (First.x == -1 && Tiles[(x - 1) + (pos.y * MapSize.x)].state != check)
				First = { x, pos.y };
			else if (Last.x == -1)
				Last = { x, pos.y };
		}
	}

	if (First.x == Last.x && First.y == Last.y && First.x != -1)
		MeetCnt--;

	if (MeetCnt % 2 == 0)
		return false;
	else
		return true;

}

void MyMap::UnCheckAll()
{
	for (int y = 0; y < MapSize.y; y++)
		for (int x = 0; x < MapSize.x; x++)
			Tiles[x + (y * MapSize.x)].IsChecked = false;
}


void MyMap::CheckFilled()
{
	if (TempFillContainer.empty()) return;

	int Min = MapSize.x; int Max = -1;

	for (int y = 0; y < MapSize.y; y++)
	{
		for (int x = 0; x < MapSize.x; x++)
		{
			MapTile TempTile = Tiles[x + (y * MapSize.x)];
			if (TempTile.state == TEMP_FILLED && x < Min)
				Min = x;
			else if ((TempTile.state == TEMP_FILLED && x > Max))
				Max = x;
		}

		for (int x = Min; x < Max; x++)
		{
			if (Tiles[x + (y * MapSize.x)].state == NOT_FILLED)
			{
				Tiles[x + (y * MapSize.x)].color = FILL;
				Tiles[x + (y * MapSize.x)].state = FILLED;
				FilledContainer.push_back({ x, y });
			}
		}

		Min = MapSize.x; Max = -1;
	}

	Min = MapSize.y; Max = -1;

	for (int x = 0; x < MapSize.x; x++)
	{
		for (int y = 0; y < MapSize.y; y++)
		{
			MapTile TempTile = Tiles[x + (y * MapSize.x)];
			if (TempTile.state == TEMP_FILLED && y < Min)
				Min = y;
			else if ((TempTile.state == TEMP_FILLED && y > Max))
				Max = y;
		}

		for (int y = Min; y < Max; y++)
		{
			if (Tiles[x + (y * MapSize.x)].state == NOT_FILLED)
			{
				Tiles[x + (y * MapSize.x)].color = FILL;
				Tiles[x + (y * MapSize.x)].state = FILLED;
				FilledContainer.push_back({ x, y });
			}
		}

		Min = MapSize.y; Max = -1;
	}
}
