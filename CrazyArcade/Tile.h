#pragma once

#define TILE_SIZE 40

class Tile
{
private:
	bool IsPassable;
	bool IsDestructible;

	POINT Pos;
	int TileImage;
	HBITMAP hImage;
	BITMAP bitImage;

	POINT Sprite_Size;
	POINT Pivot;
	POINT Start;

	int Anim_Frame_Max;
	int Anim_Frame_Min;
	int Anim_Frame_Cur;
	int Anim_Frame_Flag;
public:
	Tile();
	~Tile();
	
	//wstring path, bool Passable, bool Destructible, POINT pivot
	void InitTile(wstring, bool, bool, POINT);
	inline void SetPos(POINT pos) { Pos = pos; Pos.x -= Pivot.x; Pos.y -= Pivot.y;};

	void Render(HDC front, HDC back);
};

