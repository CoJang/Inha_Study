#include "stdafx.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
	MainChar = NULL;
	map = NULL;
}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::ResetCollisionManager()
{
	HitableBlocks.clear();
	ObstacleBlocks.clear();
	Items.clear();
	OtherBombs.clear();
	OtherPlayers.clear();
}
