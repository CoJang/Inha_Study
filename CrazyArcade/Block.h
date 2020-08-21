#pragma once
#include "MapObjects.h"

#define ColliderSize 48

class Block : public MapObjects
{
private:
	bool IsPassable;
	bool IsDestructible;

	RECT Collider;
	POINT ColPivot;

	POINT Start;
	int Anim_Frame_Max;
	int Anim_Frame_Min;
	int Anim_Frame_Cur;
	int Anim_Frame_Flag;
public:
	Block();
	~Block();

	void Init(bool Passable, bool IsDestructible, POINT pos, POINT pivot);
	void SetImage(HBITMAP & image, BITMAP & bitmap);
	void Render(HDC front, HDC back, bool ColliderDraw);
	void UpdateFrame();

	inline RECT GetArea() { return Collider; };
	inline bool GetDestructible() { return IsDestructible; };
	inline bool GetPassable() { return IsPassable; };
};

