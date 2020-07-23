#pragma once
#include "stdafx.h"
#include <cmath>

#define Deg2Rad(x) (x * 3.141592 / 180)
#define Rad2Deg(x) (x / 3.141592 * 180)

class MyStar 
{
private:
	int r;
	POINT pos;
	POINT vertex[10];
public:
	MyStar();
	MyStar(int x, int y, int movspd, int rotangle, int dirx, int diry);
	~MyStar() {};

	void Show(HDC hdc);
	void SetPos(POINT input) { pos = input; };
};

POINT CramersRule(POINT P1, POINT P2, POINT P3, POINT P4);
POINT RotatePoint(POINT p, int r, int degree);
