#include "stdafx.h"
#include "MyMap.h"


MyMap::MyMap()
{
	Pos = { 100, 100 };
	POINT CharPos = { Pos.x + Grid_Dist / 2, Pos.y + Grid_Dist / 2 };
	MainChar = new Player(CharPos, Grid_Dist / 2);

	GridXNum = Grid_Width / Grid_Dist;
	GridYNum = Grid_Height / Grid_Dist;

	Tiles = new Tile[GridXNum * GridYNum];
	InitTiles();
	Tiles[45].SetColor(0x00000000);
	Tiles[45].SetState(FILLED);
	FilledContainer.push_back({ 4, 5 });
	Tiles[46].SetColor(0x00000000);
	Tiles[46].SetState(FILLED);
	FilledContainer.push_back({ 4, 6 });
	Tiles[55].SetColor(0x00000000);
	Tiles[55].SetState(FILLED);
	FilledContainer.push_back({ 5, 5 });
	Tiles[56].SetColor(0x00000000);
	Tiles[56].SetState(FILLED);
	FilledContainer.push_back({ 5, 6 });

	StartEnd[0] = { -1, 0 };
	StartEnd[1] = { -1, 0 };
}


MyMap::~MyMap()
{
	delete MainChar;
	delete[] Tiles;
}

void MyMap::Render(HDC hdc)
{
	DrawGrid(hdc);
	for(int i = 0; i < GridXNum * GridYNum; i++)
		Tiles[i].Render(hdc);

	MainChar->Render(hdc);
}

void MyMap::Update()
{
	MainChar->Update();

	for (int i = 0; i < GridXNum * GridYNum; i++)
		Tiles[i].Update();
}

void MyMap::CheckKeyDown()
{
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		MainChar->MoveChar({ -1, 0 }, Pos);
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		MainChar->MoveChar({ 0, 1 }, Pos);
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		MainChar->MoveChar({ 1, 0 }, Pos);
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		MainChar->MoveChar({ 0, -1 }, Pos);
	}
	else
	{
		MainChar->MoveChar({ 0, 0 }, Pos);
	}

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		POINT index;
		index.x = (MainChar->GetPos().x - Pos.x) / Grid_Dist;
		index.y = (MainChar->GetPos().y - Pos.y) / Grid_Dist;

		Tiles[index.x + (index.y * GridXNum)].SetColor(0x000000FF);
		Tiles[index.x + (index.y * GridXNum)].SetState(TEMP_FILLED);

		if (Tiles[index.x + (index.y * GridXNum)].GetState() == TEMP_FILLED)
		{
			if(TempFillContainer.empty())
				TempFillContainer.push_back({ index.x, index.y });

			bool IsNotExist = true;
			for (int i = 0; i < TempFillContainer.size(); i++)
			{
				if (TempFillContainer[i].x == index.x && TempFillContainer[i].y == index.y)
					IsNotExist = false;
			}

			if(IsNotExist)
				TempFillContainer.push_back({ index.x, index.y });
		}
		if (Tiles[index.x + (index.y * GridXNum)].GetState() == FILLED)
		{
			if (StartEnd[0].x == -1)
			{
				StartEnd[0] = index;
			}
			else if (StartEnd[1].x == -1)
			{
				StartEnd[1] = { index.x, index.y };
				FillLine();
			}
		}
	}
}

void MyMap::FillLine()
{
	for (POINT i : TempFillContainer)
	{
		Tiles[i.x + (i.y * GridXNum)].SetColor(0x00000000);
		Tiles[i.x + (i.y * GridXNum)].SetState(FILLED);
		FilledContainer.push_back(i);
	}
	TempFillContainer.clear();
	StartEnd[0] = { -1, 0 };
	StartEnd[1] = { -1, 0 };
	CheckFilled();
}

void MyMap::CheckFilled()
{ 
	int Min, Max;
	Min = 10; Max = -1;
	for (int y = 0; y < GridYNum; y++)
	{
		for (int x = 0; x < GridXNum; x++)
		{
			Tile TempTile = Tiles[x + (y * GridXNum)];
			if (TempTile.GetState() == FILLED && x < Min)
				Min = x;
			else if ((TempTile.GetState() == FILLED && x > Max))
				Max = x;
		}

		for (int x = Min; x < Max; x++)
		{
			Tiles[x + (y * GridXNum)].SetColor(0x00000000);
			Tiles[x + (y * GridXNum)].SetState(FILLED);
			FilledContainer.push_back({x, y});
		}

		Min = 10; Max = -1;
	}
}



void MyMap::DrawGrid(HDC hdc)
{
	for (int y = Pos.y; y <= Grid_Height + Pos.y; y += Grid_Dist)
		for (int x = Pos.x; x <= Grid_Width + Pos.x; x += Grid_Dist)
		{
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, Grid_Width, y);

			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, x, Grid_Height);
		}
}

void MyMap::InitTiles()
{
	for (int y = 0; y < GridYNum; y++)
	{
		for (int x = 0; x < GridXNum; x++)
		{
			POINT TilePos = { Pos.x + x * Grid_Dist + Grid_Dist / 2, 
							  Pos.y + y * Grid_Dist + Grid_Dist / 2 };
			(Tiles + (x + (y * GridXNum)))->SetTile(TilePos, 0x00FFFFFF, NOT_FILLED);
		}

	}
}

Tile::Tile()
{
	Pos = { 0, 0 };
	color = RGB(0, 0, 0);
	state = FILLED;
	Rgn = { Pos.x - Grid_Dist / 2, Pos.y - Grid_Dist / 2,
			Pos.x + Grid_Dist / 2, Pos.y + Grid_Dist / 2 };
}

void Tile::SetTile(POINT position, COLORREF col, TileState condition)
{
	Pos = position; color = col; state = condition;
	Rgn = { Pos.x - Grid_Dist / 2, Pos.y - Grid_Dist / 2,
			Pos.x + Grid_Dist / 2, Pos.y + Grid_Dist / 2};
}

void Tile::Update()
{
	if (state == NOT_FILLED) return;
}

void Tile::Render(HDC hdc)
{
	if (state == NOT_FILLED) return;

	HBRUSH hBrush;
	HBRUSH oldBrush;
	hBrush = CreateSolidBrush(color);
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	Rectangle(hdc, Rgn.left, Rgn.top, Rgn.right, Rgn.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}
