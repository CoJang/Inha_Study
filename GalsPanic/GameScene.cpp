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

	Life = LIFE_MAX;
	Timer = 0;
	GenTime = 333;

	Map = new MyMap;
	MainChar = new Player;
	Background = new ImageObject;

	MainChar->InitPlayer(Map);
}

GameScene::~GameScene()
{
	delete MainChar;
	delete Map;
	delete Background;
}

void GameScene::Render()
{
	if (Life <= 0) return;

	// Hide Background Image with Bitmap
	HBITMAP BackBitmap = CreateCompatibleBitmap(*FrontBuffer, WIN_WIDTH, WIN_HEIGHT);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(*BackBuffer, BackBitmap);

	// First Priority [ Background ], Render Target : BackBuffer
	Background->Render(*FrontBuffer, *BackBuffer);

	// Copy [ BackBuffer -> FrontBuffer ]
	BitBlt(*FrontBuffer, 0, 0, WIN_WIDTH, WIN_HEIGHT, *BackBuffer, 0, 0, SRCCOPY);
	SelectObject(*BackBuffer, oldBitmap);

	// Hide again & Use BackBuffer again
	HBITMAP BackBitmap1 = CreateCompatibleBitmap(*FrontBuffer, WIN_WIDTH, WIN_HEIGHT);
	HBITMAP oldBitmap1 = (HBITMAP)SelectObject(*BackBuffer, BackBitmap1);
	
	// Render Target : BackBuffer
	Map->Render(*FrontBuffer, *BackBuffer);

	// Copy & Filtering [ BackBuffer -> Front Buffer ]
	TransparentBlt(*FrontBuffer, 0, 0, WIN_WIDTH, WIN_HEIGHT,
		*BackBuffer, 0, 0, WIN_WIDTH, WIN_HEIGHT, RGB(0, 0, 0));
	SelectObject(*BackBuffer, BackBitmap1);

	DrawButtons();
	MainChar->Render(*FrontBuffer, *BackBuffer);

	DeleteObject(oldBitmap);
	DeleteObject(oldBitmap1);
	DeleteObject(BackBitmap);
	DeleteObject(BackBitmap1);
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
	MainChar->Update();
	Map->Update();
}

void GameScene::ResetScene()
{
	score = 0;
	myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("Valorant"));
	Life = LIFE_MAX;
	Timer = 0;

	MainChar->SetPos({ 0, 0 });
}

void GameScene::DrawButtons()
{
	oldFont = (HFONT)SelectObject(*FrontBuffer, myFont);

	ScoreStr = TEXT("Score : ") + (to_wstring(score));
	DrawText(*FrontBuffer, ScoreStr.c_str(), ScoreStr.size(), &SCORE_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	DrawText(*FrontBuffer, ID.c_str(), ID.size(), &ID_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	wstring temp = TEXT("LIFE : ") + to_wstring(Life);
	DrawText(*FrontBuffer, temp.c_str(), temp.size(), &LIFE_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	SelectObject(*FrontBuffer, oldFont);

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
