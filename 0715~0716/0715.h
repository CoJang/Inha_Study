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

// ������ �������ν� �ٸ� ���ڸ� ���� �� ����, ���ϵ� �� �� ����.
void CALLBACK AutoMove(HWND hWnd, UINT msg, UINT_PTR idEvent, DWORD dTime)
{
	int breakpoint = 0;
}

