#include "stdafx.h"
#include "GameOverScene.h"

extern SceneManager manager;

GameOverScene::GameOverScene()
{
	type = GAMEOVER;

	RANK_Rect = { 0, 112, 434, 550 };
	RANK_smallRect = { 2, 312, 434, 550 };
	START_Rect = { 0, 650, 434, 742 };
	RETRY_Rect = {0, 650, 150, 742};
	QUIT_Rect = { 284, 650, 434, 742 };

	ID_Rect = { -16, 150, WIN_WIDTH, 220 };
	SCORE_Rect = { -16, 220, WIN_WIDTH, 290 };

	myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("Valorant"));
}

GameOverScene::~GameOverScene()
{
	DeleteObject(myFont);
}

void GameOverScene::Update()
{
	str = TEXT("SCORE : ") + to_wstring(manager.GetScore());
}

void GameOverScene::Render()
{
	myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("Valorant"));

	Rectangle(*hdc, RANK_Rect.left, RANK_Rect.top, RANK_Rect.right, RANK_Rect.bottom);
	//Rectangle(*hdc, START_Rect.left, START_Rect.top, START_Rect.right, START_Rect.bottom);
	Rectangle(*hdc, RETRY_Rect.left, RETRY_Rect.top, RETRY_Rect.right, RETRY_Rect.bottom);
	Rectangle(*hdc, QUIT_Rect.left, QUIT_Rect.top, QUIT_Rect.right, QUIT_Rect.bottom);

	oldFont = (HFONT)SelectObject(*hdc, myFont);
	TextOut(*hdc, 150, 100, TEXT("- RANK -"), 8);
	DrawText(*hdc, ID.c_str(), ID.size(), &ID_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	DrawText(*hdc, str.c_str(), str.size(), &SCORE_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	DrawText(*hdc, TEXT("RETRY"), 5, &RETRY_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	DrawText(*hdc, TEXT("QUIT"), 4, &QUIT_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	if (!Loadstr.empty())
	{
		myFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("Valorant"));
		oldFont = (HFONT)SelectObject(*hdc, myFont);
		DrawText(*hdc, Loadstr.c_str(), Loadstr.size(), &RANK_smallRect, DT_LEFT);
	}
	else
		FileLoad(TEXT("Ranking.dat"));

	SelectObject(*hdc, oldFont);
}

void GameOverScene::FileSave(wstring ID, int Score)
{
	wofstream DstFile;
	//char buff = 0;

	DstFile.open(TEXT("Ranking.dat"), ios_base::binary | ios_base::out | ios_base::app);

	if (!DstFile.good())
	{
		printf("ERROR! FileSave DstFile OpenFailed!\n"); return;
	}

	wstring temp;
	temp += TEXT("ID : ") + ID + TEXT("        SCORE : ") + to_wstring(Score) + TEXT("\n");
	DstFile.write(temp.c_str(), temp.size());

	DstFile.close();
}

void GameOverScene::FileLoad(TCHAR* srcFileName)
{
	wifstream SrcFile;
	TCHAR buff = 0;

	wstring id;
	string score;
	int count = 0;

	SrcFile.open(srcFileName, ios_base::binary | ios_base::in);

	if (!SrcFile.good())
	{
		printf("ERROR! FileLoad SrcFile OpenFailed!\n"); return;
	}

	while (SrcFile.get(buff))
	{
		if (buff == ':') count++;

		if (count == 1 && buff != ':')
		{
			id += buff;
		}

		if (count == 2 && isdigit(buff))
		{
			score += buff;
		}

		if (buff == '\n')
		{
			count = 0;
			int temp = atoi(score.c_str());
			score = "";
			id = TEXT("");
			ScoreList.push_back(temp);
			IDList.push_back(id);
		}

		Loadstr += buff;
	}

	SrcFile.close();
}

ButtonType GameOverScene::CheckClick(POINT mpos, int flag)
{
	if (mpos.x < RETRY_Rect.right && mpos.x > RETRY_Rect.left &&
		mpos.y < RETRY_Rect.bottom && mpos.y > RETRY_Rect.top)
	{
		if (flag == 0)
		{
			FileSave(ID, manager.GetScore());
			manager.PrevScene();
			Loadstr.clear();
		}
	}

	if (mpos.x < QUIT_Rect.right && mpos.x > QUIT_Rect.left &&
		mpos.y < QUIT_Rect.bottom && mpos.y > QUIT_Rect.top)
	{
		if (flag == 0) 
		{ 
			FileSave(ID, manager.GetScore());
			Loadstr.clear();
			PostQuitMessage(0);
		}
	}

	return UNKNOWN;
}