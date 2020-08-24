#include "stdafx.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Singleton.h"


Singleton::Singleton()
{
}


Singleton::~Singleton()
{
	delete SM;
	delete CM;
}

void Singleton::InitSingleton(HDC* Frontbuffer, HDC* backbuffer)
{
	SM = new SceneManager;
	CM = new CollisionManager;

	SM->InitManager(Frontbuffer, backbuffer);
}
