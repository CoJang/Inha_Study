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

private:
	HDC* BackBuffer;
	HDC* FrontBuffer;
	ImageObject* GridImage;
public:
	ServerClass();
	~ServerClass();

	void InitServer(HWND hWnd, HDC* Front, HDC* Back);
	void Render();
	void Accept(HWND hWnd);
	void ReadMessage(WPARAM wParam);
	void CheckKeyDown(WPARAM wParam);

	wstring MakeWStrMsg(TCHAR* Msg);
	wstring MakeWStrMsg(SOCKET ID, TCHAR* Msg);
	string MakeStrMsg(char* Msg);
	string MakeStrMsg(SOCKET ID, char* Msg);
};

