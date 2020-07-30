#include "stdafx.h"
#include "SceneManager.h"
#include "Singleton.h"


Singleton::Singleton()
{
}


Singleton::~Singleton()
{
	delete SM;
}

void Singleton::InitSingleton(HDC* Frontbuffer, HDC* backbuffer)
{
	SM = new SceneManager;

	SM->InitManager(Frontbuffer, backbuffer);
}
