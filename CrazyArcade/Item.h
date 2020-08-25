#pragma once
#include "Objects.h"

enum ItemType
{
	WATER_BOMB,
	ROLLER_SKATE,
	FLASK
};

class Item : public AnimObject
{
private:
	ItemType Type;
	bool IsUpper;
	int Timer;
public:
	Item(ItemType itemtype);
	~Item();

	void Update();
	ItemType GetType() { return Type; };
};

