#pragma once
#include "Tile.h"
#include "Block.h"

class Map
{
private:
	Tile FrameImage;
	Tile BackTiles;
	
	Block* Blocks;
	HBITMAP* BlockImages;
	BITMAP* BlockBitmaps;
public:
	Map();
	~Map();

	void LoadingTiles();
	void LoadingBlocks();

	// 플레이어와 상호작용하여 렌더 순서를 바꾸는게 필요(앞, 뒤 판정)
	void FrontRender(HDC front, HDC back);
	void BackRender(HDC front, HDC back, bool ColliderDraw);

	inline Block* GetBlocks() { return Blocks; };
};

