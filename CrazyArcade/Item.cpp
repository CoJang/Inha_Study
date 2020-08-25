#include "stdafx.h"
#include "CollisionManager.h"
#include "Item.h"

extern Singleton* singleton;

Item::Item(ItemType itemtype)
{
	AnimObject::Init(TEXT("images/items/Gift1.bmp"), { 0, 52 }, { -26, -48 });
	AnimObject::InitAnimation(0, 2, 3, 1, 0);
	AnimObject::InitCollider({ 24, 24 }, 32);
	AnimObject::SetImageSize(1.1f);
	AnimObject::SetAnimSpeed(150);

	Type = itemtype;
	IsUpper = true;
	Timer = 0;
}

Item::~Item()
{
}

void Item::Update()
{
	Timer += ElapseTime;

	if (Timer >= 200)
	{
		if (IsUpper)
		{
			Pos.y -= 5;
			IsUpper = false;
		}
		else
		{
			Pos.y += 5;
			IsUpper = true;
		}

		Timer = 0;
	}

	AnimObject::Update();
}

