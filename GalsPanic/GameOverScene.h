#pragma once
#include "stdafx.h"
#include "Scene.h"

class GameOverScene : public Scene
{
private:
	wstring str;
	RECT ID_Rect;
	RECT SCORE_Rect;
	RECT RANK_Rect;
	RECT RANK_smallRect;
	RECT START_Rect;

	RECT RETRY_Rect;
	RECT QUIT_Rect;

	wstring Loadstr;
	vector<int> ScoreList;
	vector<wstring> IDList;
public:
	GameOverScene();
	~GameOverScene();

	void Update();
	void Render();
	void FileSave(wstring ID, int Score);
	void FileLoad(TCHAR* dstFileName);
	ButtonType CheckClick(POINT mpos, int flag);
};

