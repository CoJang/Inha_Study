#include "stdafx.h"
#include "SceneManager.h"
#include "TitleScene.h"

extern Singleton* singleton;

TitleScene::TitleScene()
{
	type = TITLE;
	//IP = "221.140.229.28";
	IP = "165.246.192.68";
	ID = TEXT("Unknown");
	ID_Rect = {0, 250, 450, 450};
	START_Rect = { 0, 650, 450, 742 };
	BK_Color = 0x00000000;
	FT_Color = 0x00ffffff;
	blinktime = 400; Timer = 0;
	myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("Valorant"));
}


TitleScene::~TitleScene()
{
	DeleteObject(myFont);
}

void TitleScene::Render()
{
	ShowID();
	DrawButtons();
}

void TitleScene::Update()
{

}

void TitleScene::ResetScene()
{
	ID = TEXT("Unknown");
	Timer = 0;
	myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("Valorant"));
}

void TitleScene::ShowID()
{
	Timer += ElapseTime;
	SetBkMode(*FrontBuffer, OPAQUE);
	SetBkColor(*FrontBuffer, BK_Color);
	SetTextColor(*FrontBuffer, FT_Color);
	Rectangle(*FrontBuffer, ID_Rect.left, ID_Rect.top, ID_Rect.right, ID_Rect.bottom);

	oldFont = (HFONT)SelectObject(*FrontBuffer, myFont);

	TextOutA(*FrontBuffer, 110, 235, "ENTER IP", 9);
	DrawTextA(*FrontBuffer, IP.c_str(), IP.size(), &ID_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	SelectObject(*FrontBuffer, oldFont);

	if (blinktime < Timer)
	{
		int temp = BK_Color;
		BK_Color = FT_Color;
		FT_Color = temp;
		Timer = 0;
	}
}

void TitleScene::DrawButtons()
{
	oldFont = (HFONT)SelectObject(*FrontBuffer, myFont);
	Rectangle(*FrontBuffer, START_Rect.left, START_Rect.top, START_Rect.right, START_Rect.bottom);
	DrawText(*FrontBuffer, TEXT("PRESS TO START"), 14, &START_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

ButtonType TitleScene::CheckClick(POINT mpos, int flag)
{
	if (mpos.x < START_Rect.right && mpos.x > START_Rect.left &&
		mpos.y < START_Rect.bottom && mpos.y > START_Rect.top)
	{
		if (flag == 0)
		{
			NETWORKMANAGER->SetIP(IP);

			if (singleton->GetNetworkManager()->OperateServer())
			{
				singleton->GetSceneManager()->NextScene();
			}
		}
	}
	return UNKNOWN;
}

void TitleScene::CheckKeyDown()
{

}


