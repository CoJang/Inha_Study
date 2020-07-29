#pragma once
#include "stdafx.h"


class Player
{
private:
	POINT Pos;
	int r;
public:
	Player(POINT input, int size) { Pos = input; r = size; };
	~Player() {};

	void Render(HDC hdc);
	void Update();
	void MoveChar(POINT Dir, POINT MapPos);
	POINT GetPos() { return Pos; };
};

