#pragma once
#include "Objects.h"

class Enemy : public Objects
{
private:
	int Speed;

	int Anim_Frame_Max;
	int Anim_Frame_Min;
	int Anim_Frame_Cur;
	int Anim_Frame_Flag;

	POINT Start;
public:
	Enemy();
	~Enemy();




};

