#pragma once
#include "Objects.h"

class Item : public AnimObject
{
private:
	int Type;
	bool IsUpper;
	int Timer;

	bool Waterproof;
public:
	Item(POINT pos, int itemtype);
	~Item();

	void Update();
	int GetType() { return Type; };
	int GetState() { return Waterproof; };
};

