#pragma once
#include "Objects.h"
#include "SoundManager.h"

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
// Temp Sound
	static CSound* ExplosionSound;
// Temp Image
	static HBITMAP ExplosionEffect;
	static BITMAP BitExplosionFX;
public:
	Bomb(int Owner, POINT pos, int power);
	~Bomb();

	static void BombInit();
	void Update();
	void UpdateFrame();
	void Render(HDC, HDC, bool);
	POINT RePosition(POINT pos);
	void Explosion();

	bool InitWave(int index, int flag);
	bool InitWave(int index, int flag, HBITMAP image, BITMAP bitmap);

	inline bool GetBombState() { return IsDetonated; };
	inline void Detonate() { IsDetonated = true; };
};

