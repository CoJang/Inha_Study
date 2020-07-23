#pragma once
#include "stdafx.h"

class Objects
{
protected:
	POINT pos;
	int r;
public:
	Objects() : pos({ 0,0 }), r(25) {};
	virtual ~Objects() {};

	virtual void Render(HDC hdc) {};
	virtual void Update() {};
	virtual void SetPos(POINT input) { pos = input; };
	virtual POINT GetPos() { return pos; };
	int GetRadius() { return r; };
};

