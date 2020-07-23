#pragma once
#include "Scene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "GameOverScene.h"

class SceneManager
{
private:
	vector<Scene*> Manager;
	Scene* CurrentScene;
	HDC* hdc;

	wstring ID;
	int score;
public:
	SceneManager() {};
	~SceneManager() {};

	Scene* GetInstance() { return CurrentScene; };

	void InitManager(HDC* device);
	void Destroy();

	void NextScene();
	void PrevScene();

	void UpdateScore(int input) { score = input; };
	int GetScore() { return score; };
};

