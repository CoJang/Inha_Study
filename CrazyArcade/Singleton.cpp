#include "stdafx.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "Singleton.h"


Singleton::Singleton()
{
}


Singleton::~Singleton()
{
	delete SM;
	delete CM;
	//delete SFXM;
}

void Singleton::InitSingleton(HDC* Frontbuffer, HDC* backbuffer)
{
	SM = new SceneManager;
	CM = new CollisionManager;
	//SFXM = new SoundManager;

	SM->InitManager(Frontbuffer, backbuffer);
}

void Singleton::Release()
{

}
