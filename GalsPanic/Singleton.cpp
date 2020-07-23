#include "stdafx.h"
#include "Singleton.h"


Singleton::Singleton()
{
}


Singleton::~Singleton()
{
	delete SM;
}

void Singleton::InitSingleton(HDC* hdc)
{
	SM = new SceneManager;

	SM->InitManager(hdc);
}
