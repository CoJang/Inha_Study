#include "stdafx.h"
#include "GunTower.h"


GunTower::GunTower()
{
	pos = { 213, 700 };
	r = 50;
	LineR = 80;
	LinePos = { pos.x, pos.y - LineR };
	LineOrigin = { pos.x, pos.y - LineR };
	LineAngle = 180;

	for(int i = 0; i < BULLET_MAX; i++)
		bullets[i] = new Bullet({LinePos.x, LinePos.y}, 5);
}

GunTower::~GunTower()
{
	for (int i = 0; i < BULLET_MAX; i++)
		delete bullets[i];
}

void GunTower::Update()
{

}

void GunTower::Render(HDC hdc)
{
	Pie(hdc, pos.x - r, pos.y - r, pos.x + r, pos.y + r,
			 pos.x + r, pos.y, pos.x - r, pos.y);

	DrawLine(hdc);

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullets[i]->GetState())
		{
			bullets[i]->Update((LineAngle - 90));
			bullets[i]->Render(hdc);
		}
	}
}

void GunTower::DrawLine(HDC hdc)
{
	MoveToEx(hdc, pos.x, pos.y - 1, NULL);
	LineTo(hdc, LinePos.x, LinePos.y);
}

void GunTower::Rotate(float degree)
{
	LineAngle = degree + 90;
	
	if (LineAngle < 90 && LineAngle > 0)
		LineAngle = 91;
	else if (LineAngle > -90 && LineAngle < 0)
		LineAngle = 270;

	RotatePoint(LinePos, pos, -LineAngle, LineR);
}

void GunTower::Shot(HDC hdc)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!bullets[i]->GetState())
		{
			bullets[i]->SetState(true);
			bullets[i]->SetPos({ LinePos.x, LinePos.y });
			bullets[i]->SetVectors(LineAngle - 90);
			break;
		}
	}
}

void Bullet::Render(HDC hdc)
{
	Ellipse(hdc, pos.x - r, pos.y - r, pos.x + r, pos.y + r);
}

void Bullet::Update(float angle)
{
	pos.x -= vectorX * Speed;
	pos.y += vectorY * Speed;

	if (pos.y < -10 || pos.x > WIN_WIDTH || pos.x < 0)
		IsActive = false;
}

void Bullet::SetVectors(float angle)
{
	vectorX = cos(Deg2Rad(angle));
	vectorY = -sin(Deg2Rad(angle));
}
