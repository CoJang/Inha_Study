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
	Tiles[Start.x + (MapSize.x * Start.y)].color = RGB(255, 255, 0);
	Tiles[End.x + (MapSize.x * End.y)].color = RGB(0, 0, 255);

	for (int x = 0; x < MapSize.x; x++)
		for (int y = 0; y < MapSize.y; y++)
		{
			Tiles[x + (y * MapSize.x)].Render(hdc);

			if(IsCostRenderMode)
				Tiles[x + (y * MapSize.x)].CostRender(hdc);
		}
	
	if (IsCostRenderMode)
	{
		Tiles[Start.x + (Start.y * MapSize.x)].CostRender(hdc);
		Tiles[End.x + (End.y * MapSize.x)].CostRender(hdc);
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
	}
	else if (End.x == -1 && End.y == -1)
	{
		End = index;
		Tiles[index.x + (MapSize.x * index.y)].color = RGB(0, 255, 255);
		UpdateH(End);
		UpdateF();
		Run();
	}
}

void Map::SetObstacle(POINT MousePos)
{
	POINT index = { -1, -1 };

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

	Tiles[index.x + (index.y * MapSize.x)].IsObstacle = true;
	Tiles[index.x + (index.y * MapSize.x)].color = RGB(0, 0, 0);
}

// Need Fix
void Map::UpdateNearValue(POINT index)
{
	if (Tiles[index.x + (index.y * MapSize.x)].Parents.x == -1)
		Tiles[index.x + (index.y * MapSize.x)].Parents = index;

	POINT Parent = Tiles[index.x + (index.y * MapSize.x)].Parents;
	int ParentG = Tiles[Parent.x + (Parent.y * MapSize.x)].CostFromStart;

	if (!index.x - 1 < 0)
	{
		//UpdateG({ index.x - 1, index.y }, index, ParentG, 10);
		AddToOpenList({ index.x - 1, index.y }, Parent);
	}
	if (!index.y - 1 < 0)
	{
		//UpdateG({ index.x, index.y - 1 }, index, ParentG, 10);
		AddToOpenList({ index.x, index.y - 1 }, Parent);
	}
	if (!(index.x + 1 >= MapSize.x))
	{
		//UpdateG({ index.x + 1, index.y }, index, ParentG, 10);
		AddToOpenList({ index.x + 1, index.y }, Parent);
	}
	if (!(index.y + 1 >= MapSize.y))
	{
		//UpdateG({ index.x, index.y + 1 }, index, ParentG, 10);
		AddToOpenList({ index.x, index.y + 1 }, Parent);
	}

	if (!(index.x - 1 < 0 || index.y - 1 < 0))
	{
		//UpdateG({ index.x - 1, index.y - 1 }, index, ParentG, 14);
		AddToOpenList({ index.x - 1, index.y - 1 }, Parent);
	}
	if (!(index.x - 1 < 0 || index.y + 1 >= MapSize.y))
	{
		//UpdateG({ index.x - 1, index.y + 1 }, index, ParentG, 14);
		AddToOpenList({ index.x - 1, index.y + 1 }, Parent);
	}
	if (!(index.y - 1 < 0 || index.x + 1 >= MapSize.x))
	{
		//UpdateG({ index.x + 1, index.y - 1 }, index, ParentG, 14);
		AddToOpenList({ index.x + 1, index.y - 1 }, Parent);
	}
	if (!(index.x + 1 >= MapSize.x || index.y + 1 >= MapSize.y))
	{
		//UpdateG({ index.x + 1, index.y + 1 }, index, ParentG, 14);
		AddToOpenList({ index.x + 1, index.y + 1 }, Parent);
	}

	CloseList.push_back(index);
	Tiles[index.x + (index.y * MapSize.x)].color = RGB(255, 0, 0);
}

// Need Fix
void Map::UpdateG(POINT index, POINT parent, int ParentG, int AddValue)
{
	int oldG = Tiles[index.x + (index.y * MapSize.x)].CostFromStart;

	if (AddValue == 0)
	{
		//POINT parent = Tiles[index.x + (index.y * MapSize.x)].Parents;
		POINT Gap = { index.x, index.y };
		Gap.x = abs(Gap.x - parent.x);
		Gap.y = abs(Gap.y - parent.y);

		int Cost = ParentG;
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

		if (oldG > Cost || oldG == 0)
		{
			Tiles[index.x + (index.y * MapSize.x)].Parents = parent;
			Tiles[index.x + (index.y * MapSize.x)].CostFromStart = Cost;
			UpdateF();
		}
	}
	else if (oldG > ParentG + AddValue || oldG == 0)
	{
		Tiles[index.x + (index.y * MapSize.x)].Parents = parent;
		Tiles[index.x + (index.y * MapSize.x)].CostFromStart = ParentG + AddValue;
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

void Map::UpdateF(POINT index)
{
	Tiles[index.x + (index.y * MapSize.x)].UpdateF();
}

// return index
POINT Map::GetMinF()
{
	if (OpenList.empty()) return{ -1, -1 };

	int MinF = 99999; POINT index; int i = 0; int location = 0;
	for (auto Node : OpenList)
	{
		if (Tiles[Node.x + (Node.y * MapSize.x)].TotalCost < MinF)
		{
			location = i;
			index = Node;
			MinF = Tiles[Node.x + (Node.y * MapSize.x)].TotalCost;
		}
		i++;
	}

	OpenList.erase(OpenList.begin() + location);

	return index;
}

void Map::AddToOpenList(POINT index, POINT parent)
{
	if (Tiles[index.x + (index.y * MapSize.x)].IsObstacle || Tiles[index.x + (index.y * MapSize.x)].Parents == parent)
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
		UpdateG({ index.x, index.y }, parent, Tiles[parent.x + (parent.y * MapSize.x)].CostFromStart, 0);
		Tiles[index.x + (index.y * MapSize.x)].Parents = parent;
		Tiles[index.x + (index.y * MapSize.x)].color = RGB(0, 255, 0);
	}
	else//if(IsDuplicated)
	{
		UpdateG(index, parent, Tiles[parent.x + (parent.y * MapSize.x)].CostFromStart, 0);
		UpdateF(index);
	}
}

void Map::Run()
{
	POINT NextNode = GetMinF();

	if (NextNode.x != -1 && NextNode.y != -1)
	{
		if (NextNode.x != End.x || NextNode.y != End.y)
		{
			UpdateNearValue(NextNode);
			Run();
		}
	}
	DrawResult();
}

void Map::DrawResult()
{
	POINT Next = Tiles[End.x + (End.y * MapSize.x)].Parents;

	while (Next.x != Start.x && Next.y != Start.y)
	{
		Tiles[Next.x + (Next.y * MapSize.x)].color = RGB(120, 120, 120);
		Next = Tiles[Next.x + (Next.y * MapSize.x)].Parents;
	}
}
