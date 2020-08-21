#pragma once

#define DETONATE_TIME 2000

class Bomb
{
private:
	POINT Pos;

	int Power;
	int PlayerNum;

	RECT Collider;
	POINT ColPivot;
	int BombColliderSize;
// Image & Anim
	HBITMAP hImage;
	BITMAP bitImage;
	POINT Sprite_Size;
	POINT Pivot;
	POINT Start;
	float BombSize;
	int Anim_Frame_Max;
	int Anim_Frame_Min;
	int Anim_Frame_Cur;
	int Anim_Frame_Flag;
	int Anim_Speed;
	int Anim_Timer;
public:
	Bomb(int Owner, POINT pos, int power);
	~Bomb();

	void Update();
	void UpdateFrame();
	void Render(HDC front, HDC back, bool ColliderDraw);

};

