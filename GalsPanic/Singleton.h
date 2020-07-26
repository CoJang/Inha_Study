#pragma once
#include "SceneManager.h"

class Singleton
{
private:
	SceneManager* SM;
public:
	Singleton();
	~Singleton();

	void InitSingleton(HDC* Frontbuffer, HDC* backbuffer);

	SceneManager* GetSceneManager() { return SM; };
};

