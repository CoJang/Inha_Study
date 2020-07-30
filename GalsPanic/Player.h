#pragma once
#include "Objects.h"
#include "MyMap.h"

//class FootPrint : Objects
//{
//private:
//	int r;
//	POINT Pivot;
//
//	int Life;
//	int LifeTime;
//	bool IsActive;
//public:
//	FootPrint();
//	~FootPrint() {};
//
//	int GetR() { return r; };
//	void Update(MyMap* input);
//	bool IsActived() { return IsActive; };
//	void SetState(bool input) { IsActive = input; };
//	void SetPos(POINT input) { Pos = input; };
//
//	bool SetPixelsRgn(MyMap* input, TileState state, COLORREF color);
//};

class Player : public Objects
{
private:
	int Anim_Frame_Max;
	int Anim_Frame_Min;
	int Anim_Frame_Cur;
	int Anim_Frame_Flag;

	POINT Start;
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
	void SetPixelsRgn(TileState state, COLORREF color, RECT Region);
	void SetPixel(TileState state, COLORREF color);
	float GetPlayerSize() { return CharSize; };
};

