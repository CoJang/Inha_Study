#include "stdafx.h"
#include "TitleScene.h"

extern Singleton singleton;

TitleScene::TitleScene()
{
	type = TITLE;
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

void TitleScene::ShowID()
{
	Timer += ElapseTime;
	SetBkMode(*hdc, OPAQUE);
	SetBkColor(*hdc, BK_Color);
	SetTextColor(*hdc, FT_Color);
	Rectangle(*hdc, ID_Rect.left, ID_Rect.top, ID_Rect.right, ID_Rect.bottom);

	oldFont = (HFONT)SelectObject(*hdc, myFont);

	TextOut(*hdc, 110, 235, TEXT("ENTER YOUR ID"), 13);
	DrawText(*hdc, ID.c_str(), ID.size(), &ID_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	SelectObject(*hdc, oldFont);
	
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
	oldFont = (HFONT)SelectObject(*hdc, myFont);
	Rectangle(*hdc, START_Rect.left, START_Rect.top, START_Rect.right, START_Rect.bottom);
	DrawText(*hdc, TEXT("PRESS TO START"), 14, &START_Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

ButtonType TitleScene::CheckClick(POINT mpos, int flag)
{
	if (mpos.x < START_Rect.right && mpos.x > START_Rect.left &&
		mpos.y < START_Rect.bottom && mpos.y > START_Rect.top)
	{
		if(flag == 0) singleton.GetSceneManager()->NextScene();
	}
	return UNKNOWN;
}

void TitleScene::CheckKeyDown(WPARAM wParam)
{

}


