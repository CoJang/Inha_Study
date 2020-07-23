#pragma once
#include "stdafx.h"


enum TYPE
{
	RECTANGLE,
	CIRCLE,
	STAR
};
enum GAMEMODE
{
	NORMAL,
	MERGE,
	DIVIDE,
};

#define Deg2Rad(x) (x * 3.141592 / 180)
#define Rad2Deg(x) (x / 3.141592 * 180)

class Cshape
{
protected:
	POINT pos;
	int r;
	TYPE shape;
	int moveSpeed;
	float angle;
	float rotation;
	POINT Dir;
public:
	Cshape();
	virtual ~Cshape() {};

	virtual void Update() = 0;
	void Collision(RECT winRect, vector<Cshape*> & CollisionManager, GAMEMODE mode);
	virtual void Show(HDC hdc) = 0;

	int GetRadius() { return r; };
	POINT GetPos() { return pos; };
	POINT GetDir() { return Dir; };
	int GetSpeed() { return moveSpeed; };
	TYPE GetType() { return shape; };
	float GetAngle() { return angle; };

	void SetDir(POINT dir) { Dir = dir; };
	void SetSpeed(int speed) { moveSpeed = speed; };
	void SetRadius(int inputR) { r = inputR; };
};

class MyRect : public Cshape
{
private:
	POINT vertex[4];
public:
	MyRect();
	MyRect(int x, int y, int movspd, int rotangle, int dirx, int diry);
	~MyRect() {};

	void Show(HDC hdc);
	void Update();
	void Rotate();
};

class MyCircle : public Cshape
{
public:
	MyCircle();
	MyCircle(int x, int y, int movspd, int dirx, int diry);
	~MyCircle() {};

	void Show(HDC hdc);
	void Update();
};
