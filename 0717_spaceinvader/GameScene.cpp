#include "stdafx.h"
#include "GameScene.h"

extern SceneManager manager;

GameScene::GameScene()
{
	type = GAME;
	ID_Rect = { 0, 15, 200, 35 };
	SCORE_Rect = { 200, 15, 450, 35 };
	LIFE_Rect = { 200, 55, 450, 75 };
	score = 0;
	myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("Valorant"));

	Tower = new GunTower;
	Life = LIFE_MAX;
	Timer = 0;
	GenTime = 333;
	GenPos = { 55, 55 };

	for (int i = 0; i < ENEMY_MAX; i++)
		Enemys[i] = new Enemy;
}

GameScene::~GameScene()
{
	DeleteObject(myFont);
	delete Tower;

	for (int i = 0; i < ENEMY_MAX; i++)
		delete Enemys[i];
}

void GameScene::Render()
{
	if (Life <= 0) return;

	DrawButtons();
	Tower->Render(*hdc);

	for (int i = 0; i < ENEMY_MAX; i++)
		if (Enemys[i]->GetState() != NOT_ACTIVE)
		{
			Enemys[i]->Render(*hdc);
		}
}

void GameScene::Update()
{
	if (Life <= 0)
	{
		manager.UpdateScore(score);
		manager.NextScene();
		Life = LIFE_MAX;
		score = 0;
		return;
	}

	Timer += ElapseTime;
	GenerateEnemy();
	Tower->Update();

	for (int i = 0; i < ENEMY_MAX; i++)
		if (Enemys[i]->GetState() != NOT_ACTIVE)
		{
			Enemys[i]->Update();
			if (Enemys[i]->IsCollision(Tower->bullets)) score += 100;

			if (Enemys[i]->GetPos().y > WIN_HEIGHT + 30)
			{
				Life--;
				Enemys[i]->SetState(NOT_ACTIVE);
			}
		}
}

void GameScene::GenerateEnemy()
{
	if (Timer > GenTime)
	{
		GenPos.x += 25;
		if (GenPos.x > WIN_WIDTH) GenPos.x = 10;

		for (int i = 0; i < ENEMY_MAX; i++)
			if (Enemys[i]->GetState() == NOT_ACTIVE)
			{
				Enemys[i]->SetState(ACTIVE);
				Enemys[i]->SetPos(GenPos);
				break;
			}
		
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
	POINT pos = Tower->GetTowerPos();
	float tempangle = Rad2Deg(atan2(pos.y - mpos.y, pos.x - mpos.x));
	Tower->Rotate(tempangle);

	return UNKNOWN;
}

void GameScene::CheckKeyDown(WPARAM wParam)
{
	if (wParam == VK_SPACE)
	{
		Tower->Shot(*hdc);
	}
}
