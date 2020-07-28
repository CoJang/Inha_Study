#pragma once
#include "stdafx.h"
#include "Cshape.h"
#include "MyStar.h"


Cshape::Cshape():
	pos({200, 200}), r(35), shape(RECTANGLE), 
	moveSpeed(30), angle(8.0f), Dir({1, 1}), rotation(0) {}

void Cshape::Collision(RECT winRect, vector<Cshape*>& CollisionManager, GAMEMODE mode)
{
	if (pos.x + r >= winRect.right)
		Dir.x = -1;
	if (pos.x - r <= winRect.left)
		Dir.x = 1;
	if (pos.y + r >= winRect.bottom)
		Dir.y = -1;
	if (pos.y - r <= winRect.top)
		Dir.y = 1;

	for (int i = 0; i < CollisionManager.size(); i++)
	{
		if (CollisionManager[i] == this)
			continue;

		POINT otherPos = CollisionManager[i]->GetPos();
		POINT otherDir = CollisionManager[i]->GetDir();
		int otherR =	 CollisionManager[i]->GetRadius();
		int otherSpeed = CollisionManager[i]->GetSpeed();
		float distance = sqrt(pow(pos.x - otherPos.x, 2) + pow(pos.y - otherPos.y, 2));

		if (distance < otherR + r)
		{
			// swap dir
			POINT temp = Dir;
			Dir = otherDir;
			CollisionManager[i]->SetDir(temp);

			// swap speed
			temp.x = moveSpeed;
			moveSpeed = otherSpeed;
			CollisionManager[i]->SetSpeed(temp.x);

			if (pos.x > otherPos.x)
				pos.x = pos.x + moveSpeed;
			else
				pos.x = pos.x - moveSpeed;

			if (mode == DIVIDE)
			{
				TYPE otherType = CollisionManager[i]->GetType();
				if (shape == otherType)
					continue;

				if (otherR > 20)
					CollisionManager[i]->SetRadius(otherR / 2);
				else
					continue;

				Cshape* temp;
				if (otherType == CIRCLE)
					temp = new MyCircle(otherPos.x, otherPos.y, otherSpeed, otherDir.x, otherDir.y);
				if (otherType == RECTANGLE)
					temp = new MyRect(otherPos.x, otherPos.y, otherSpeed, CollisionManager[i]->GetAngle(), otherDir.x, otherDir.y);
				if(otherType == STAR)
					temp = new MyStar(otherPos.x, otherPos.y, otherSpeed, CollisionManager[i]->GetAngle(), otherDir.x, otherDir.y);

				temp->SetRadius(otherR / 2);
				CollisionManager.push_back(temp);
			}
			else if (mode == MERGE)
			{
				TYPE otherType = CollisionManager[i]->GetType();

				if (shape != otherType)
					continue;

				r = r + otherR;

				delete CollisionManager[i];
				CollisionManager.erase(CollisionManager.begin() + i);
				i--;
				return;
			}
		}
	}
}

MyRect::MyRect()
{
	shape = RECTANGLE;

	vertex[0].x = pos.x - r; vertex[1].x = pos.x + r;
	vertex[0].y = pos.y - r; vertex[1].y = pos.y - r;

	vertex[3].x = pos.x - r; vertex[2].x = pos.x + r;
	vertex[3].y = pos.y + r; vertex[2].y = pos.y + r;
}

MyRect::MyRect(int x, int y, int movspd, int rotangle, int dirx, int diry)
{
	shape = RECTANGLE;

	pos = { x, y };
	moveSpeed = movspd;
	angle = rotangle;
	Dir = { dirx, diry };

	vertex[0].x = pos.x - r; vertex[1].x = pos.x + r;
	vertex[0].y = pos.y - r; vertex[1].y = pos.y - r;
	vertex[3].x = pos.x - r; vertex[2].x = pos.x + r;
	vertex[3].y = pos.y + r; vertex[2].y = pos.y + r;
}

void MyRect::Show(HDC hdc)
{
	Polygon(hdc, vertex, 4);
}

void MyRect::Update()
{
	pos.x = pos.x + (moveSpeed * Dir.x);
	pos.y = pos.y + (moveSpeed * Dir.y);

	vertex[0].x = pos.x - r; vertex[1].x = pos.x + r;
	vertex[0].y = pos.y - r; vertex[1].y = pos.y - r;
	vertex[3].x = pos.x - r; vertex[2].x = pos.x + r;
	vertex[3].y = pos.y + r; vertex[2].y = pos.y + r;

	Rotate();
}

void MyRect::Rotate()
{
	float radian = Deg2Rad(rotation);
	double cosin = cos(radian);
	double sine = sin(radian);

	//vertex[0].x = -r * cosin + pos.x;	vertex[0].y = r * sine + pos.y;
	//vertex[1].x = r * sine + pos.x;		vertex[1].y = r * cosin + pos.y;
	//vertex[2].x = r * cosin + pos.x;	vertex[2].y = -r * sine + pos.y;
	//vertex[3].x = -r * sine + pos.x;	vertex[3].y = -r * cosin + pos.y;

	for (int i = 0; i < 4; i++)
	{
		POINT Center = { vertex[i].x - pos.x , vertex[i].y - pos.y };

		int x2 = Center.x * cosin - Center.y * sine + pos.x;
		int y2 = Center.x * sine + Center.y * cosin + pos.y;

		vertex[i] = { x2, y2 };
	}

	if (rotation < 360) rotation += angle;
	else rotation = 0;
}

MyCircle::MyCircle()
{
	shape = CIRCLE;
	pos = { 100, 200 };
	moveSpeed = 15;
}

MyCircle::MyCircle(int x, int y, int movspd, int dirx, int diry)
{
	shape = CIRCLE;
	pos = { x, y };
	moveSpeed = movspd;
	Dir = { dirx, diry };
}

void MyCircle::Show(HDC hdc)
{
	Ellipse(hdc, pos.x - r, pos.y - r, pos.x + r, pos.y + r);
}

void MyCircle::Update()
{
	pos.x = pos.x + (moveSpeed * Dir.x);
	pos.y = pos.y + (moveSpeed * Dir.y);
}

