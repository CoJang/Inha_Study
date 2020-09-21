#pragma once

enum ImageTag
{
	BG_FRAME,	MAP_TILE,

	//////////////////// DO NOT MODIFY /////////////////////
	MAP_OBS_1,	MAP_OBS_2,	MAP_OBS_3,	MAP_OBS_POND,
	MAP_BLK_1,	MAP_BLK_2,	MAP_BLK_3,	MAP_BLK_4,	MAP_BLK_5,
	MAP_BLK_6,	MAP_BLK_7,	MAP_BLK_8,	MAP_BLK_9,

	ITEM_BOMB, ITEM_SKATE, ITEM_FLASK, ITEM_TOXIC,
	//////////////////// DO NOT MODIFY /////////////////////

	EFX_EXPLOSION, WATER_BOMB, 

	CHAR_BAZZY, CHAR_BAZZY_TRAP, CHAR_BAZZY_DIE,
	CHAR_DAO, CHAR_DAO_TRAP, CHAR_DAO_DIE,

	LOBBY_FRAME, LOBBY_MINIMAP_FOREST, 
	LOBBY_CHECK1, LOBBY_CHECK2, LOBBY_START, 
	LOBBY_BAZZY_FACE, LOBBY_DAO_FACE,
	LOBBY_BAZZY_CHAR, LOBBY_DAO_CHAR,

	GAME_WIN, GAME_LOSE, GAME_DRAW,

	TOTAL_SIZE
};

class ImageManager
{
private:
	HBITMAP* Images;

public:
	ImageManager();
	~ImageManager();

	bool LoadingImages();

	inline HBITMAP GetImage(const ImageTag tag) { return Images[tag]; };
	inline HBITMAP GetImage(const int tag) { return Images[tag]; };
};

