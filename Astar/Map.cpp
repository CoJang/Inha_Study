#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	MapSize = { (WIN_WIDTH / TILE_SIZE), (WIN_HEIGHT / TILE_SIZE) };
	Tiles = new Tile[ MapSize.x * MapSize.y ];
	IsCostRenderMode = false;

	Start = { -1, -1 }; End = { -1, -1 };
}


Map::~Map()
{
	delete[] Tiles;
}

void Map::InitTiles()
{
	Tiles[0].Pos = { 25, 25 };

	for(int x = 0; x < MapSize.x; x++)
		for (int y = 0; y < MapSize.y; y++)
		{
			Tiles[x + (y * MapSize.x)].Pos = { Tiles[0].Pos.x + x * TILE_SIZE,
											   Tiles[0].Pos.y + y * TILE_SIZE };
		}
}

void Map::Render(HDC hdc)
{
	for (int x = 0; x < MapSize.x; x++)
		for (int y = 0; y < MapSize.y; y++)
		{
			Tiles[x + (y * MapSize.x)].Render(hdc);

			if(IsCostRenderMode)
				Tiles[x + (y * MapSize.x)].CostRender(hdc);
		}
}

void Map::SetStartGoal(POINT MousePos)
{
	POINT index = {-1, -1};

	for (int x = 0; x < MapSize.x; x++)
		for (int y = 0; y < MapSize.y; y++)
		{
			if (Tiles[x + (y * MapSize.x)].CheckClicked(MousePos))
			{
				index = { x, y };
				break;
			}
		}

	if (index.x == -1 || index.y == -1) return;

	if (Start.x == -1 && Start.y == -1)
	{
		Start = index;
		Tiles[index.x + (MapSize.x * index.y)].color = RGB(255, 255, 0);
		UpdateNearValue(Start);
		OpenList.push_back(Start);
	}
	else if (End.x == -1 && End.y == -1)
	{
		End = index;
		Tiles[index.x + (MapSize.x * index.y)].color = RGB(0, 255, 255);
		UpdateH(End);
		UpdateF();
	}
}

// Need Fix
void Map::UpdateNearValue(POINT index)
{
	if (Tiles[index.x + (index.y * MapSize.x)].Parents.x == -1)
		Tiles[index.x + (index.y * MapSize.x)].Parents = index;

	POINT Parent = Tiles[index.x + (index.y * MapSize.x)].Parents;
	int ParentG = Tiles[Parent.x + (Parent.y * MapSize.x)].CostFromStart;

	if(!index.x - 1 < 0)			
		Tiles[index.x - 1 + (index.y * MapSize.x)].CostFromStart = ParentG + 10;
	if(!index.y - 1 < 0)			
		Tiles[index.x + (index.y - 1 * MapSize.x)].CostFromStart = ParentG + 10;
	if(!(index.x + 1 >= MapSize.x)) 
		Tiles[index.x + 1 + (index.y * MapSize.x)].CostFromStart = ParentG + 10;
	if(!(index.y + 1 >= MapSize.y)) 
		Tiles[index.x + (index.y + 1 * MapSize.x)].CostFromStart = ParentG + 10;

	if (!(index.x - 1 < 0 || index.y - 1 < 0))
		Tiles[index.x - 1 + (index.y - 1 * MapSize.x)].CostFromStart = ParentG + 14;
	if(!(index.x - 1 < 0 || index.y + 1 >= MapSize.y))
		Tiles[index.x - 1 + (index.y + 1 * MapSize.x)].CostFromStart = ParentG + 14;
	if (!(index.y - 1 < 0 || index.x + 1 >= MapSize.x))
		Tiles[index.x + 1 + (index.y - 1 * MapSize.x)].CostFromStart = ParentG + 14;
	if (!(index.x + 1 >= MapSize.x || index.y + 1 >= MapSize.y))
		Tiles[index.x + 1 + (index.y + 1 * MapSize.x)].CostFromStart = ParentG + 14;
}

// Need Fix
void Map::UpdateG(POINT index, int ParentG, int AddValue)
{
	int G = Tiles[index.x + (index.y * MapSize.x)].CostFromStart;

	if (G != 0)
	{
		if (ParentG > G)
		{
			Tiles[index.x + (index.y * MapSize.x)].CostFromStart;
		}
	}


}

void Map::UpdateH(POINT destIndex)
{
	for (int x = 0; x < MapSize.x; x++)
		for (int y = 0; y < MapSize.y; y++)
		{
			POINT Gap = { x, y };
			Gap.x = abs(Gap.x - destIndex.x);
			Gap.y = abs(Gap.y - destIndex.y);

			int Cost = 0;
			while (Gap.x > 0 && Gap.y > 0)
			{
				Gap.x--; Gap.y--;
				Cost += 14;
			}
			while (Gap.x > 0)
			{
				Gap.x--;
				Cost += 10;
			}
			while (Gap.y > 0)
			{
				Gap.y--;
				Cost += 10;
			}

			Tiles[x + (y * MapSize.x)].CostToDist = Cost;
		}
}

void Map::UpdateF()
{
	for (int x = 0; x < MapSize.x; x++)
		for (int y = 0; y < MapSize.y; y++)
		{
			Tiles[x + (y * MapSize.x)].UpdateF();
		}
}

POINT Map::GetMinF()
{
	if (OpenList.empty()) return{ -1, -1 };

	int MinF = 99999; POINT index; int i = 0;
	for (auto Node : OpenList)
	{
		if (Tiles[Node.x + (Node.y * MapSize.x)].TotalCost < MinF)
		{
			index = Node;
			MinF = Tiles[Node.x + (Node.y * MapSize.x)].TotalCost;
		}
		i++;
	}

	OpenList.erase(OpenList.begin() + i);

	return index;
}

void Map::AddToOpenList(POINT index, POINT parent)
{
	if (Tiles[index.x + (index.y * MapSize.x)].IsObstacle)
		return;

	for (POINT Node : CloseList)
	{
		if (index.x == Node.x && index.y == Node.y)
			return;
	}

	bool IsDuplicated = false;
	for (POINT Node : OpenList)
	{
		if (index.x == Node.x && index.y == Node.y)
			IsDuplicated = true;
	}

	if (!IsDuplicated)
	{
		OpenList.push_back(index);
		Tiles[index.x + (index.y * MapSize.x)].Parents = parent;
	}
	///////////////////////////////////////////////////////////////////////
	else//if(IsDuplicated)
	{
		int oldG = Tiles[index.x + (index.y * MapSize.x)].CostFromStart;
	}
	///////////////////////////////////////////////////////////////////////
}
