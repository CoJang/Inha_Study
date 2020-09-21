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
	Dir = { 0, 0 }; Speed = 10;

	ColPivot = { 26, 48 };
	ColliderSize = { 36, 36 };
	ImageScale = 1.1f;

	MaxBomb = 2;
	BombPower = 1;

	IsTrapped = false;
	IsDeath = false;

	DeathAnim = 0;
	DeathTimer = 0;
	LifeTime = 2000;

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

void Player::InitPlayer(POINT pos, POINT pivot, int playerflag, int charflag)
{
	if (charflag == 0)
	{
		SetImage(GETIMAGE(CHAR_BAZZY));
		DeathImage[0] = GETIMAGE(CHAR_BAZZY_TRAP);
		GetObject(DeathImage[0], sizeof(BITMAP), &DeathBitmap[0]);
		DeathImage[1] = GETIMAGE(CHAR_BAZZY_DIE);
		GetObject(DeathImage[1], sizeof(BITMAP), &DeathBitmap[1]);
	}
	else if (charflag == 1)
	{
		SetImage(GETIMAGE(CHAR_DAO));
		DeathImage[0] = GETIMAGE(CHAR_DAO_TRAP);
		GetObject(DeathImage[0], sizeof(BITMAP), &DeathBitmap[0]);
		DeathImage[1] = GETIMAGE(CHAR_DAO_DIE);
		GetObject(DeathImage[1], sizeof(BITMAP), &DeathBitmap[1]);
	}

	AnimObject::InitAnimation(0, 5, 6, 4, 1);

	ImagePivot = pivot;
	Pos = pos;
	PlayerFlag = playerflag;
}

void Player::SetPlayerDir()
{
	static bool IsKeyDown = false;
	Packet temp; temp.head = USER; temp.PlayerFlag = PlayerFlag;
	temp.Pos = Pos; temp.IsTrapped = IsTrapped; temp.IsDeath = IsDeath;

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		IsKeyDown = true;
		Dir = { -1, 0 };
		if(!IsTrapped && !IsDeath)
			Anim_Frame_Flag = 2;

		temp.Input = VK_LEFT;
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		IsKeyDown = true;
		Dir = { 1, 0 };
		if (!IsTrapped && !IsDeath)
			Anim_Frame_Flag = 3;

		temp.Input = VK_RIGHT;
	}

	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		IsKeyDown = true;
		Dir = { 0, 1 };
		if (!IsTrapped && !IsDeath)
			Anim_Frame_Flag = 1;

		temp.Input = VK_DOWN;
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		IsKeyDown = true;
		Dir = { 0, -1 };
		if (!IsTrapped && !IsDeath)
			Anim_Frame_Flag = 0;

		temp.Input = VK_UP;
	}

	if (!IsKeyDown)
	{
		Dir = { 0, 0 };

		if (!IsTrapped && !IsDeath)
			Anim_Frame_Cur = Anim_Frame_Min;

		temp.Input = 0;
	}

	NETWORKMANAGER->SendPacket(temp);

	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		if(!IsTrapped && !IsDeath)
			PutBomb();
	}

	IsKeyDown = false;
}

void Player::SetPlayerDir(int KeyState)
{
	if (KeyState == VK_LEFT)
	{
		Dir = { -1, 0 };
		if (!IsTrapped && !IsDeath)
			Anim_Frame_Flag = 2;
	}
	else if (KeyState == VK_RIGHT)
	{
		Dir = { 1, 0 };
		if (!IsTrapped && !IsDeath)
			Anim_Frame_Flag = 3;
	}

	else if (KeyState == VK_DOWN)
	{
		Dir = { 0, 1 };
		if (!IsTrapped && !IsDeath)
			Anim_Frame_Flag = 1;
	}
	else if (KeyState == VK_UP)
	{
		Dir = { 0, -1 };
		if (!IsTrapped && !IsDeath)
			Anim_Frame_Flag = 0;
	}

	if (KeyState == 0)
	{
		Dir = { 0, 0 };

		if (!IsTrapped && !IsDeath)
			Anim_Frame_Cur = Anim_Frame_Min;
	}
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
			ObstacleCollision(block);
		}
	}

	for (Block* block : OBSTACLE_VECTOR)
	{
		if (RRCollision(&ColliderBox, &block->GetCollider()))
		{
			RewindMove();
			ObstacleCollision(block);
		}
	}

	for (Bomb* B : BombBag)
	{
		if (!B->GetColliderState())
			continue;

		if (RRCollision(&ColliderBox, &B->GetCollider()))
		{
			RewindMove();
		}
	}

	for (Bomb* B : BOMB_VECTOR)
	{
		if (!B->GetColliderState())
			continue;

		if (RRCollision(&ColliderBox, &B->GetCollider()))
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

	if (IsTrapped)
	{
		for (Player* otherPlayer : PLAYER_VECTOR)
		{
			if (otherPlayer == this) return;
			
			if (RRCollision(&ColliderBox, &otherPlayer->GetCollider()))
			{
				KillPlayer();
			}
		}
	}
}

void Player::UpdateColliderBox()
{
	ColliderBox = { Pos.x - ColliderSize.x / 2 + ColPivot.x,
					Pos.y - ColliderSize.y / 2 + ColPivot.y,
					Pos.x + ColliderSize.x / 2 + ColPivot.x,
					Pos.y + ColliderSize.y / 2 + ColPivot.y };

	vertex[0] = { ColliderBox.left,  ColliderBox.top };
	vertex[1] = { ColliderBox.right, ColliderBox.top };
	vertex[2] = { ColliderBox.right, ColliderBox.bottom };
	vertex[3] = { ColliderBox.left,  ColliderBox.bottom };
}

void Player::PutBomb()
{
	if (BombBag.size() < MaxBomb)
	{
		Bomb* NewBomb = new Bomb(PlayerFlag, Pos, BombPower);
		if (NewBomb->GetPos().x > 780 || NewBomb->GetPos().x < 26 ||
			NewBomb->GetPos().y > 676 || NewBomb->GetPos().y < 16)
		{
			delete NewBomb;
			return;
		}

		for (Bomb* B : BombBag)
		{
			if (NewBomb->GetPos().x == B->GetPos().x &&
				NewBomb->GetPos().y == B->GetPos().y)
			{
				delete NewBomb;
				return;
			}
		}

		for (Bomb* B : BOMB_VECTOR)
		{
			if (NewBomb->GetPos().x == B->GetPos().x &&
				NewBomb->GetPos().y == B->GetPos().y)
			{
				delete NewBomb;
				return;
			}
		}

		SOUNDMANAGER->PlaySFX("BombPut");
		BombBag.push_back(NewBomb);
		BOMB_VECTOR.push_back(NewBomb);

		Packet temp; temp.head = BOMB; temp.PlayerFlag = PlayerFlag;
		temp.Pos = NewBomb->GetPos(); temp.Power = BombPower;
		NETWORKMANAGER->SendPacket(temp);
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
			Speed++;
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

void Player::TrapPlayer()
{
	if (!IsTrapped && !IsDeath)
		IsTrapped = true;
	else
		return;

	HBITMAP htemp = hImage;
	BITMAP btemp = bitImage;
	hImage = DeathImage[0];
	bitImage = DeathBitmap[0];
	DeathImage[0] = hImage;
	DeathBitmap[0] = bitImage;

	InitAnimation(0, 3, 4, 1, 0);
	Anim_Speed = 600;
	ImageScale = 1.3f;
	ImagePivot = { 18, 0 };
	oldSpeed = Speed;
	Speed = 1;
}

void Player::KillPlayer()
{
	if (IsTrapped && !IsDeath)
		IsDeath = true;
	else
		return;
	
	hImage = DeathImage[1];
	bitImage = DeathBitmap[1];

	InitAnimation(0, 7, 8, 1, 0);
	Anim_Speed = 100;
	ImageScale = 1.2f;
	ImagePivot = { 0, 0 };
	
	cout << "Player " << PlayerFlag << "Death!" << endl;
	SOUNDMANAGER->PlaySFX("Die");
}

bool Player::ObstacleCollision(Objects* other)
{
	RECT rt = other->GetCollider();
	POINT Halfsize = other->GetColliderSize();
	Halfsize.x /= 2;  Halfsize.y /= 2;

	POINT BoxVTX[4];

	// LT[0], RT[0], RB[2], LB[3]
	BoxVTX[0] = { rt.left,  rt.top };
	BoxVTX[1] = { rt.right, rt.top };
	BoxVTX[2] = { rt.right, rt.bottom };
	BoxVTX[3] = { rt.left,  rt.bottom };

	/*
		v0--v1
		|	|
		|	|
		v3--v2
	*/


	if (vertex[0].x <= BoxVTX[2].x && 
		vertex[0].x > BoxVTX[2].x - Halfsize.x)
	{
		if (vertex[0].y >= BoxVTX[2].y)
			Pos.x += Speed / 3;
	}
	if (vertex[0].x >= BoxVTX[2].x)
	{
		if (vertex[0].y <= BoxVTX[2].y &&
			vertex[0].y > BoxVTX[2].y - Halfsize.y)
			Pos.y += Speed / 3;
	}

	if (vertex[1].x >= BoxVTX[3].x &&
		vertex[1].x < BoxVTX[3].x + Halfsize.x)
	{
		if (vertex[1].y >= BoxVTX[3].y)
			Pos.x -= Speed / 3;
	}
	if (vertex[1].x <= BoxVTX[3].x)
	{
		if (vertex[1].y <= BoxVTX[3].y &&
			vertex[1].y > BoxVTX[3].y - Halfsize.y)
			Pos.y += Speed / 3;
	}

	if (vertex[2].x >= BoxVTX[0].x &&
		vertex[2].x < BoxVTX[0].x + Halfsize.x)
	{
		if (vertex[2].y <= BoxVTX[0].y)
			Pos.x -= Speed / 3;
	}
	if (vertex[2].x <= BoxVTX[0].x)
	{
		if (vertex[2].y >= BoxVTX[0].y &&
			vertex[2].y < BoxVTX[0].y + Halfsize.y)
			Pos.y -= Speed / 3;
	}

	if (vertex[3].x <= BoxVTX[1].x &&
		vertex[3].x > BoxVTX[1].x - Halfsize.x)
	{
		if (vertex[3].y <= BoxVTX[1].y)
			Pos.x += Speed / 3;
	}
	if (vertex[3].x >= BoxVTX[1].x)
	{
		if (vertex[3].y >= BoxVTX[1].y &&
			vertex[3].y < BoxVTX[1].y + Halfsize.y)
			Pos.y -= Speed / 3;
	}

	UpdateColliderBox();

	return false;
}

void Player::Update()
{
	UpdateFrame();

	for (int i = 0; i < BombBag.size(); i++)
	{
		BombBag[i]->Update();

		if (BombBag[i]->GetBombState())
		{
			delete BombBag[i];
			BombBag.erase(BombBag.begin() + i);
		}
	}

	if (IsDeath) return;

	if (IsTrapped)
	{
		DeathTimer += ElapseTime;

		if (DeathTimer >= LifeTime)
		{
			KillPlayer();
		}
	}

	Pos.x += Speed * Dir.x;
	Pos.y += Speed * Dir.y;

	if (Pos.x > 780 || Pos.x < 26 ||
		Pos.y > 676 || Pos.y < 16)
	{
		RewindMove();
	}

	UpdateColliderBox();
	Collision();
}

void Player::UpdateFrame()
{
	if(IsDeath && Anim_Frame_Cur == Anim_Frame_Max)
	{
		return;
	}
	
	AnimObject::UpdateFrame();

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
