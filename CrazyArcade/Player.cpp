#include "stdafx.h"
#include "Objects.h"
#include "Block.h"
#include "MyMath.h"
#include "CollisionManager.h"
#include "Player.h"

extern Singleton* singleton;

Player::Player()
{
	hImage = (HBITMAP)LoadImage(NULL, TEXT("images/char/Role1.bmp"), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hImage, sizeof(BITMAP), &bitImage);

	Sprite_Size.x = bitImage.bmWidth / 6;
	Sprite_Size.y = bitImage.bmHeight / 4;

	Anim_Frame_Max = bitImage.bmWidth / Sprite_Size.x - 1;
	Anim_Frame_Min = 0;
	Anim_Frame_Cur = Anim_Frame_Min;
	Anim_Frame_Flag = 1;

	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;
	Dir = { 0, 0 }; Speed = 10;

	ColPivot = { 26, 48 };
	ColliderSize = { 36, 36 };
	ImageScale = 1.1f;

	MaxBomb = 1;
	BombPower = 1;

	singleton->GetCollisionManager()->SetPlayer(this);
}

Player::~Player()
{
	for (Bomb* B : BombBag)
	{
		delete B;
	}

	BombBag.clear();
}

void Player::InitPlayer(POINT pos, POINT pivot)
{
	ImagePivot = pivot;
	Pos = pos;

	Pos.x -= ImagePivot.x;
	Pos.y -= ImagePivot.y;
}

void Player::SetPlayerDir(POINT dir)
{
	Dir = dir;

	// Left
	if (Dir.x == 1)
	{
		Anim_Frame_Flag = 3;
	} // Right
	else if (Dir.x == -1)
	{
		Anim_Frame_Flag = 2;
	}// Up
	else if (Dir.y == -1)
	{
		Anim_Frame_Flag = 0;
	}// Down
	else if (Dir.y == 1)
	{
		Anim_Frame_Flag = 1;
	}
	else // idle
	{
		Anim_Frame_Cur = Anim_Frame_Min;
	}
}

void Player::Collision()
{
	for (Block* block : BLOCK_VECTOR)
	{
		if (!block->GetColliderState()) continue;

		if (RRCollision(&ColliderBox, &block->GetCollider()))
			RewindMove();
	}

	for (Block* block : OBSTACLE_VECTOR)
	{
		if (RRCollision(&ColliderBox, &block->GetCollider()))
			RewindMove();
	}

	RECT BlockArea;
	for (Bomb* B : BombBag)
	{
		if (B->GetColliderState())
			BlockArea = B->GetCollider();
		else
			continue;

		if (RRCollision(&ColliderBox, &BlockArea))
		{
			RewindMove();
		}
	}

	for (int i = 0; i < ITEM_VECTOR.size(); i++)
	{
		if (RRCollision(&ColliderBox, &ITEM_VECTOR[i]->GetCollider()))
		{
			GetItem(ITEM_VECTOR[i]->GetType());
			delete ITEM_VECTOR[i];
			ITEM_VECTOR.erase(ITEM_VECTOR.begin() + i);
		}
	}
}

void Player::PutBomb()
{
	if (BombBag.size() < MaxBomb)
	{
		Bomb* NewBomb = new Bomb(1, Pos, BombPower);
		BombBag.push_back(NewBomb);
	}
}

void Player::RewindMove()
{
	Pos.x -= Speed * Dir.x;
	Pos.y -= Speed * Dir.y;

	ColliderBox = { Pos.x - ColliderSize.x / 2 + ColPivot.x,
					Pos.y - ColliderSize.y / 2 + ColPivot.y,
					Pos.x + ColliderSize.x / 2 + ColPivot.x,
					Pos.y + ColliderSize.y / 2 + ColPivot.y };
}

void Player::GetItem(ItemType newitem)
{
	switch (newitem)
	{
	case WATER_BOMB:
		MaxBomb++;
		break;
	case ROLLER_SKATE:
		Speed += 2;
		break;
	case FLASK:
		BombPower += 2;
		break;
	}

	ItemBag.push_back(&newitem);
}

void Player::Update()
{
	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;

	UpdateFrame();

	Pos.x += Speed * Dir.x;
	Pos.y += Speed * Dir.y;

	ColliderBox = { Pos.x - ColliderSize.x / 2 + ColPivot.x,
					Pos.y - ColliderSize.y / 2 + ColPivot.y,
					Pos.x + ColliderSize.x / 2 + ColPivot.x,
					Pos.y + ColliderSize.y / 2 + ColPivot.y };


	for (int i = 0; i < BombBag.size(); i++)
	{
		BombBag[i]->Update();

		if (BombBag[i]->GetBombState())
		{
			delete BombBag[i];
			BombBag.erase(BombBag.begin() + i);
		}
	}
}

void Player::Render(HDC front, HDC back, bool ColliderDraw)
{
	AnimObject::Render(front, back, ColliderDraw);

	if(!BombBag.empty())
		for (Bomb* B : BombBag)
		{
			B->Render(front, back, ColliderDraw);
		}
}
