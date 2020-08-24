#pragma once

class SceneManager;
class CollisionManager;

class Singleton
{
private:
	SceneManager* SM;
	CollisionManager* CM;
public:
	Singleton();
	~Singleton();

	void InitSingleton(HDC* Frontbuffer, HDC* backbuffer);

	SceneManager* GetSceneManager() { return SM; };
	CollisionManager* GetCollisionManager() { return CM; };
};
