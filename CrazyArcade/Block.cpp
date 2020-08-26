#include "stdafx.h"
#include "Item.h"
#include "CollisionManager.h"
#include "ImageManager.h"
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
	int RandomNum = GenerateRandomNum(ITEM_BOMB, ITEM_FLASK + 2);
	if (RandomNum > ITEM_FLASK) return;

	Item* tempItem = new Item(Pos, RandomNum);
	ITEM_VECTOR.push_back(tempItem);
}
