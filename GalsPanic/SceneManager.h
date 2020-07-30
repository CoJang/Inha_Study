#pragma once
#include "TitleScene.h"
#include "GameScene.h"
#include "GameOverScene.h"

class SceneManager
{
private:
	vector<Scene*> Manager;
	Scene* CurrentScene;
	HDC* FrontBuffer;
	HDC* BackBuffer;

	wstring ID;
	int score;
public:
	SceneManager() {};
	~SceneManager() {};

	Scene* GetInstance() { return CurrentScene; };

	void InitManager(HDC* Front, HDC* Back);
	void Destroy();

	void NextScene();
	void PrevScene();

	void UpdateScore(int input) { score = input; };
	int GetScore() { return score; };
};

