#include "stdafx.h"
#include "Player.h"
#include "CollisionManager.h"
#include "ImageManager.h"
#include "Bomb.h"

extern Singleton* singleton;

Bomb::Bomb(int Owner, POINT pos, int power)
{
	AnimObject::Init(RePosition(pos), { 0, 0 });
	SetImage(GETIMAGE(WATER_BOMB));

	Sprite_Size.x = bitImage.bmWidth / 3;
	Sprite_Size.y = bitImage.bmHeight;
	ImageScale = 1.2f;

	AnimObject::InitAnimation();
	Anim_Speed = 180;

	AnimObject::InitCollider({ 26, 26 }, 36);
	IsColliderActive = false;

	Power = power;
	PlayerNum = Owner;
	IsDetonated = false;
	IsExpoding = false;
	Timer = 0;
}

Bomb::~Bomb()
{
	for (int i = 0; i < BOMB_VECTOR.size(); i++)
	{
		if (BOMB_VECTOR[i] == this)
		{
			BOMB_VECTOR.erase(BOMB_VECTOR.begin() + i);
			break;
		}
	}

	for (AnimObject* Wave : BombWaves)
	{
		delete Wave;
	}

	BombWaves.clear();
}

void Bomb::Update()
{
	Timer += ElapseTime;

	if (Timer > DETONATE_TIME && IsExpoding == false)
	{
		IsExpoding = true;
		Explosion();
	}

	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;

	UpdateFrame();

	if (!BombWaves.empty())
		for (AnimObject* Waves : BombWaves)
		{
			Waves->Update();
			if (RRCollision(&PLAYER->GetCollider(), &Waves->GetCollider()))
			{
				PLAYER->TrapPlayer();
			}

			for (int i = 0; i < ITEM_VECTOR.size(); i++)
			{
				if (ITEM_VECTOR[i]->GetState()) continue;

				if (RRCollision(&Waves->GetCollider(), &ITEM_VECTOR[i]->GetCollider()))
				{
					delete ITEM_VECTOR[i];
					ITEM_VECTOR.erase(ITEM_VECTOR.begin() + i);
				}
			}

			// Explosion Wave's Center
			if (Waves->GetPos().x == Pos.x &&
				Waves->GetPos().y == Pos.y) continue;

			for (Bomb* B : BOMB_VECTOR)
			{
				if (B == this || B->IsExpoding) continue;

				if (RRCollision(&Waves->GetCollider(), &B->GetCollider()))
				{
					B->IsExpoding = true;
					B->Explosion();
				}
			}
		}
}

void Bomb::UpdateFrame()
{
	Anim_Timer += ElapseTime;

	if (Anim_Timer > Anim_Speed)
	{
		Anim_Frame_Cur++;
		Anim_Timer = 0;
		IsColliderActive = true;
	}

	if (Anim_Frame_Cur > Anim_Frame_Max)
		Anim_Frame_Cur = Anim_Frame_Min;
}

void Bomb::Render(HDC front, HDC back, bool colliderdraw)
{
	AnimObject::Render(front, back, colliderdraw);

	if (!BombWaves.empty() && IsExpoding)
	{
		for (AnimObject* Waves : BombWaves)
		{
			Waves->Render(front, back, colliderdraw);
			if (Timer >= WAVE_ANIM_SPEED * 14)
			{
				IsDetonated = true;
			}
		}
	}
}

// Set In Tile
POINT Bomb::RePosition(POINT pos)
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		if (i * 52 < pos.x && pos.x < (i + 1) * 52)
		{
			pos.x = i * 52 + 26;
			break;
		}
	}

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		if (i * 52 < pos.y && pos.y < (i + 1) * 52)
		{
			pos.y = i * 52 + 52;
			break;
		}
	}

	return pos;
}

void Bomb::Explosion()
{
	Timer = 0;
	// Wave Image Flag Index
	// Flag 0: Up, 1: Down, 2: Left, 3: Right, 4: Center
	for (int Flag = 0; Flag < 5; Flag++)
	{
		for (int i = 0; i < Power; i++)
		{
			// Skiped Details [Update Later]
			if (!InitWave(i, Flag))
				break;
		}
	}

	SOUNDMANAGER->PlaySFX("Boom");

	for (AnimObject* Waves : BombWaves)
		for (int i = 0; i < TargetBlocks.size(); i++)
		{
			if (!TargetBlocks[i]->GetColliderState()) continue;

			if (RRCollision(&Waves->GetCollider(),
				&TargetBlocks[i]->GetCollider()))
			{
				TargetBlocks[i]->SetColliderState(false);
				TargetBlocks.erase(TargetBlocks.begin() + i);
			}
		}
}

bool Bomb::InitWave(int index, int flag)
{
	POINT WavePos = Pos;
	if (flag == 0)		WavePos = { Pos.x, Pos.y - 52 * (index + 1) };
	else if (flag == 1) WavePos = { Pos.x, Pos.y + 52 * (index + 1) };
	else if (flag == 2) WavePos = { Pos.x - 52 * (index + 1), Pos.y };
	else if (flag == 3) WavePos = { Pos.x + 52 * (index + 1), Pos.y };

	if (WavePos.x > 780 || WavePos.x < 0 ||
		WavePos.y > 676 || WavePos.y < 52) return false;

	AnimObject* Wave = new AnimObject;
	Wave->Init(WavePos, { 0, 0 });
	Wave->SetImage(GETIMAGE(EFX_EXPLOSION));
	Wave->InitAnimation(3, 4, 14, 5, flag);
	Wave->SetAnimSpeed(WAVE_ANIM_SPEED);
	Wave->SetImageSize(1.3f);
	Wave->InitCollider({ 26, 24 }, 36);

	for(Block* block : OBSTACLE_VECTOR)
		if (RRCollision(&Wave->GetCollider(), &block->GetCollider()))
		{
			delete Wave;
			return false;
		}

	for (Block* block : BLOCK_VECTOR)
		if (RRCollision(&Wave->GetCollider(), &block->GetCollider()))
		{
			BombWaves.push_back(Wave);
			TargetBlocks.push_back(block);
			return false;
		}

	BombWaves.push_back(Wave);
	return true;
}

