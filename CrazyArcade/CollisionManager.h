#pragma once
#include "Player.h"
#include "Map.h"

class CollisionManager
{
private:
	Player* MainChar;
	Map* map;

	vector<Block*> HitableBlocks;
	vector<Block*> ObstacleBlocks;
public:
	CollisionManager();
	~CollisionManager();

	inline void SetPlayer(Player* instance) { MainChar = instance; };
	inline void SetMap(Map* instance) { map = instance; };
	inline Player* GetPlayer() { return MainChar; };
	inline Map* GetMap() { return map; };

	inline vector<Block*> & GetObstacles() { return ObstacleBlocks; };
	inline vector<Block*> & GetBlocks() { return HitableBlocks; };
};

