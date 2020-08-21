#include "stdafx.h"
#include "SceneManager.h"
#include "GameScene.h"

extern Singleton singleton;

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
	MainChar->InitPlayer({ 52, 0 }, {-26, -26});

	ColliderDrawMode = false;
}

GameScene::~GameScene()
{
	delete MainChar;
	delete map;
}

void GameScene::Render()
{
	map->FrontRender(*FrontBuffer, *BackBuffer);
	map->BackRender(*FrontBuffer, *BackBuffer, ColliderDrawMode);
	MainChar->Render(*FrontBuffer, *BackBuffer, ColliderDrawMode);
}

void GameScene::Update()
{
	Timer += ElapseTime;

	MainChar->Update();
	MainChar->Collision(map->GetBlocks());
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
	DrawText(*FrontBuffer, ID.c_str(), ID.size(), &ID_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	SelectObject(*FrontBuffer, oldFont);
}

ButtonType GameScene::CheckClick(POINT mpos, int flag)
{
	return UNKNOWN;
}

void GameScene::CheckKeyDown()
{
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		MainChar->SetPlayerDir({ -1, 0 });
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		MainChar->SetPlayerDir({ 0, 1 });
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		MainChar->SetPlayerDir({ 1, 0 });
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		MainChar->SetPlayerDir({ 0, -1 });
	}
	else
	{
		MainChar->SetPlayerDir({ 0, 0 });
	}

	if (GetAsyncKeyState(VK_TAB) & 0x0001)
	{
		ColliderDrawMode ^= true;
	}
}
