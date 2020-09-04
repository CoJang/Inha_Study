#include "stdafx.h"
#include "LobbyScene.h"

extern Singleton* singleton;

LobbyScene::LobbyScene()
{
	type = LOBBY;
}

LobbyScene::~LobbyScene()
{
}

void LobbyScene::Render()
{
	if (NETWORKMANAGER->GetClientNum() != 0)
	{
		NETWORKMANAGER->BroadcastMsg((string)"NextScene", false);
		singleton->GetSceneManager()->NextScene();
	}
}

void LobbyScene::Update()
{
}

void LobbyScene::ResetScene()
{
}
