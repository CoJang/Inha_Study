#pragma once

class Objects
{
protected:
	POINT Pos;
	HBITMAP hImage;
	BITMAP bitImage;

	POINT ImagePivot;
	POINT Sprite_Size;

	POINT ColPivot;
	RECT ColliderBox;
	POINT ColliderSize;
	bool IsColliderActive;
public:
	Objects();
	virtual ~Objects() = default;

	virtual void Init(wstring path, POINT pos, POINT pivot);

	virtual void Init(POINT pos, POINT pivot);
	virtual void SetBitmap();
	virtual void SetImage(HBITMAP image);
	virtual void SetImage(HBITMAP & image, BITMAP & bitmap);

	virtual void InitCollider(POINT pivot, int size);
	virtual void InitCollider(POINT pivot, int sizex, int sizey);
	inline RECT GetCollider() { return ColliderBox; };
	inline POINT GetColliderSize() { return ColliderSize; };
	virtual bool GetColliderState() { return IsColliderActive; };
	virtual void SetColliderState(bool isactive) { IsColliderActive = isactive; };

	virtual void SetPos(POINT pos) { Pos = pos; };
	virtual POINT GetPos() { return Pos; };

	virtual void Update() {};
	virtual void Render(HDC front, HDC back, bool colliderdraw);
	virtual void TransRender(HDC front, HDC back, bool colliderdraw);
};

class AnimObject : public Objects
{
protected:
	POINT Start;

	int Anim_Frame_Max;
	int Anim_Frame_Min;
	int Anim_Frame_Cur;
	int Anim_Frame_Flag;
	int Anim_Speed;
	int Anim_Timer;

	float ImageScale;
public:
	AnimObject();
	virtual ~AnimObject() { };

	virtual void InitAnimation();
	virtual void InitAnimation(int minframe, int framelimit, 
							   int maxframe, int maxframeflag, int flag);

	inline void SetImageSize(float scale) { ImageScale = scale; };
	inline void SetAnimSpeed(int milisec) { Anim_Speed = milisec; };
	inline void SetAnimFrameFlag(int frame_flag) { Anim_Frame_Flag = frame_flag; };
	inline void SetAnimMinFrame(int min_frame) { Anim_Frame_Min = min_frame; };
	inline void SetAnimMaxFrame(int max_frame) { Anim_Frame_Max = max_frame; };

	virtual void Update();
	virtual void UpdateFrame();
	virtual void Render(HDC front, HDC back, bool colliderdraw);
};

