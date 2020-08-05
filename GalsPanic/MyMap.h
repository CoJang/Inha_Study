#pragma once

enum TileState
{
	FILLED,
	NOT_FILLED,
	TEMP_FILLED
};

class MapTile
{
public:
	POINT Pos;
	COLORREF color;
	TileState state;
	bool IsChecked;

	RECT Rgn;
	HPEN hPen;
	HBRUSH hBrush;
public:
	MapTile() {};
	~MapTile() {};

	void Render(HDC front, HDC back);
};

class MyMap
{
private:
	MapTile* Tiles;
	POINT MapSize;

	vector<POINT> TempFillContainer;
	vector<POINT> FilledContainer;
	stack<POINT> FloodFillContainer;
	POINT StartEnd[2];
public:
	MyMap();
	~MyMap();

	TileState GetMapTileState(POINT pos);
	void SetMapTileState(POINT pos, TileState input);

	COLORREF GetMapTileColor(POINT pos);
	void SetMapTileColor(POINT pos, COLORREF input);

	void Render(HDC front, HDC back);
	void Update() {};

	// Color Fill Func.
	void FloodFill(POINT pos, TileState check);
	void NonRecursiveFloodFill(POINT pos, TileState check);
	void CheckTileState(POINT pos);
	void CheckFilled();
	void FillLine();

	bool IsIn(POINT pos, TileState check);
	void UnCheckAll();
};

