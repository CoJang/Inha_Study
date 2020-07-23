#pragma once
#include "stdafx.h"

void DrawStar(HDC, int, int, int);
POINT RotatePoint(POINT p, int r, int degree);

void DrawCircle(HDC hdc, int CenterX, int CenterY, int rX, int rY)
{
	Ellipse(hdc, CenterX - rX, CenterY - rY, CenterX + rX, CenterY + rY);
}

void DrawCircle(HDC hdc, int CenterX, int CenterY, int r)
{
	Ellipse(hdc, CenterX - r, CenterY - r, CenterX + r, CenterY + r);
}

// 지정된 형식으로써 다른 인자를 받을 수 없고, 리턴도 할 수 없다.
void CALLBACK AutoMove(HWND hWnd, UINT msg, UINT_PTR idEvent, DWORD dTime)
{
	int breakpoint = 0;
}

