#pragma once

class Tile
{
public:
	int CostFromStart;	// g value
	int CostToDist;		// h value
	int TotalCost;		// f value

	POINT Pos;
	bool IsObstacle;
	COLORREF color;
	POINT Parents;
public:
	Tile();
	~Tile();

	void Render(HDC hdc);
	void CostRender(HDC hdc);
	bool CheckClicked(POINT MousePos);
	void UpdateF() { TotalCost = CostToDist + CostFromStart; };
};

