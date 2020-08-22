#pragma once
#include "Objects.h"

#define DETONATE_TIME 2000

class Bomb : public AnimObject
{
private:
	int Power;
	int PlayerNum;

	int Timer;
	bool IsDetonated;
public:
	Bomb(int Owner, POINT pos, int power);
	~Bomb();

	void Update();
	void UpdateFrame();
};

