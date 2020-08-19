#pragma once
#include "Tile.h"
class Map
{
private:
	Tile* Tiles;

	POINT Start, End;
	vector<POINT> OpenList;
	vector<POINT> CloseList;

	POINT MapSize;
	bool IsCostRenderMode;
public:
	Map();
	~Map();

	void InitTiles();
	void Render(HDC hdc);
	void SetCostRenderMode() { IsCostRenderMode ^= true; };
	void SetStartGoal(POINT MousePos);
	void SetObstacle(POINT MousePos);

	void UpdateNearValue(POINT index);
	void UpdateG(POINT index, POINT parent, int ParentG, int AddValue);
	void UpdateH(POINT destIndex);
	void UpdateF();
	void UpdateF(POINT index);
	POINT GetMinF();
	void AddToOpenList(POINT index, POINT parent);
	void Run();
	void DrawResult();
};

