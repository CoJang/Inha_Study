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
		Packet temp; temp.head = COMMAND; temp.Cmd = "NextScene";
		NETWORKMANAGER->SendPacket(temp);
		singleton->GetSceneManager()->NextScene();
	}
}

void LobbyScene::Update()
{
}

void LobbyScene::ResetScene()
{
}
