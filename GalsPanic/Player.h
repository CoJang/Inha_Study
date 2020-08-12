#pragma once
#include "Objects.h"
#include "MyMap.h"

class Player : public Objects
{
private:
	int Anim_Frame_Max;
	int Anim_Frame_Min;
	int Anim_Frame_Cur;
	int Anim_Frame_Flag;

	POINT Start;
	POINT oldPos;
	POINT Pivot;
	int Speed;
	float CharSize;

	MyMap* map;
public:
	Player();
	~Player();

	void InitPlayer(MyMap* input);
	void Render(HDC front, HDC back);
	void UpdateFrame();
	void Update();

	void SetPlayerDir(POINT input);
	void SetPlayerSize(float input) { CharSize = input; };
	void SetPixel(TileState state, COLORREF color, POINT pos);
	float GetPlayerSize() { return CharSize; };
};

