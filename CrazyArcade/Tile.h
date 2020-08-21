#pragma once
#include "MapObjects.h"

class Tile : public MapObjects
{
public:
	Tile();
	~Tile();
	
	void Init(POINT pos, POINT pivot);
	void Init(wstring path, POINT pos, POINT pivot);
	void SetImage(HBITMAP & image, BITMAP & bitmap);
	void Render(HDC front, HDC back);
};

