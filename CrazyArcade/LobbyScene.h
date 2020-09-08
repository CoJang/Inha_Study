#pragma once
#include "Objects.h"
#include "Scene.h"

class LobbyScene : public Scene
{
private:
	Objects LobbyImage;
public:
	LobbyScene();
	~LobbyScene();

	void Render();
	void Update();
	void ResetScene();
	void ReceiveData(Packet* data);
};

