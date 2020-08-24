#pragma once
#include "Objects.h"

#define DETONATE_TIME 2000
#define WAVE_ANIM_SPEED 20
class Player;

class Bomb : public AnimObject
{
private:
	int Power;
	int PlayerNum;

	int Timer;
	bool IsDetonated;

	vector<AnimObject*> BombWaves;
public:
	Bomb(int Owner, POINT pos, int power);
	~Bomb();

	void Update();
	void UpdateFrame();
	void Render(HDC, HDC, bool);
	POINT RePosition(POINT pos);
	void Explosion();

	bool InitWave(int index, int flag);

	inline bool GetBombState() { return IsDetonated; };
	inline void Detonate() { IsDetonated = true; };
};

