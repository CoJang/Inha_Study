#include "stdafx.h"
#include "Item.h"
#include "CollisionManager.h"
#include "Block.h"

extern Singleton* singleton;

Block::Block()
{
	Pos = { -1, -1 };
	ImagePivot = { 0, 0 };
	ColPivot = { 26, 33 };
	ColliderSize = {48, 48};

	IsColliderActive = true;
	IsDestructible = false;
}

Block::~Block()
{
}

void Block::Render(HDC front, HDC back, bool ColliderDraw)
{
	if (Pos.x == -1 || Pos.y == -1) return;

	AnimObject::Render(front, back, ColliderDraw);
}

void Block::Update()
{
	AnimObject::Update();
}

void Block::UpdateFrame()
{
	AnimObject::UpdateFrame();
}

void Block::CreateItem()
{
	int RandomNum = GenerateRandomNum(0, 4);
	if (RandomNum == 0 || RandomNum == 4) return;
	Item* tempItem = new Item(Pos, RandomNum);
	ITEM_VECTOR.push_back(tempItem);
}
