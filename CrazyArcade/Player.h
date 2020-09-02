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
	POINT vertex[4];

// Game Attri
	bool IsTrapped;
	bool IsDeath;

	int MaxBomb;
	int BombPower;
	vector<Bomb*> BombBag;
	vector<int*> ItemBag;

	int DeathAnim;
	HBITMAP DeathImage[2];
	BITMAP DeathBitmap[2];
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
	void TrapPlayer();

	bool ObstacleCollision(Objects* other);
};

