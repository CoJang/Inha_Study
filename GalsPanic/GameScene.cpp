#include "stdafx.h"
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

	Life = LIFE_MAX;
	Timer = 0;
	GenTime = 333;
	GenPos = { 55, 55 };

	MainChar = new Player;
}

GameScene::~GameScene()
{
	delete MainChar;
}

void GameScene::Render()
{
	if (Life <= 0) return;

	DrawButtons();
	MainChar->Render(*hdc);
}

void GameScene::Update()
{
	if (Life <= 0)
	{
		singleton.GetSceneManager()->UpdateScore(score);
		singleton.GetSceneManager()->NextScene();
		Life = LIFE_MAX;
		score = 0;
		return;
	}

	Timer += ElapseTime;
	GenerateEnemy();

	MainChar->Update();
}

void GameScene::ResetScene()
{
	score = 0;
	myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("Valorant"));
	Life = LIFE_MAX;
	Timer = 0;

	GenPos = { 55, 55 };
	MainChar->SetPos({ 0, 0 });
}

void GameScene::GenerateEnemy()
{
	if (Timer > GenTime)
	{
		GenPos.x += 25;
		if (GenPos.x > WIN_WIDTH) GenPos.x = 10;
		
		Timer = 0;
	}
}


void GameScene::DrawButtons()
{
	oldFont = (HFONT)SelectObject(*hdc, myFont);

	ScoreStr = TEXT("Score : ") + (to_wstring(score));
	DrawText(*hdc, ScoreStr.c_str(), ScoreStr.size(), &SCORE_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	DrawText(*hdc, ID.c_str(), ID.size(), &ID_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	wstring temp = TEXT("LIFE : ") + to_wstring(Life);
	DrawText(*hdc, temp.c_str(), temp.size(), &LIFE_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	SelectObject(*hdc, oldFont);

}

ButtonType GameScene::CheckClick(POINT mpos, int flag)
{
	return UNKNOWN;
}

void GameScene::CheckKeyDown(WPARAM wParam)
{
	static float CharSize = 2.0f;
	if (GetKeyState(VK_NUMPAD8) & 0x8000)
	{
		CharSize += 0.1f;
		MainChar->SetPlayerSize(CharSize);
	}
	else if (GetKeyState(VK_NUMPAD2) & 0x8000)
	{
		CharSize -= 0.1f;
		MainChar->SetPlayerSize(CharSize);
	}

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
}
