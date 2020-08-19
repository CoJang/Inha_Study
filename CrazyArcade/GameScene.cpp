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

	MainChar = new Player;
	map = new Map;
}

GameScene::~GameScene()
{
	delete MainChar;
	delete map;
}

void GameScene::Render()
{
	MainChar->Render(*FrontBuffer);
	map->Render(*FrontBuffer, *BackBuffer);
}

void GameScene::Update()
{
	Timer += ElapseTime;
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

//void GameScene::CheckKeyDown(WPARAM wParam)
//{
//	if (GetKeyState(VK_LEFT) & 0x8000)
//	{
//		MainChar->SetPlayerDir({ -1, 0 });
//	}
//	else if (GetKeyState(VK_DOWN) & 0x8000)
//	{
//		MainChar->SetPlayerDir({ 0, 1 });
//	}
//	else if (GetKeyState(VK_RIGHT) & 0x8000)
//	{
//		MainChar->SetPlayerDir({ 1, 0 });
//	}
//	else if (GetKeyState(VK_UP) & 0x8000)
//	{
//		MainChar->SetPlayerDir({ 0, -1 });
//	}
//	else
//	{
//		MainChar->SetPlayerDir({ 0, 0 });
//	}
//}
