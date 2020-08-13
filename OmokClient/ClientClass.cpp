#include "stdafx.h"
#include "ClientClass.h"


ClientClass::ClientClass()
{
	addr = { 0 };
	memset(msg, 0 , sizeof(msg));
	memset(buff, 0, sizeof(buff));
	memset(wbuff, 0, sizeof(wbuff));
	Cnt = 0; size = 0; msgLen = 0;

	GridImage = new ImageObject;
	GridImage->InitImageObject(TEXT("images/board.bmp"), { 0, 0 });
	//WhiteStone = new ImageObject;
	//WhiteStone->InitImageObject(TEXT("images/white.bmp"), { 0, 0 });
	//BlackStone = new ImageObject;
	//BlackStone->InitImageObject(TEXT("images/black.bmp"), { 0, 0 });
}


ClientClass::~ClientClass()
{
	delete GridImage;
	delete WhiteStone;
	delete BlackStone;
	closesocket(s);
	WSACleanup();
}

void ClientClass::InitClient(HWND hWnd, HDC * Front, HDC * Back)
{
	FrontBuffer = Front;
	BackBuffer = Back;

	WSAStartup(MAKEWORD(2, 2), &wsadata);
	s = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = 20;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	if (connect(s, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		MessageBox(NULL, TEXT("Connect Failed"), TEXT("Error"), MB_OK);
		return;
	}
	else
		MessageBox(NULL, TEXT("Connect Success"), TEXT("Success"), MB_OK);

	WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_READ);
}

void ClientClass::Render()
{
	MoveToEx(*FrontBuffer, 0, 845, NULL);
	LineTo(*FrontBuffer, 845, 845);
	TextOut(*FrontBuffer, 0, 860, wbuff, (int)_tcslen(wbuff));

	for (int i = 0; i < ChatLog.size(); i++)
	{
		TextOut(*FrontBuffer, 0, WIN_HEIGHT + (i * 20) - 205, ChatLog[i].c_str(), ChatLog[i].size());
	}

	//GridImage->Render(*FrontBuffer, *BackBuffer);
	//WhiteStone->Render(*FrontBuffer, *BackBuffer);
	//BlackStone->Render(*FrontBuffer, *BackBuffer);

	DrawGrid({ 25, 25 }, 19);
}

void ClientClass::ReadMessage(WPARAM wParam)
{
	 msgLen = recv(s, buff, 128, 0);
	 buff[msgLen] = NULL;
#ifdef _UNICODE
	 msgLen = MultiByteToWideChar(CP_ACP, 0, buff, strlen(buff), NULL, NULL);
	 MultiByteToWideChar(CP_ACP, 0, buff, strlen(buff), msg, msgLen);
	 msg[msgLen] = NULL;
#else
	 strcpy_s(msg, buff);
#endif
	 if (ChatLog.size() >= MAX_CHAT)
		 ChatLog.erase(ChatLog.begin());

	ChatLog.push_back(msg);
}

void ClientClass::CheckKeyDown(WPARAM wParam)
{
	if (wParam != VK_RETURN && wParam != VK_BACK)
	{
		wbuff[Cnt++] = wParam;
		wbuff[Cnt] = NULL;

#ifdef _UNICODE
		msgLen = WideCharToMultiByte(CP_ACP, 0, wbuff, -1, NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, wbuff, -1, buff, msgLen, NULL, NULL);
#else
		strcpy_s(buff, wbuff);
		msgLen = strlen(buff);
#endif
	}
	else if (wParam == VK_BACK && Cnt > 0)
	{
		wbuff[Cnt--] = NULL;
	}
	else if (wParam == VK_RETURN && Cnt > 0)
	{
		if (s == INVALID_SOCKET)
		{
			return;
		}

		// -9 = Chat
		string temp = to_string(-9);
		temp += buff;

		send(s, temp.c_str(), temp.size(), 0);

		Cnt = 0;
		memset(msg, 0, sizeof(msg));
		memset(buff, 0, sizeof(buff));
		memset(wbuff, 0, sizeof(wbuff));
	}
}

void ClientClass::MouseDown(POINT MousePos)
{
	// -8 = System
	string temp = to_string(-8);
	//temp += "MousePosition (";
	temp += to_string(MousePos.x);
	temp += ", ";
	temp += to_string(MousePos.y);
	//temp += ")";

	send(s, temp.c_str(), temp.size(), 0);
}

void ClientClass::DrawLine(POINT start, POINT end)
{
	MoveToEx(*FrontBuffer, start.x, start.y, NULL);
	LineTo(*FrontBuffer, end.x, end.y);
}

void ClientClass::DrawGrid(POINT pos, int Num)
{
	int Max_Dist = 700;
	int Dist = 40;

	for (int x = pos.x; x < Num * Dist + pos.x; x += Dist)
		for (int y = pos.y; y < Num * Dist + pos.y; y += Dist)
		{
			DrawLine({ x, y }, { x, Max_Dist });
			DrawLine({ x, y }, { Max_Dist, y });
		}
}

