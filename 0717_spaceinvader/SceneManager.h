#pragma once
#include "stdafx.h"
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
	int Score;
public:
	SceneManager() {};
	~SceneManager() {};

	void Destroy();
	void NextScene();
	void PrevScene();

	Scene* GetInstance() { return CurrentScene;	};
	void InitManager(HDC* device);

	void UpdateScore(int input) { Score = input; };
	int GetScore() { return Score; };
};

