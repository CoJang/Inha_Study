#pragma once
#include "Singleton.h"

struct Packet;

enum SceneType
{
	TITLE,
	LOBBY,
	GAME,
	GAMEOVER,
	DEFAULT
};

enum ButtonType
{
	NEXT,
	PREVIOUS,
	QUIT,

	UNKNOWN = 99
};

class Scene
{
protected:
	string IP;
	wstring ID;
	SceneType type;

	HFONT myFont;
	HFONT oldFont;

	HDC* FrontBuffer;
	HDC* BackBuffer;
public:
	Scene() { type = DEFAULT; };
	virtual ~Scene() {};
	void InitScene(HDC* Front, HDC* Back) { FrontBuffer = Front; BackBuffer = Back; };

	virtual void SetIP(string input) { IP = input; };
	virtual void SetID(wstring input) { ID = input; };
	virtual wstring GetID() { return ID; };
	virtual void ShowID() {};

	virtual void DrawButtons() {};
	virtual ButtonType CheckClick(POINT mpos, int flag) { return UNKNOWN; };
	virtual void CheckKeyDown() { };

	int GetType() { return type; };
	void SetType(SceneType input) { type = input; };

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void ResetScene() = 0;

	virtual void ReceiveData(Packet* data) {};
};
