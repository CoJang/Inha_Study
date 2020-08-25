#include "stdafx.h"
#include "CollisionManager.h"
#include "Item.h"

extern Singleton* singleton;

Item::Item(POINT pos, int itemtype)
{
	wstring Path = TEXT("images/items/Gift");
	Path += to_wstring(itemtype); Path += TEXT(".bmp");

	AnimObject::Init(Path.c_str(), pos, { -11, -12 });
	AnimObject::InitAnimation(0, 2, 3, 1, 0);
	AnimObject::InitCollider({ 24, 24 }, 32);
	AnimObject::SetImageSize(1.1f);
	AnimObject::SetAnimSpeed(150);

	Type = itemtype;
	IsUpper = true;
	Waterproof = true;
	Timer = 0;
}

Item::~Item()
{
}

void Item::Update()
{
	Timer += ElapseTime;

	if (Timer % 200 < 17)
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
	}

	if (Timer >= 330)
	{
		Waterproof = false;
	}

	AnimObject::Update();
}

