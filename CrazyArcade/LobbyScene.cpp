#include "stdafx.h"
#include "LobbyScene.h"

extern Singleton* singleton;

LobbyScene::LobbyScene()
{
	type = LOBBY;
	MoveWindow(NETWORKMANAGER->GetWindowHandle(), 100, 100, 817, 670, false);
	LobbyImage.Init({ 0, 0 }, { 0, 0 });
	LobbyImage.SetImage(GETIMAGE(LOBBY_FRAME));

	SOUNDMANAGER->AddBGM("sounds/bg/Prepare.mp3");
	SOUNDMANAGER->PlayBGM();
}

LobbyScene::~LobbyScene()
{
}

void LobbyScene::Render()
{
	LobbyImage.Render(*FrontBuffer, *BackBuffer, false);

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

void LobbyScene::ReceiveData(Packet* data)
{
	if (data->head == COMMAND)
	{
		if (strcmp(data->Cmd.c_str(), "NextScene") == 0)
		{
			singleton->GetSceneManager()->NextScene();
		}
	}
}
