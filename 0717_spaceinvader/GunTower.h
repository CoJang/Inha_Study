#pragma once
#include "stdafx.h"
#include "Objects.h"
#include "MyMath.h"

#define BULLET_MAX 8

class Bullet : public Objects
{
private:
	int Speed;
	bool IsActive;
	float vectorX, vectorY;
public:
	Bullet() :Speed(15), IsActive(false), vectorX(0){};
	Bullet(POINT p, int radius) 
	{ pos = p; r = radius; Speed = 15; IsActive = false; vectorX = 0; };
	~Bullet() {};
	
	void Render(HDC hdc);
	void Update(float angle);
	void SetVectors(float angle);

	bool GetState() { return IsActive; };
	void SetState(bool input) { IsActive = input; };
};

class GunTower : public Objects
{
private:
	int LineR;
	POINT LineOrigin;
	float LineAngle;
	POINT LinePos;

public:
	Bullet* bullets[BULLET_MAX];

	GunTower();
	~GunTower();

	void Update();
	void Render(HDC hdc);
	void Rotate(float degree);
	void DrawLine(HDC hdc);
	void Shot(HDC hdc);

	POINT GetTowerPos() { return pos; };
};

