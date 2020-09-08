#pragma once
#include "Objects.h"
#include "Scene.h"

class LobbyScene : public Scene
{
private:
	Objects MiniMap;
	Objects LobbyImage;
	Objects MyCheckImage;
	Objects OthersCheckImage;
	AnimObject StartImage;
	AnimObject BazzyPickImage;

	RECT StartColl;
	RECT* BazzyColl;
public:
	LobbyScene();
	~LobbyScene();

	void Render();
	void Update();
	void ResetScene();
	void ReceiveData(Packet* data);
	ButtonType CheckClick(POINT mpos, int flag);
};

