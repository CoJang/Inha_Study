#pragma once
#include "stdafx.h"
#include "Objects.h"
#include "GunTower.h"

enum STATE
{
	ACTIVE,
	HIT,
	NOT_ACTIVE
};

class Enemy : public Objects
{
private:
	POINT vertex[4];
	STATE state;
	float moveSpeed;
public:
	Enemy();
	~Enemy();

	void Render(HDC hdc);
	void Update();
	void Rotate();
	void Move();
	bool IsCollision(Bullet** other);
	int GetState() { return state; };
	void SetState(STATE input) { state = input; };
};

