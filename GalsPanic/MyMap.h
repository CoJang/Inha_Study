#pragma once

enum TileState
{
	FILLED,
	NOT_FILLED,
	TEMP_FILLED,
	RECT_REGION
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
	stack<POINT> FloodFillContainer;
	POINT StartEnd[2];

	// Use This
	vector<POINT> VertexContainer;
	vector<POINT> TempVertexContainer;
	POINT Min, Max;
public:
	MyMap();
	~MyMap();

	void SaveVertex(POINT pos);

	TileState GetMapTileState(POINT pos);
	void SetMapTileState(POINT pos, TileState input);

	COLORREF GetMapTileColor(POINT pos);
	void SetMapTileColor(POINT pos, COLORREF input);
	void SetPixelsRgn(COLORREF color, TileState state, RECT Rgn);

	void Render(HDC front, HDC back);
	void Update() {};

	// Color Fill Func.
	void NonRecursiveFloodFill(POINT, TileState, COLORREF, TileState);
	void FillRectLine(POINT Min, POINT Max, TileState state);
	void CheckRegion(POINT Min, POINT Max);
	void CheckTileState(POINT pos);
	void FillLine();

	POINT GetVertex(int flag);
	void UnCheckAll();
};

