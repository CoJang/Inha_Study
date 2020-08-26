#include "stdafx.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "Singleton.h"


Singleton::Singleton()
{
	CSound::Init();
}


Singleton::~Singleton()
{
	delete SM;
	delete CM;
	//delete SFXM;
	delete IM;

	CSound::Release();
}

void Singleton::InitSingleton(HDC* Frontbuffer, HDC* backbuffer)
{
	SM = new SceneManager;
	CM = new CollisionManager;
	//SFXM = new SoundManager;
	IM = new ImageManager;

	SM->InitManager(Frontbuffer, backbuffer);
}

void Singleton::Release()
{

}
