#pragma once
#include "Scene.h"
#include "GunTower.h"
#include "MyMath.h"
#include "Enemy.h"

#define ENEMY_MAX 15
#define LIFE_MAX 10

class GameScene : public Scene
{
private:
	RECT ID_Rect;
	RECT SCORE_Rect;
	RECT LIFE_Rect;

	wstring ScoreStr;
	int score;
	GunTower* Tower;
	Enemy* Enemys[ENEMY_MAX];

	float Timer;
	float GenTime;
	POINT GenPos;
	int Life;
public:
	GameScene();
	~GameScene();

	void DrawButtons();
	ButtonType CheckClick(POINT mpos, int flag);
	void CheckKeyDown(WPARAM wParam);

	void Render();
	void Update();
	void GenerateEnemy();
};

