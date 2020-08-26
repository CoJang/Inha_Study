#pragma once

class SceneManager;
class CollisionManager;
class SoundManager;
class ImageManager;

class Singleton
{
private:
	SceneManager* SM;
	CollisionManager* CM;
	SoundManager* SFXM;
	ImageManager* IM;
public:
	Singleton();
	~Singleton();

	void InitSingleton(HDC* Frontbuffer, HDC* backbuffer);
	void Release();

	inline SceneManager* GetSceneManager() { return SM; };
	inline CollisionManager* GetCollisionManager() { return CM; };
	inline SoundManager* GetSoundManager() { return SFXM; };
	inline ImageManager* GetImageManager() { return IM; };
};
