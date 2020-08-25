#pragma once
#include "Objects.h"
#include "Bomb.h"
#include "Item.h"

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
	vector<ItemType*> ItemBag;
public:
	Player();
	~Player();

	void Update();
	void Render(HDC front, HDC back, bool ColliderDraw);
	void InitPlayer(POINT pos, POINT pivot);
	void SetPlayerDir(POINT dir);
	void Collision();

	void PutBomb();
	void RewindMove();
	void GetItem(ItemType);
};

