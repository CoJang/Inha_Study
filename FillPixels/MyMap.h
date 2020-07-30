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

class ImageObject
{
	wstring ImagePath;
	HBITMAP hImage;
	BITMAP bitImage;

	POINT Dir;
	POINT Pos;
	POINT Sprite_Size;
public:
	ImageObject();
	~ImageObject() {};

	void Update();
	void Render(HDC hdc);
};

class MyMap
{
private:
	POINT Pos;
	Tile* Tiles;
	Player* MainChar;
	ImageObject* Suzy;

	int GridXNum;
	int GridYNum;

	vector<POINT> TempFillContainer;
	vector<POINT> FilledContainer;
	POINT StartEnd[2];

	HDC* hdc, *front, *Back;
	HBITMAP BackBitmap;
public:
	MyMap();
	~MyMap();

	void InitMap(HDC* _hdc, HDC* FRONT, HDC* BACK);
	void InitTiles();

	void Update();
	void FillLine();
	void CheckFilled();
	void CheckKeyDown();
	void Render(HDC input);
	void DrawGrid(HDC hdc);
};

