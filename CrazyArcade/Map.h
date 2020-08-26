#pragma once
#include "Block.h"
#include "Item.h"

class Map
{
private:
	Objects FrameImage;
	Objects BackTiles;
	
	Block* Blocks;
public:
	Map();
	~Map();

	void LoadingBlocks();
	void LoadingBackground();

	void Update();

	// 플레이어와 상호작용하여 렌더 순서를 바꾸는게 필요(앞, 뒤 판정)
	void FrontRender(HDC front, HDC back, bool ColliderDraw);
	void BackRender(HDC front, HDC back, bool ColliderDraw);

	inline Block* GetBlocks() { return Blocks; };
};

