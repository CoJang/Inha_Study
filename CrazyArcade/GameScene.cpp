#include "stdafx.h"
#include "SceneManager.h"
#include "GameScene.h"

extern Singleton* singleton;

GameScene::GameScene()
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

	// 52 + 26
	MainChar->InitPlayer({ 78, 26 }, {0, 0}, 1);

	ColliderDrawMode = false;

	// ==Mute==
	//SOUNDMANAGER->PlayBGM();
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

	for (Bomb* B : OtherBombs)
	{
		B->Render(*FrontBuffer, *BackBuffer, ColliderDrawMode);
	}
}

void GameScene::Update()
{
	Timer += ElapseTime;

	MainChar->Update();
	map->Update();
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
