#include "stdafx.h"
#include "Player.h"

void Player::Render(HDC hdc)
{
	Ellipse(hdc, Pos.x - r, Pos.y - r, Pos.x + r, Pos.y + r);
}


void Player::Update()
{
	
}

void Player::MoveChar(POINT Dir, POINT MapPos)
{
	Pos.x = Pos.x + (Dir.x * Grid_Dist);
	Pos.y = Pos.y + (Dir.y * Grid_Dist);

	if (Pos.x < MapPos.x) Pos.x = Pos.x + Grid_Dist;
	if (Pos.x > Grid_Width + MapPos.x) Pos.x = Pos.x - Grid_Dist;
	if (Pos.y < MapPos.y) Pos.y = Pos.y + Grid_Dist;
	if (Pos.y > Grid_Height + MapPos.y)
		Pos.y = Pos.y - Grid_Dist;
}


