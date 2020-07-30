#pragma once
#include "stdafx.h"
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
	
	void Update();
	void Render(HDC hdc);
	void SetTile(POINT position, COLORREF col, TileState condition);
	void SetColor(COLORREF col) { if (state != FILLED) color = col; };
	void SetState(TileState condition) { if(state != FILLED) state = condition; };
	TileState GetState() { return state; };
	COLORREF GetColor() { return color; };
};



class MyMap
{
private:
	POINT Pos;
	Tile* Tiles;
	Player* MainChar;

	int GridXNum;
	int GridYNum;

	vector<POINT> TempFillContainer;
	vector<POINT> FilledContainer;
	POINT StartEnd[2];
public:
	MyMap();
	~MyMap();

	void InitTiles();

	void Update();
	void FillLine();
	void CheckFilled();
	void CheckKeyDown();
	void Render(HDC hdc);
	void DrawGrid(HDC hdc);
};

