#include "stdafx.h"
#include "SceneManager.h"
#include "GameScene.h"

extern Singleton* singleton;

GameScene::GameScene(int playerFlag, int charFlag)
	: PlayerFlag(playerFlag), CharFlag(charFlag)
{
	type = GAME;
	ID_Rect = { 0, 15, 200, 35 };
	SCORE_Rect = { 200, 15, 450, 35 };
	LIFE_Rect = { 200, 55, 450, 75 };
	score = 0;
	myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("Valorant"));

	Timer = 0;

	map = new Map;
	MainChar = new Player;
	OtherChar = new Player;

	ColliderDrawMode = false;

	SpawnPoints[0] = { 78, 78 };
	SpawnPoints[1] = { 702, 78 };
	SpawnPoints[2] = { 78, 598 };
	SpawnPoints[3] = { 702, 598 };

	// ==Mute==
#if !_DEBUG
	SOUNDMANAGER->AddBGM("sounds/bg/Forest.mp3");
	SOUNDMANAGER->PlayBGM();
#endif
	if (NETWORKMANAGER->GetNetworkType() == HOST)
	{
		NETWORKMANAGER->SetPlayerFlag();
	}

	MainChar->InitPlayer(SpawnPoints[PlayerFlag - 1], { 0, 0 }, PlayerFlag, CharFlag);
	singleton->GetCollisionManager()->SetPlayer(MainChar);

	Packet temp; temp.head = USERINIT;
	temp.Pos = MainChar->GetPos();
	temp.PlayerFlag = PlayerFlag;
	temp.Power = CharFlag;
	NETWORKMANAGER->SendPacket(temp);
	
	MoveWindow(NETWORKMANAGER->GetWindowHandle(), 100, 100, WIN_WIDTH, WIN_HEIGHT, false);
}

GameScene::~GameScene()
{
	delete MainChar;
	delete map;
}

void GameScene::Render()
{
	map->FrontRender(*FrontBuffer, *BackBuffer, ColliderDrawMode);
	map->BackRender(*FrontBuffer, *BackBuffer, ColliderDrawMode);
	MainChar->Render(*FrontBuffer, *BackBuffer, ColliderDrawMode);
	OtherChar->Render(*FrontBuffer, *BackBuffer, ColliderDrawMode);

	for (Bomb* B : OtherBombs)
	{
		B->Render(*FrontBuffer, *BackBuffer, ColliderDrawMode);
	}
}

void GameScene::Update()
{
	Timer += ElapseTime;

	MainChar->Update();
	OtherChar->Update();
	map->Update();

	for (int i = 0; i < OtherBombs.size(); i++)
	{
		OtherBombs[i]->Update();

		if (OtherBombs[i]->GetBombState())
		{
			delete OtherBombs[i];
			OtherBombs.erase(OtherBombs.begin() + i);
		}
	}
}

void GameScene::ResetScene()
{
	score = 0;
	myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("Valorant"));
	Timer = 0;
}

void GameScene::DrawButtons()
{
	oldFont = (HFONT)SelectObject(*FrontBuffer, myFont);

	ScoreStr = TEXT("Score : ") + (to_wstring(score));
	DrawText(*FrontBuffer, ScoreStr.c_str(), ScoreStr.size(), &SCORE_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	DrawTextA(*FrontBuffer, IP.c_str(), IP.size(), &ID_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	SelectObject(*FrontBuffer, oldFont);
}

ButtonType GameScene::CheckClick(POINT mpos, int flag)
{
	return UNKNOWN;
}

void GameScene::CheckKeyDown()
{
	MainChar->SetPlayerDir();

	if (GetAsyncKeyState(VK_TAB) & 0x0001)
	{
		ColliderDrawMode ^= true;
	}
}

void GameScene::ReceiveData(Packet* data)
{
	// 1p {78, 78}, 2p {702, 78}, 3p{78, 598}, 4p{702, 598}
	switch (data->head)
	{
	case COMMAND:
		return;
	case BOMB:
		{
			Bomb* NewBomb = new Bomb(data->PlayerFlag, data->Pos, data->Power);
			OtherBombs.push_back(NewBomb);
			BOMB_VECTOR.push_back(NewBomb);
		}
		return;
	case USER:
		OtherChar->SetPos(data->Pos);
		OtherChar->SetPlayerDir(data->Input);
		if (data->IsTrapped == true)
			OtherChar->TrapPlayer();
		return;
	case ITEM:
		{
			Item* tempItem = new Item(data->Pos, data->Power);
			ITEM_VECTOR.push_back(tempItem);
		}
		return;
	case USERINIT:
		{
			OtherChar->InitPlayer(data->Pos, { 0, 0 }, data->PlayerFlag, data->Power);
		}
		return;
	default:
		return;
	}
}

