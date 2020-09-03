#pragma once

#include "SceneManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "NetworkManager.h"

class Singleton
{
private:
	NetworkManager* NM;
	SceneManager* SM;
	CollisionManager* CM;
	SoundManager* SFXM;
	ImageManager* IM;
public:
	Singleton();
	~Singleton();

	void InitSingleton(HWND hWnd, HDC* Frontbuffer, HDC* backbuffer);
	void Release();

	inline SceneManager* GetSceneManager() { return SM; };
	inline CollisionManager* GetCollisionManager() { return CM; };
	inline SoundManager* GetSoundManager() { return SFXM; };
	inline ImageManager* GetImageManager() { return IM; };
	inline NetworkManager* GetNetworkManager() { return NM; };
};
