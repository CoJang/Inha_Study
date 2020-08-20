#pragma once
#include "MapObjects.h"

class Block : public MapObjects
{
private:
	bool IsPassable;
	bool IsDestructible;

	POINT Start;

	int Anim_Frame_Max;
	int Anim_Frame_Min;
	int Anim_Frame_Cur;
	int Anim_Frame_Flag;
public:
	Block();
	~Block();

	void Init(wstring Path, bool Passable, bool IsDestructible, POINT pivot);
	void Render(HDC front, HDC back);
	void UpdateFrame();
};

