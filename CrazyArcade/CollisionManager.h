#pragma once
#include "Player.h"
#include "Map.h"

class CollisionManager
{
private:
	Player* MainChar;
	Map* map;

public:
	CollisionManager();
	~CollisionManager();

	inline void SetPlayer(Player* instance) { MainChar = instance; };
	inline void SetMap(Map* instance) { map = instance; };
	inline Player* GetPlayer() { return MainChar; };
	inline Map* GetMap() { return map; };
};

