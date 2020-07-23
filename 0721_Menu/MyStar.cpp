#include "stdafx.h"
#include "MyStar.h"


MyStar::MyStar()
{
	int tempAngle = 72;
	r = 15;

	for (int i = 0; i < 5; i++)
	{
		vertex[i] = RotatePoint(pos, r, tempAngle * i);
	}
}

MyStar::MyStar(int x, int y, int movspd, int rotangle, int dirx, int diry)
{
	pos = { x, y };
	r = 15;

	int tempAngle = 72;

	for (int i = 0; i < 5; i++)
	{
		vertex[i] = RotatePoint(pos, r, tempAngle * i);
	}
}

void MyStar::Show(HDC hdc)
{
	int tempAngle = 72;
	for (int i = 0; i < 10; i += 2)
	{
		vertex[i] = RotatePoint(pos, r, tempAngle * i);
	}
	
	vertex[1] = CramersRule(vertex[0], vertex[4], vertex[2], vertex[8]);
	vertex[3] = CramersRule(vertex[0], vertex[4], vertex[2], vertex[6]);
	vertex[5] = CramersRule(vertex[2], vertex[6], vertex[4], vertex[8]);
	vertex[7] = CramersRule(vertex[0], vertex[6], vertex[4], vertex[8]);
	vertex[9] = CramersRule(vertex[0], vertex[6], vertex[2], vertex[8]);

	Polygon(hdc, vertex, 10);
}

//void MyStar::Update()
//{
//	pos.x = pos.x + (moveSpeed * Dir.x);
//	pos.y = pos.y + (moveSpeed * Dir.y);
//
//	int tempAngle = 72;
//	for (int i = 0; i < 10; i += 2)
//	{
//		vertex[i] = RotatePoint(pos, r, tempAngle * i);
//	}
//
//	vertex[1] = CramersRule(vertex[0], vertex[4], vertex[2], vertex[8]);
//	vertex[3] = CramersRule(vertex[0], vertex[4], vertex[2], vertex[6]);
//	vertex[5] = CramersRule(vertex[2], vertex[6], vertex[4], vertex[8]);
//	vertex[7] = CramersRule(vertex[0], vertex[6], vertex[4], vertex[8]);
//	vertex[9] = CramersRule(vertex[0], vertex[6], vertex[2], vertex[8]);
//
//	Rotate();
//}

//void MyStar::Rotate()
//{
//	float radian = Deg2Rad(rotation);
//	double cosin = cos(radian);
//	double sine = sin(radian);
//
//	for (int i = 0; i < 10; i++)
//	{
//		int x2 = (vertex[i].x - pos.x) * cosin - (vertex[i].y - pos.y) * sine + pos.x;
//		int y2 = (vertex[i].x - pos.x) * sine + (vertex[i].y - pos.y) * cosin + pos.y;
//
//		vertex[i] = { x2, y2 };
//	}
//	if (rotation < 360) rotation += angle;
//	else rotation = 0;
//}

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

POINT RotatePoint(POINT p, int r, int degree)
{
	POINT temp = { p.x, p.y };

	temp.x = p.x + (r * cos(Deg2Rad(degree)));
	temp.y = p.y - (r * sin(Deg2Rad(degree)));
	return temp;
}
