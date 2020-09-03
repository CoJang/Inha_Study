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
		static POINT Pos = { 100, 100 };
		for (int i = 0; i < NETWORKMANAGER->GetClientNum(); i++)
		{
			Rectangle(*FrontBuffer, Pos.x * (i + 1) - 30, Pos.y * (i + 1) - 30,
								    Pos.x * (i + 1) + 30, Pos.y * (i + 1) + 30);
		}
	}
}

void LobbyScene::Update()
{
}

void LobbyScene::ResetScene()
{
}
