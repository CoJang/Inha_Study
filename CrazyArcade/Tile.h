#pragma once
#include "MapObjects.h"

class Tile : public MapObjects
{
public:
	Tile();
	~Tile();
	
	void Init(wstring Path, POINT pos, POINT pivot);
	void Render(HDC front, HDC back);
};

