#include "stdafx.h"
#include "Tile.h"


Tile::Tile()
	:CostFromStart(0),
	 CostToDist(-1),
	 TotalCost(-1),
	 Pos({0, 0}),
	 Parents({-1, -1}),
	 color(RGB(255, 255, 255)),
	 IsObstacle(false){}

Tile::~Tile(){}

void Tile::Render(HDC hdc)
{
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	Rectangle(hdc, Pos.x - TILE_SIZE / 2, Pos.y - TILE_SIZE / 2,
					Pos.x + TILE_SIZE / 2, Pos.y + TILE_SIZE / 2);

	SelectObject(hdc, oldBrush);
	DeleteObject(oldBrush);
	//DeleteObject(hBrush);
}

void Tile::CostRender(HDC hdc)
{
	static POINT Pivot = { 5, 18 };

	TextOut(hdc, Pos.x - Pivot.x - 12, Pos.y - Pivot.y,
			to_wstring(CostFromStart).c_str(), to_wstring(CostFromStart).size());

	TextOut(hdc, Pos.x + Pivot.x, Pos.y - Pivot.y, 
			to_wstring(CostToDist).c_str(),	to_wstring(CostToDist).size());

	TextOut(hdc, Pos.x - Pivot.x, Pos.y, 
			to_wstring(TotalCost).c_str(), to_wstring(TotalCost).size());
}

bool Tile::CheckClicked(POINT MousePos)
{
	if (MousePos.x >= Pos.x - (TILE_SIZE / 2) && MousePos.x <= Pos.x + (TILE_SIZE / 2) &&
		MousePos.y >= Pos.y - (TILE_SIZE / 2) && MousePos.y <= Pos.y + (TILE_SIZE / 2))
		return true;

	return false;
}

