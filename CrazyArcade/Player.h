#pragma once
#include "Bomb.h"
class Block;

class Player
{
private:
// Basic Attri
	POINT Pos;
	POINT Dir;
	int Speed;
	float CharSize;
// Game Attri
	int MaxBomb;
	int BombPower;
	vector<Bomb*> BombBag;
// Collision
	RECT Collider;
	int PlayerColliderSize;
	POINT ColPivot;
// Image & Anim
	HBITMAP hImage;
	BITMAP bitImage;
	POINT Sprite_Size;
	POINT Pivot;
	POINT Start;
	int Anim_Frame_Max;
	int Anim_Frame_Min;
	int Anim_Frame_Cur;
	int Anim_Frame_Flag;
public:
	Player();
	~Player();

	void Update();
	void UpdateFrame();
	void Render(HDC front, HDC back, bool ColliderDraw);
	void InitPlayer(POINT pos, POINT pivot);
	void SetPlayerDir(POINT dir);
	void Collision(Block * Blocks);

	void PutBomb();
	void RewindMove();
};

