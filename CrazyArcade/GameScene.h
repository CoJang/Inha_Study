#pragma once
#include "Scene.h"
#include "Bomb.h"
#include "Player.h"
#include "Map.h"

class GameScene : public Scene
{
private:
	RECT ID_Rect;
	RECT SCORE_Rect;
	RECT LIFE_Rect;

	float Timer;
	wstring ScoreStr;
	int score;

	Player* MainChar;
	Map* map;

	bool ColliderDrawMode;
public:
	GameScene();
	~GameScene();

	void DrawButtons();
	ButtonType CheckClick(POINT mpos, int flag);
	void CheckKeyDown();

	void Render();
	void Update();
	void ResetScene();
};

