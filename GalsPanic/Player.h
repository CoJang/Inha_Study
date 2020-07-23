#pragma once
#include "stdafx.h"
#include "Objects.h"

class Player : public Objects
{
private:
	int Anim_Frame_Max;
	int Anim_Frame_Min;
	int Anim_Frame_Cur;
	int Anim_Frame_Flag;

	POINT Start;
	int Speed;
public:
	Player();
	~Player();

	void Render(HDC hdc);
	void UpdateFrame();
	void Update();

	void SetPlayerDir(POINT input);
};

