#include "stdafx.h"
#include "Block.h"

Block::Block()
{
	Pos = { -1, -1 };
	ImagePivot = { 0, 0 };
	ColPivot = { 26, 36 };
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
