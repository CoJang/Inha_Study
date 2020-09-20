#pragma once
#include "Scene.h"
#include "Bomb.h"
#include "Player.h"
#include "Map.h"

class GameScene : public Scene
{
private:
	int PlayerFlag;
	int CharFlag;
	RECT ID_Rect;
	RECT SCORE_Rect;
	RECT LIFE_Rect;

	float Timer;
	wstring ScoreStr;
	int score;

	Player* MainChar;
	Player* OtherChar;
	Map* map;

	bool ColliderDrawMode;
	vector<Bomb*> OtherBombs;
	POINT SpawnPoints[4];
public:
	GameScene(int playerFlag, int charFlag);
	~GameScene();

	void DrawButtons();
	ButtonType CheckClick(POINT mpos, int flag);
	void CheckKeyDown();
	void ReceiveData(Packet* data);
	void Temp();

	void Render();
	void Update();
	void ResetScene();
};

