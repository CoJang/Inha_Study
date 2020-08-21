#pragma once


class Player
{
private:
	POINT Pos;
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
	Player();
	~Player();

	void InitPlayer(POINT pos, POINT pivot);
	void Render(HDC front, HDC back);
};

