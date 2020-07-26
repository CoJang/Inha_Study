#pragma once
#include "stdafx.h"
#include "Scene.h"

class TitleScene : public Scene
{
private:
	wstring Title;

	RECT ID_Rect;
	RECT TITLE_Rect;
	RECT START_Rect;

	int BK_Color;
	int FT_Color;
	int blinktime;
	int Timer;
public:
	TitleScene();
	~TitleScene();

	void SetID(wstring input) { ID = input; };
	wstring GetID(){ return ID; };

	void ShowID();
	void DrawButtons();
	ButtonType CheckClick(POINT mpos, int flag);
	void CheckKeyDown(WPARAM wParam);

	void Render();
	void Update();
	void ResetScene();
};

