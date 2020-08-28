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
}

void Singleton::InitSingleton(HDC* Frontbuffer, HDC* backbuffer)
{
	SM = new SceneManager;
	CM = new CollisionManager;
	SFXM = new SoundManager;
	IM = new ImageManager;

	SFXM->init();
	SM->InitManager(Frontbuffer, backbuffer);
}

void Singleton::Release()
{

}
