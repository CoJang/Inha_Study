#pragma once
#include "Scene.h"
#include "Player.h"

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

	float Timer;
	float GenTime;
	POINT GenPos;
	int Life;

	Player* MainChar;
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

