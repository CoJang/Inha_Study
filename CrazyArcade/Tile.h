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
	POINT Start;

	int Anim_Frame_Max;
	int Anim_Frame_Min;
	int Anim_Frame_Cur;
	int Anim_Frame_Flag;
public:
	Tile();
	~Tile();
	
	void InitTile(wstring path, POINT pos);

	void Render(HDC front, HDC back);
};

