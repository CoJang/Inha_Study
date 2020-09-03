#include "stdafx.h"
#include "Singleton.h"


Singleton::Singleton()
{
}

Singleton::~Singleton()
{
	delete SM;
	delete CM;
	delete SFXM;
	delete IM;
	delete NM;
}

void Singleton::InitSingleton(HWND hWnd, HDC* Frontbuffer, HDC* backbuffer)
{
	NM = new NetworkManager;
	SM = new SceneManager;
	CM = new CollisionManager;
	SFXM = new SoundManager;
	IM = new ImageManager;

	SFXM->init();
	SM->InitManager(Frontbuffer, backbuffer);
	NM->InitNetworkManager(hWnd);
}

void Singleton::Release()
{

}
