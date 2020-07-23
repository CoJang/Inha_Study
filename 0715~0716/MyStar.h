#pragma once
#include "stdafx.h"
#include "Cshape.h"

class MyStar : public Cshape
{
private:
	POINT vertex[10];
public:
	MyStar();
	MyStar(int x, int y, int movspd, int rotangle, int dirx, int diry);
	~MyStar() {};

	void Show(HDC hdc);
	void Update();
	void Rotate();
};

POINT CramersRule(POINT P1, POINT P2, POINT P3, POINT P4);
POINT RotatePoint(POINT p, int r, int degree);
