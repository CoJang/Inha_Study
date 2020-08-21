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

	// �÷��̾�� ��ȣ�ۿ��Ͽ� ���� ������ �ٲٴ°� �ʿ�(��, �� ����)
	void FrontRender(HDC front, HDC back);
	void BackRender(HDC front, HDC back, bool ColliderDraw);

	inline Block* GetBlocks() { return Blocks; };
};

