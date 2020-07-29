#pragma once
#include "Player.h"

enum TileState
{
	FILLED,
	NOT_FILLED,
	TEMP_FILLED
};

class Tile
{
private:
	POINT Pos;
	COLORREF color;
	TileState state;

	RECT Rgn;
public:
	Tile();
	~Tile() {};

	
	void SetTile(POINT position, COLORREF col, TileState condition);
	void SetColor(COLORREF col) { color = col; };
	void SetState(TileState condition) { state = condition; };
	void Update();
	void Render(HDC hdc);
};



class MyMap
{
private:
	POINT Pos;
	Tile* Tiles;
	Player* MainChar;

	int GridXNum;
	int GridYNum;
public:
	MyMap();
	~MyMap();

	void InitTiles();

	void Update();
	void Render(HDC hdc);
	void DrawGrid(HDC hdc);
	void CheckKeyDown();
};

