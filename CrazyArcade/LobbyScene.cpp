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

	BazzyFace.Init({ 530, 90 }, { 0, 0 });
	BazzyFace.SetImage(GETIMAGE(LOBBY_BAZZY_FACE));
	BazzyFace.InitCollider({ 42, 42 }, 84);
	
	DaoFace.Init({ 655, 90 }, { 0, 0 });
	DaoFace.SetImage(GETIMAGE(LOBBY_DAO_FACE));
	DaoFace.InitCollider({ 42, 42 }, 84);

	NETWORKMANAGER->SetPlayerFlag();

	if (NETWORKMANAGER->GetNetworkType() == HOST)
	{
		PlayerFlag = 1;
		MyChar.Init({ 35, 125 }, { 0, 0 });
	}

	OtherChar[0].Init({ 145, 125 }, { 0, 0 });
	OtherChar[1].Init({ 250, 125 }, { 0, 0 });
	OtherChar[2].Init({ 355, 125 }, { 0, 0 });
	//OtherChar[0].SetImage(GETIMAGE(LOBBY_DAO_CHAR));
	//OtherChar[1].SetImage(GETIMAGE(LOBBY_DAO_CHAR));
	//OtherChar[2].SetImage(GETIMAGE(LOBBY_DAO_CHAR));

	MyCheckImage.Init({ -100, 0 }, { 0, 0 });
	MyCheckImage.SetImage(GETIMAGE(LOBBY_CHECK2));

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

	BazzyFace.TransRender(*FrontBuffer, *BackBuffer, false);
	DaoFace.TransRender(*FrontBuffer, *BackBuffer, false);
	MyCheckImage.TransRender(*FrontBuffer, *BackBuffer, false);
	MyChar.TransRender(*FrontBuffer, *BackBuffer, false);

	for (int i = 0; i < 3; i++)
	{
		OtherChar[i].TransRender(*FrontBuffer, *BackBuffer, false);
	}

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
	else if(data->head == USERINIT)
	{
		PlayerFlag = data->PlayerFlag;

		switch (PlayerFlag)
		{
		case 2:
			MyChar.SetPos({ 145, 125 });
			OtherChar[0].SetPos({ 35, 125 });
			OtherChar[1].SetPos({ 250, 125 });
			OtherChar[2].SetPos({ 355, 125 });
			break;
		case 3:
			MyChar.SetPos({ 250, 125 });
			OtherChar[0].SetPos({ 35, 125 });
			OtherChar[1].SetPos({ 145, 125 });
			OtherChar[2].SetPos({ 355, 125 });
			break;
		case 4:
			MyChar.SetPos({ 355, 125 });
			OtherChar[0].SetPos({ 35, 125 });
			OtherChar[1].SetPos({ 145, 125 });
			OtherChar[2].SetPos({ 250, 125 });
			break;
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

	// Left Click
	if (flag == 0)
	{
		if (mpos.x < BazzyFace.GetCollider().right && mpos.x > BazzyFace.GetCollider().left&&
			mpos.y < BazzyFace.GetCollider().bottom && mpos.y > BazzyFace.GetCollider().top)
		{
			MyChar.SetImage(GETIMAGE(LOBBY_BAZZY_CHAR));
			MyCheckImage.SetPos({ 580, 90 });
			CharFlag = 0;

			//Packet temp; temp.head = USERINIT; temp.Cmd = "NextScene";
			//NETWORKMANAGER->SendPacket(temp);
		}

		if (mpos.x < DaoFace.GetCollider().right && mpos.x > DaoFace.GetCollider().left&&
			mpos.y < DaoFace.GetCollider().bottom && mpos.y > DaoFace.GetCollider().top)
		{
			MyChar.SetImage(GETIMAGE(LOBBY_DAO_CHAR));
			MyCheckImage.SetPos({ 705, 90 });
			CharFlag = 1;
		}
	}

	return UNKNOWN;
}
