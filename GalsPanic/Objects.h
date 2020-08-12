#pragma once
#include "stdafx.h"

class Objects
{
protected:
	wstring ImagePath;
	HBITMAP hImage;
	BITMAP bitImage;

	POINT Dir;
	POINT Pos;
	POINT Sprite_Size;
public:
	Objects() : Pos({ 0,0 }) {};
	virtual ~Objects() {};

	virtual void Render(HDC front, HDC back) {}
	virtual void Update() {};
	virtual void SetPos(POINT input) { Pos = input; };
	virtual POINT GetPos() { return Pos; };
};

class ImageObject : Objects
{
public:
	ImageObject();
	~ImageObject() {};

	void InitImageObject(wstring Path, POINT pos);
	void Update();
	void Render(HDC front, HDC back);
};

