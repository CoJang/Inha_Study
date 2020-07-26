#pragma once
#include "stdafx.h"
#include "Objects.h"

class FootPrint : Objects
{
private:
	int r;
	RECT Rgn;
	COLORREF color;
	POINT Pivot;

	int Life;
	int LifeTime;
	bool IsActive;
public:
	FootPrint();
	~FootPrint() {};

	int GetR() { return r; };
	void Render(HDC front, HDC back);
	void Update();
	bool IsActived() { return IsActive; };
	void SetState(bool input) { IsActive = input; };
	void SetPos(POINT input) { Pos = input; };
};

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

	POINT prevPos;
	int Max_Print;
	FootPrint FootPrints[99];
	int PrintDist;
public:
	Player();
	~Player();

	void Render(HDC front, HDC back);
	void UpdateFrame();
	void Update();

	void SetPlayerDir(POINT input);
	void SetPlayerSize(float input) { CharSize = input; };
	float GetPlayerSize() { return CharSize; };
};

