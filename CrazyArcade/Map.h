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

	// �÷��̾�� ��ȣ�ۿ��Ͽ� ���� ������ �ٲٴ°� �ʿ�(��, �� ����)
	void FrontRender(HDC front, HDC back, bool ColliderDraw);
	void BackRender(HDC front, HDC back, bool ColliderDraw);

	inline Block* GetBlocks() { return Blocks; };
};

