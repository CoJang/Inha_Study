#include "stdafx.h"
#include "LobbyScene.h"

extern Singleton* singleton;

LobbyScene::LobbyScene()
{
	type = LOBBY;
	MoveWindow(NETWORKMANAGER->GetWindowHandle(), 100, 100, 817, 670, false);
	LobbyImage.Init({ 0, 0 }, { 0, 0 });
	LobbyImage.SetImage(GETIMAGE(LOBBY_FRAME));

	MiniMap.Init({ 487, 348 }, { 0, 0 });
	MiniMap.SetImage(GETIMAGE(LOBBY_MINIMAP_FOREST));

	StartImage.Init({ 534, 493 }, { 0, 0 });
	StartImage.SetImage(GETIMAGE(LOBBY_START));
	StartImage.InitCollider({ 95, 28 }, 190, 56);
	StartImage.InitAnimation(0, 0, 1, 2, 0);

	StartColl = StartImage.GetCollider();

	SOUNDMANAGER->AddBGM("sounds/bg/Prepare.mp3");
	SOUNDMANAGER->PlayBGM();
}

LobbyScene::~LobbyScene()
{
}

void LobbyScene::Render()
{
	LobbyImage.Render(*FrontBuffer, *BackBuffer, false);
	MiniMap.Render(*FrontBuffer, *BackBuffer, false);
	StartImage.Render(*FrontBuffer, *BackBuffer, false);

	if (NETWORKMANAGER->GetClientNum() != 0)
	{
		Packet temp; temp.head = COMMAND; temp.Cmd = "NextScene";
		NETWORKMANAGER->SendPacket(temp);
		SOUNDMANAGER->Stop();
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

ButtonType LobbyScene::CheckClick(POINT mpos, int flag)
{
	if (mpos.x < StartColl.right && mpos.x > StartColl.left&&
		mpos.y < StartColl.bottom && mpos.y > StartColl.top)
	{
		StartImage.SetAnimFrameFlag(1);
		StartImage.UpdateFrame();
	}
	else
	{
		StartImage.SetAnimFrameFlag(0);
		StartImage.UpdateFrame();
	}
	return UNKNOWN;
}
