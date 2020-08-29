#pragma once
#include "Objects.h"
#include "Bomb.h"
#include "Item.h"
#include "SoundManager.h"

class Block;

#define BOMB_LIMIT 9
#define SPEED_LIMIT 15
#define POWER_LIMIT 5

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
	vector<int*> ItemBag;
public:
	Player();
	~Player();

	void Update();
	void Render(HDC front, HDC back, bool ColliderDraw);
	void InitPlayer(POINT pos, POINT pivot);
	void SetPlayerDir();
	void Collision();

	void UpdateColliderBox();
	void PutBomb();
	void RewindMove();
	void GetItem(int);

	bool ObstacleCollision(Objects* other);
};

