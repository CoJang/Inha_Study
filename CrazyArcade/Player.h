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
// Player Flag
	int PlayerFlag;

// Basic Attri
	POINT Dir;
	int Speed;
	int oldSpeed;
	POINT vertex[4];

// Game Attri
	bool IsTrapped;
	bool IsDeath;

	int MaxBomb;
	int BombPower;
	vector<Bomb*> BombBag;
	vector<int*> ItemBag;

	int DeathTimer;
	int LifeTime;
	int DeathAnim;
	HBITMAP DeathImage[2];
	BITMAP DeathBitmap[2];
public:
	Player();
	~Player();
	void InitPlayer(POINT pos, POINT pivot, int playerflag);

	void Update();
	void Render(HDC front, HDC back, bool ColliderDraw);

	void RewindMove();
	void SetPlayerDir();
	void SetPlayerDir(int KeyState);

	void Collision();
	void UpdateColliderBox();
	bool ObstacleCollision(Objects* other);

	void PutBomb();
	void GetItem(int);

	void TrapPlayer();
	void KillPlayer();
};

