#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	vertex[0].x = pos.x - r; vertex[1].x = pos.x + r;
	vertex[0].y = pos.y - r; vertex[1].y = pos.y - r;
	vertex[3].x = pos.x - r; vertex[2].x = pos.x + r;
	vertex[3].y = pos.y + r; vertex[2].y = pos.y + r;

	pos = { 55, 55 };
	state = NOT_ACTIVE;
	moveSpeed = 15;
	r = 10;
}

Enemy::~Enemy(){}

void Enemy::Render(HDC hdc)
{
	Polygon(hdc, vertex, 4);
}

void Enemy::Update()
{
	pos.y = pos.y + moveSpeed;

	switch (state)
	{
	case ACTIVE:
		Move();
		break;
	case HIT:
		Rotate();
		break;
	}	
}

bool Enemy::IsCollision(Bullet** others)
{
	if (state != ACTIVE)
		return false;

	POINT otherPos;
	int otherR;
	float distance;

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!others[i]->GetState()) continue;
 		otherPos = others[i]->GetPos();
		otherR = others[i]->GetRadius();
		distance = sqrt(pow(pos.x - otherPos.x, 2) + pow(pos.y - otherPos.y, 2));

		if (distance <= otherR + r)
		{
			state = STATE::HIT;
			others[i]->SetState(false);
			return true;
		}
	}


	return false;
}

void Enemy::Rotate()
{
	if (abs(vertex[0].x - vertex[1].x) < 2)
	{
		state = NOT_ACTIVE;
		return;
	}

	float angle = 30;
	float radian = Deg2Rad(angle);

	for (int i = 0; i < 4; i++)
	{
		vertex[i].x = cos(radian) * (vertex[i].x - pos.x) - sin(radian) * (vertex[i].y - pos.y) + pos.x;
		vertex[i].y = sin(radian) * (vertex[i].x - pos.x) + cos(radian) * (vertex[i].y - pos.y) + pos.y;
	}

}

void Enemy::Move()
{
	vertex[0].x = pos.x - r; vertex[1].x = pos.x + r;
	vertex[0].y = pos.y - r; vertex[1].y = pos.y - r;
	vertex[3].x = pos.x - r; vertex[2].x = pos.x + r;
	vertex[3].y = pos.y + r; vertex[2].y = pos.y + r;
}
