#pragma once

enum TileState
{
	FILLED,
	NOT_FILLED,
	TEMP_FILLED
};

struct MapTile
{
	TileState state;
	POINT Pos;
	COLORREF color;
};

class MyMap
{
private:
	// WIN_HEIGHT : 800, WIN_WIDTH : 450
	MapTile Tiles[WIN_HEIGHT][450];
	unsigned int* p_pattern;
	HBITMAP Tile;
public:
	MyMap();
	~MyMap();

	TileState GetMapTileState(POINT pos) { return Tiles[pos.y][pos.x].state; }
	void SetMapTileState(POINT pos, TileState input) { Tiles[pos.y][pos.x].state = input; };

	COLORREF GetMapTileColor(POINT pos) { return Tiles[pos.y][pos.x].color; }
	void SetMapTileColor(POINT pos, COLORREF input) { Tiles[pos.y][pos.x].color = input; };

	void Render(HDC front, HDC back);
	void Update();
};

