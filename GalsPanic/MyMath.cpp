#include "stdafx.h"
#include "MyMath.h"

// src = center point,  dest = output
void RotatePoint(POINT & dest, POINT & src, float angle, int r)
{
	dest.x = src.x + sin(Deg2Rad(angle)) * r;
	dest.y = src.y + cos(Deg2Rad(angle)) * r;
}

// returns CrossPoint
POINT CramersRule(POINT P1, POINT P2, POINT P3, POINT P4)
{
	POINT CrossPoint = { 0, 0 };

	float a, b, c, d, e, f;

	a = P1.y - P2.y;
	b = -(P1.x - P2.x);
	c = P3.y - P4.y;
	d = -(P3.x - P4.x);
	e = a * P1.x + b * P1.y;
	f = c * P3.x + d * P3.y;

	CrossPoint.x = (e * d - b * f) / (a * d - b * c);
	CrossPoint.y = (a * f - e * c) / (a * d - b * c);

	return CrossPoint;
}