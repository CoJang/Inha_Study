#pragma once
#include "Scene.h"

class LobbyScene : public Scene
{
private:

public:
	LobbyScene();
	~LobbyScene();

	void Render();
	void Update();
	void ResetScene();
};

