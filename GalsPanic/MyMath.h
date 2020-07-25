#pragma once
#include "stdafx.h"

#define PI 3.1415926535
#define Deg2Rad(x) (x * PI / 180)
#define Rad2Deg(x) (x / PI * 180)

void RotatePoint(POINT & dest, POINT & src, float angle, int r);
POINT CramersRule(POINT P1, POINT P2, POINT P3, POINT P4);
void SetRgnPixels(HDC hdc, RECT region, COLORREF color);