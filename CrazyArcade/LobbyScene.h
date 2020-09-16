#pragma once
#include "Objects.h"
#include "Scene.h"

class LobbyScene : public Scene
{
private:
	Objects MiniMap;
	Objects LobbyImage;
	Objects MyCheckImage;
	Objects OthersCheckImage[3];
	AnimObject StartImage;

	Objects BazzyFace;
	Objects DaoFace;
	Objects OtherChar[3];
	Objects MyChar;

	RECT StartColl;
	int CharFlag;
	int PlayerFlag;
public:
	LobbyScene();
	~LobbyScene();

	void Render();
	void Update();
	void ResetScene();
	void ReceiveData(Packet* data);
	ButtonType CheckClick(POINT mpos, int flag);
};

