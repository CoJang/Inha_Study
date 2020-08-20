#pragma once

class MapObjects
{
protected:
	POINT Pos;
	HBITMAP hImage;
	BITMAP bitImage;

	POINT Sprite_Size;
	POINT Pivot;

public:
	MapObjects() { Pos = { 0, 0 }; Pivot = { 0, 0 }; };
	virtual ~MapObjects() {};

	virtual void Init() {};
	virtual void Render(HDC front, HDC back) {};
};

