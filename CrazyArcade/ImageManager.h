#pragma once

enum ImageTag
{
	BG_FRAME,	MAP_TILE,

	MAP_OBS_1,	MAP_OBS_2,	MAP_OBS_3,	MAP_OBS_POND,
	MAP_BLK_1,	MAP_BLK_2,	MAP_BLK_3,	MAP_BLK_4,	MAP_BLK_5,
	MAP_BLK_6,	MAP_BLK_7,	MAP_BLK_8,	MAP_BLK_9,

	ITEM_BOMB, ITEM_SKATE, ITEM_FLASK, ITEM_TOXIC,

	EFX_EXPLOSION, EFX_BIGBUBBLE,
	WATER_BOMB,

	CHAR_BAZZY, CHAR_HOOCU,

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

