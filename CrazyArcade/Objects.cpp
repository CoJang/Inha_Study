#include "stdafx.h"
#include "Objects.h"


Objects::Objects()
{
	Pos = { 0, 0 }; ImagePivot = { 0, 0 }; ColPivot = { 0, 0 };
	ColliderBox = { 0, 0, 0, 0 }; IsColliderActive = true;
}

void Objects::Init(wstring path, POINT pos, POINT pivot)
{
	ImagePivot = pivot;
	Pos = pos;

	hImage = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hImage, sizeof(BITMAP), &bitImage);

	Sprite_Size.x = bitImage.bmWidth;
	Sprite_Size.y = bitImage.bmHeight;
}

void Objects::Init(POINT pos, POINT pivot)
{
	ImagePivot = pivot;
	Pos = pos;
}

void Objects::SetImage(HBITMAP image)
{
	hImage = image;
	SetBitmap();
}

void Objects::SetBitmap()
{
	GetObject(hImage, sizeof(BITMAP), &bitImage);
	Sprite_Size.x = bitImage.bmWidth;
	Sprite_Size.y = bitImage.bmHeight;
}

void Objects::SetImage(HBITMAP & image, BITMAP & bitmap)
{
	hImage = image;
	bitImage = bitmap;
	Sprite_Size.x = bitImage.bmWidth;
	Sprite_Size.y = bitImage.bmHeight;
}


void Objects::InitCollider(POINT pivot, int size)
{
	if(pivot.x != -1)
		ColPivot = pivot;

	if (size != -1)
	{
		ColliderSize.x = size;
		ColliderSize.y = size;
	}

	ColliderBox = { Pos.x - ColliderSize.x / 2 + ColPivot.x,
					Pos.y - ColliderSize.y / 2 + ColPivot.y,
					Pos.x + ColliderSize.x / 2 + ColPivot.x,
					Pos.y + ColliderSize.y / 2 + ColPivot.y };
}

void Objects::InitCollider(POINT pivot, int sizex, int sizey)
{
	if (pivot.x != -1)
		ColPivot = pivot;

	ColliderSize.x = sizex;
	ColliderSize.y = sizey;

	ColliderBox = { Pos.x - ColliderSize.x / 2 + ColPivot.x,
					Pos.y - ColliderSize.y / 2 + ColPivot.y,
					Pos.x + ColliderSize.x / 2 + ColPivot.x,
					Pos.y + ColliderSize.y / 2 + ColPivot.y };
}

// Default Render Target : [Front Buffer]
// Use BitBlt [ No Filttering Color ]
void Objects::Render(HDC front, HDC back, bool colliderdraw)
{
	HBITMAP oldbuffer = (HBITMAP)SelectObject(back, hImage);

	BitBlt(front, Pos.x - ImagePivot.x,
				  Pos.y - ImagePivot.y, 
				  Sprite_Size.x, Sprite_Size.y,
			      back, 0, 0, SRCCOPY);

	if (colliderdraw && IsColliderActive)
		Rectangle(front, ColliderBox.left, ColliderBox.top,
						 ColliderBox.right, ColliderBox.bottom);

	SelectObject(back, oldbuffer);
	DeleteObject(oldbuffer);
}

// Default Render Target : [ Front Buffer ]
// Use TransparentBlt [ No Filttering Color ]
void Objects::TransRender(HDC front, HDC back, bool colliderdraw)
{
	HBITMAP oldbuffer = (HBITMAP)SelectObject(back, hImage);

	TransparentBlt(front, Pos.x - ImagePivot.x, 
						  Pos.y - ImagePivot.y, 
						  Sprite_Size.x, Sprite_Size.y,
						  back, 0, 0, Sprite_Size.x, Sprite_Size.y, FILTER);

	if (colliderdraw && IsColliderActive)
		Rectangle(front, ColliderBox.left, ColliderBox.top,
						 ColliderBox.right, ColliderBox.bottom);

	SelectObject(back, oldbuffer);
	DeleteObject(oldbuffer);
}

AnimObject::AnimObject()
{
	Anim_Timer = 0;
	Start = { 0, 0 };
	ImageScale = 1.0f;
	Anim_Speed = 0;
}

void AnimObject::InitAnimation()
{
	Anim_Frame_Max = bitImage.bmWidth / Sprite_Size.x - 1;
	Anim_Frame_Min = 0;
	Anim_Frame_Cur = Anim_Frame_Min;
	Anim_Frame_Flag = 0;

	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;
}

void AnimObject::InitAnimation(int minframe, int framelimit, 
							   int maxframe, int maxframeflag, int flag)
{
	Sprite_Size.x = bitImage.bmWidth / maxframe;
	Sprite_Size.y = bitImage.bmHeight / maxframeflag;

	Anim_Frame_Max = framelimit;
	Anim_Frame_Min = minframe;
	Anim_Frame_Cur = Anim_Frame_Min;
	Anim_Frame_Flag = flag;

	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;
}

void AnimObject::Update()
{
	UpdateFrame();
}

void AnimObject::UpdateFrame()
{
	Start.x = Anim_Frame_Cur * Sprite_Size.x;
	Start.y = Anim_Frame_Flag * Sprite_Size.y;

	Anim_Timer += ElapseTime;

	if (Anim_Timer >= Anim_Speed)
	{
		Anim_Frame_Cur++;
		Anim_Timer = 0;
	}

	if (Anim_Frame_Cur > Anim_Frame_Max)
		Anim_Frame_Cur = Anim_Frame_Min;
}

void AnimObject::Render(HDC front, HDC back, bool colliderdraw)
{
	HBITMAP oldbuffer = (HBITMAP)SelectObject(back, hImage);

	TransparentBlt(front, Pos.x - ImagePivot.x, Pos.y - ImagePivot.y,
							Sprite_Size.x * ImageScale,
							Sprite_Size.y * ImageScale,
							back, Start.x, Start.y,
							Sprite_Size.x, Sprite_Size.y, FILTER);

	if (colliderdraw && IsColliderActive)
		Rectangle(front, ColliderBox.left, ColliderBox.top,
						 ColliderBox.right, ColliderBox.bottom);

	SelectObject(back, oldbuffer);
}
