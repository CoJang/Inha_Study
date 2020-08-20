#include "stdafx.h"
#include "Map.h"

#define TILE_PIVOT {-26, -53}

Map::Map()
{
	Tiles = new Tile[MAP_WIDTH * MAP_HEIGHT];
	LoadingTiles();
}


Map::~Map()
{
	delete[] Tiles;
}

void Map::LoadingTiles()
{
#pragma region LoadImages
	//Tiles[0].InitTile(TEXT("images/map/SandBlockYellow.bmp"), false, true, { 0, -4 });
	//Tiles[1].InitTile(TEXT("images/map/SandBlockBuff.bmp"), false, true, { 0, -4 });
	//Tiles[2].InitTile(TEXT("images/map/SandBox.bmp"), false, true, { 0, -5 });

	//Tiles[3].InitTile(TEXT("images/map/SandCactiGreen.bmp"), false, false, { 0, -19 });
	//Tiles[4].InitTile(TEXT("images/map/SandCactiGreenBold.bmp"), false, false, { 0, -19 });
	//Tiles[5].InitTile(TEXT("images/map/SandCactiTea.bmp"), false, false, { 0, -5 });

	//Tiles[6].InitTile(TEXT("images/map/SandGround.bmp"), true, false, { 0, 0 });

	//Tiles[7].InitTile(TEXT("images/map/SandHouseBlue.bmp"), false, false, { 0, -23 });
	//Tiles[8].InitTile(TEXT("images/map/SandHouseGreen.bmp"), false, false, { 0, -23 });
	//Tiles[9].InitTile(TEXT("images/map/SandHouseTea.bmp"), false, false, { 0, -23 });

	//Tiles[10].InitTile(TEXT("images/map/SandOasis.bmp"), false, false, { 0, -5 });
	//Tiles[11].InitTile(TEXT("images/map/SandOasisAni.bmp"), false, false, { 0, -5 });

	//Tiles[12].InitTile(TEXT("images/map/SandShopBlue.bmp"), false, false, { 0, -5 });
	//Tiles[13].InitTile(TEXT("images/map/SandShopRed.bmp"), false, false, { 0, -5 });
	//Tiles[14].InitTile(TEXT("images/map/SandShopYellow.bmp"), false, false, { 0, -5 });

	//Tiles[15].InitTile(TEXT("images/map/SandStone.bmp"), false, true, { 0, -5 });

	//Tiles[16].InitTile(TEXT("images/map/SandTentBlue.bmp"), false, false, { 0, -5 });
	//Tiles[17].InitTile(TEXT("images/map/SandTentRed.bmp"), false, false, { 0, -5 });
	//Tiles[18].InitTile(TEXT("images/map/SandTentYellow.bmp"), false, false, { 0, -5 });

	//Tiles[19].InitTile(TEXT("images/map/SandTree.bmp"), false, false, { 0, -5 });
	//Tiles[20].InitTile(TEXT("images/map/SandTreeGreen.bmp"), false, false, { 0, -5 });
	//Tiles[21].InitTile(TEXT("images/map/SandTreeYellow.bmp"), false, false, { 0, -5 });

	//Tiles[22].InitTile(TEXT("images/map/TownBlockRed.bmp"), false, true, { 0, -5 });
	//Tiles[23].InitTile(TEXT("images/map/TownBlockYellow.bmp"), false, true, { 0, -5 });
	//Tiles[24].InitTile(TEXT("images/map/TownBox.bmp"), false, true, { 0, -5 });

	//Tiles[25].InitTile(TEXT("images/map/TownBush.bmp"), false, true, { 0, -5 });

	//Tiles[26].InitTile(TEXT("images/map/TownGround.bmp"), true, true, { 0, -5 });

	//Tiles[27].InitTile(TEXT("images/map/TownHouseBlue.bmp"), false, true, { 0, -5 });
	//Tiles[28].InitTile(TEXT("images/map/TownHouseRed.bmp"), false, true, { 0, -5 });
	//Tiles[29].InitTile(TEXT("images/map/TownHouseYellow.bmp"), false, true, { 0, -5 });

	//Tiles[30].InitTile(TEXT("images/map/TownTree.bmp"), false, true, { 0, -5 });

	//Tiles[31].InitTile(TEXT("images/map/TownWindmill.bmp"), false, true, { 0, -5 });
	//Tiles[32].InitTile(TEXT("images/map/TownWindmillAni.bmp"), false, true, { 0, -5 });
#pragma endregion
	FrameImage.InitTile(TEXT("images/Frame/play_bg.bmp"), false, false, { 0, 0 });
	FrameImage.SetPos({ 0, 0 });

	//Tiles[0].InitTile(TEXT("images/map/forest/Blocks/block_1_pop.bmp"), true, true, { 5, 0 });
	//Tiles[0].SetPos({ 25, 35 });

	//Tiles[1].InitTile(TEXT("images/map/forest/Obstacle/object_1.bmp"), true, true, { 0, 0 });
	//Tiles[1].SetPos({ 85, 35 });

	Tiles[2].InitTile(TEXT("images/map/forest/Tiles/tile_1.bmp"), true, true, TILE_PIVOT);
	Tiles[2].SetPos({ 0, 0 });

	Tiles[3].InitTile(TEXT("images/map/forest/Tiles/tile_1.bmp"), true, true, { -26, -53 });
	Tiles[3].SetPos({ 0, 52 * 12 });

	Tiles[4].InitTile(TEXT("images/map/forest/Tiles/tile_1.bmp"), true, true, { -26, -53 });
	Tiles[4].SetPos({ 52 * 14, 0 });

	Tiles[5].InitTile(TEXT("images/map/forest/Tiles/tile_1.bmp"), true, true, { -26, -53 });
	Tiles[5].SetPos({ 52 * 14, 52 * 12 });
}

void Map::Render(HDC front, HDC back)
{
	FrameImage.Render(front, back);

	for (int i = 0; i < MAP_SIZE; i++)
	{
		Tiles[i].Render(front, back);
	}
}
