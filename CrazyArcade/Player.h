#pragma once
#include "Bomb.h"
#include "Objects.h"
class Block;

class Player : public AnimObject
{
private:
// Basic Attri
	POINT Dir;
	int Speed;

// Game Attri
	int MaxBomb;
	int BombPower;
	vector<Bomb*> BombBag;
public:
	Player();
	~Player();

	void Update();
	void Render(HDC front, HDC back, bool ColliderDraw);
	void InitPlayer(POINT pos, POINT pivot);
	void SetPlayerDir(POINT dir);
	void Collision(Block * Blocks);

	void PutBomb();
	void RewindMove();
};

