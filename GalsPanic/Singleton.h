#pragma once
#include "SceneManager.h"

class Singleton
{
private:
	SceneManager* SM;
public:
	Singleton();
	~Singleton();

	void InitSingleton(HDC* hdc);

	SceneManager* GetSceneManager() { return SM; };
};

