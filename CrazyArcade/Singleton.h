#pragma once

class SceneManager;
class CollisionManager;
class SoundManager;

class Singleton
{
private:
	SceneManager* SM;
	CollisionManager* CM;
	SoundManager* SFXM;
public:
	Singleton();
	~Singleton();

	void InitSingleton(HDC* Frontbuffer, HDC* backbuffer);
	void Release();

	inline SceneManager* GetSceneManager() { return SM; };
	inline CollisionManager* GetCollisionManager() { return CM; };
	inline SoundManager* GetSoundManager() { return SFXM; };
};
