#include "stdafx.h"
#include "Objects.h"
#include "Block.h"
#include "MyMath.h"
#include "CollisionManager.h"
#include "ImageManager.h"
#include "Player.h"


extern Singleton* singleton;

Player::Player()
{
	SetImage(GETIMAGE(CHAR_BAZZY));

	AnimObject::InitAnimation(0, 5, 6, 4, 1);

	Dir = { 0, 0 }; Speed = 10;

	ColPivot = { 26, 48 };
	ColliderSize = { 36, 36 };
	ImageScale = 1.1f;

	MaxBomb = 2;
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

void Player::SetPlayerDir()
{
	static bool IsKeyDown = false;

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		IsKeyDown = true;
		Anim_Frame_Flag = 2;
		Dir = { -1, 0 };
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		Anim_Frame_Flag = 3;
		IsKeyDown = true;
		Dir = { 1, 0 };
	}

	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		IsKeyDown = true;
		Anim_Frame_Flag = 1;
		Dir = { 0, 1 };
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		IsKeyDown = true;
		Anim_Frame_Flag = 0;
		Dir = { 0, -1 };
	}

	if (!IsKeyDown)
	{
		Dir = { 0, 0 };
		Anim_Frame_Cur = Anim_Frame_Min;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		PutBomb();
	}

	IsKeyDown = false;
}

void Player::Collision()
{
	for (Block* block : BLOCK_VECTOR)
	{
		if (!block->GetColliderState()) continue;

		RECT rt = block->GetCollider();
		POINT rtsize = block->GetColliderSize();

		if (RRCollision(&ColliderBox, &block->GetCollider()))
		{
			RewindMove();

			if (Pos.x < rt.right && Pos.x > rt.left && Pos.y > rt.top && Pos.y < rt.bottom)
			{
				if (Pos.y > block->GetPos().y)
					Pos.x += 1;
				else if (Pos.y < block->GetPos().y)
					Pos.x -= 1;
			}

			UpdateColliderBox();
		}
	}

	for (Block* block : OBSTACLE_VECTOR)
	{
		if (ObstacleCollision(block))
			RewindMove();
	}

	for (Bomb* B : BombBag)
	{
		if (!B->GetColliderState())
			continue;

		if (ObstacleCollision(B))
		{
			RewindMove();
		}
	}

	for (int i = 0; i < ITEM_VECTOR.size(); i++)
	{
		if (RRCollision(&ColliderBox, &ITEM_VECTOR[i]->GetCollider()))
		{
			SOUNDMANAGER->PlaySFX("ItemGet");
			GetItem(ITEM_VECTOR[i]->GetType());
			delete ITEM_VECTOR[i];
			ITEM_VECTOR.erase(ITEM_VECTOR.begin() + i);
		}
	}
}

void Player::UpdateColliderBox()
{
	ColliderBox = { Pos.x - ColliderSize.x / 2 + ColPivot.x,
					Pos.y - ColliderSize.y / 2 + ColPivot.y,
					Pos.x + ColliderSize.x / 2 + ColPivot.x,
					Pos.y + ColliderSize.y / 2 + ColPivot.y };
}

void Player::PutBomb()
{
	if (BombBag.size() < MaxBomb)
	{
		SOUNDMANAGER->PlaySFX("BombPut");

		Bomb* NewBomb = new Bomb(1, Pos, BombPower);
		if (NewBomb->GetPos().x > 780 || NewBomb->GetPos().x < 26 ||
			NewBomb->GetPos().y > 676 || NewBomb->GetPos().y < 52)
		{
			delete NewBomb;
			return;
		}
		BombBag.push_back(NewBomb);
		BOMB_VECTOR.push_back(NewBomb);
	}
}

void Player::RewindMove()
{
	Pos.x -= Speed * Dir.x;
	Pos.y -= Speed * Dir.y;

	UpdateColliderBox();
}

void Player::GetItem(int newitem)
{
	switch (newitem)
	{
	case ITEM_BOMB:
		if (MaxBomb <= BOMB_LIMIT)
		{
			MaxBomb++;
			ItemBag.push_back(&newitem);
		}
		break;
	case ITEM_SKATE:
		if (Speed <= SPEED_LIMIT)
		{
			Speed += 2;
			ItemBag.push_back(&newitem);
		}
		break;
	case ITEM_FLASK:
		if (BombPower <= POWER_LIMIT)
		{
			BombPower++;
			ItemBag.push_back(&newitem);
		}
		break;
	}
}

bool Player::ObstacleCollision(Objects* other)
{
	RECT rt = other->GetCollider();
	POINT size = other->GetColliderSize();

	// x axis collision
	//if (ColliderBox.right > rt.left +  &&
	//	ColliderBox.left < rt.right)
	//{

	//}

	return false;
}

void Player::Update()
{
	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;

	UpdateFrame();

	Pos.x += Speed * Dir.x;
	Pos.y += Speed * Dir.y;

	UpdateColliderBox();
	Collision();

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
