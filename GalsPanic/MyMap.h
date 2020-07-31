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
public:
	MyMap();
	~MyMap();

	TileState GetMapTileState(POINT pos);
	void SetMapTileState(POINT pos, TileState input);

	COLORREF GetMapTileColor(POINT pos);
	void SetMapTileColor(POINT pos, COLORREF input);

	void Render(HDC front, HDC back);
	void Update();
};

