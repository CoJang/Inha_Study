#pragma once
#include "Objects.h"

struct GamePackit
{
	POINT Pos;
};

struct SystemPackit
{
	TCHAR msg[128];
};

#define WM_ASYNC WM_USER + 2
#define MAX_CHAT 5

struct Tile
{
	POINT Pos;
	bool IsUsing;
};

class ServerClass
{
private:
	WSADATA wsadata;
	SOCKET s, cs;
	TCHAR msg[512], wbuff[128];
	SOCKADDR_IN addr = { 0 }, c_addr;
	int Cnt, size, msgLen;
	int PosY = 0;
	char buff[128];
	vector<wstring> ChatLog;
	vector<SOCKET> ClientList;
	vector<POINT> WhiteStoneContainer;
	vector<POINT> BlackStoneContainer;

	// 19 * 19
	Tile Tiles[19][19];
private:
	HDC* BackBuffer;
	HDC* FrontBuffer;
public:
	ServerClass();
	~ServerClass();

	void InitServer(HWND hWnd, HDC* Front, HDC* Back);
	void Render();
	void Accept(HWND hWnd);
	void ReadMessage(WPARAM wParam);
	void CheckKeyDown(WPARAM wParam);
	POINT CircleClickCheck(POINT MousePos);

	wstring MakeWStrMsg(TCHAR* Msg);
	wstring MakeWStrMsg(SOCKET ID, TCHAR* Msg);
	string MakeStrMsg(char* Msg);
	string MakeStrMsg(SOCKET ID, char* Msg);
	string StonePosFix(POINT pos, int flag);

	void DrawLine(POINT start, POINT end);
	void DrawGrid(POINT pos, int Num);
	void DrawCircle(POINT pos, int R);
	void InitTile(POINT pos, int Num);
};

