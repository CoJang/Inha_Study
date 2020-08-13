#include "stdafx.h"
#include "ServerClass.h"

ServerClass::ServerClass()
{
	Cnt = 0; size = 0; msgLen = 0; PosY = 0;
	memset(msg, 0, sizeof(msg));
	memset(buff, 0, sizeof(buff));
	memset(wbuff, 0, sizeof(wbuff));

	GridImage = new ImageObject;
	GridImage->InitImageObject(TEXT("images/board.bmp"), { 0, 0 });
}


ServerClass::~ServerClass()
{
	delete GridImage;

	for (int i = 0; i < ClientList.size(); i++)
		closesocket(ClientList[i]);

	closesocket(s);
	WSACleanup();
}

void ServerClass::InitServer(HWND hWnd, HDC* Front, HDC* Back)
{
	FrontBuffer = Front;
	BackBuffer = Back;

	WSAStartup(MAKEWORD(2, 2), &wsadata);
	s = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = 20;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)))
	{
		MessageBox(NULL, TEXT("Binding Failed"), TEXT("Error"), MB_OK);
		return;
	}
	else
	{
		MessageBox(NULL, TEXT("Binding Success"), TEXT("Success"), MB_OK);
	}

	WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_ACCEPT);

	if (listen(s, SOMAXCONN) == SOCKET_ERROR)
	{
		MessageBox(NULL, TEXT("Listen Failed"), TEXT("Error"), MB_OK);
		return;
	}
	else
	{
		MessageBox(NULL, TEXT("Listen Success"), TEXT("Success"), MB_OK);
	}
}

void ServerClass::Render()
{
	MoveToEx(*FrontBuffer, 0, 830, NULL);
	LineTo(*FrontBuffer, 830, 830);
	TextOut(*FrontBuffer, 0, 845, wbuff, (int)_tcslen(wbuff));

	for (int i = 0; i < ChatLog.size(); i++)
	{
		TextOut(*FrontBuffer, 0, WIN_HEIGHT + (i * 20) - 230, ChatLog[i].c_str(), ChatLog[i].size());
	}

	//GridImage->Render(*FrontBuffer, *BackBuffer);
	DrawGrid(19);
}

void ServerClass::Accept(HWND hWnd)
{
	size = sizeof(c_addr);
	cs = accept(s, (LPSOCKADDR)&c_addr, &size);
	WSAAsyncSelect(cs, hWnd, WM_ASYNC, FD_READ);
	ClientList.push_back(cs);
}

void ServerClass::ReadMessage(WPARAM wParam)
{
	msgLen = recv(wParam, buff, 128, 0);
	buff[msgLen] = NULL;

#ifdef _UNICODE
	msgLen = MultiByteToWideChar(CP_ACP, 0, buff, strlen(buff), NULL, NULL);
	MultiByteToWideChar(CP_ACP, 0, buff, strlen(buff), msg, msgLen);
	msg[msgLen] = NULL;
#else
	strcpy_s(msg, buff);
	send(cs, msg, strlen(msg), 0);
#endif
	if (msg[1] == '9')
	{
		string temp = MakeStrMsg(cs, buff);
		for (int i = 0; i < ClientList.size(); i++)
			send(ClientList[i], temp.c_str(), temp.size(), 0);
	}

	if (ChatLog.size() >= MAX_CHAT)
		ChatLog.erase(ChatLog.begin());

	// 8 = System, 9 = Chat
	if (msg[1] == '9')
	{
		wstring wtemp = MakeWStrMsg(cs, msg);
		ChatLog.push_back(wtemp.c_str());
	}
}

void ServerClass::CheckKeyDown(WPARAM wParam)
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
		string temp = MakeStrMsg(buff);
		wstring wtemp = MakeWStrMsg(wbuff);

		if (ChatLog.size() >= MAX_CHAT)
			ChatLog.erase(ChatLog.begin());

		ChatLog.push_back(wtemp);

		for (int i = 0; i < ClientList.size(); i++)
			send(ClientList[i], temp.c_str(), temp.size(), 0);

		Cnt = 0;
		memset(msg, 0, sizeof(msg));
		memset(buff, 0, sizeof(buff));
		memset(wbuff, 0, sizeof(wbuff));
	}
}

wstring ServerClass::MakeWStrMsg(TCHAR* Msg)
{
	wstring wtemp = TEXT("Server :");
	wtemp += Msg;
	return wtemp;
}

wstring ServerClass::MakeWStrMsg(SOCKET ID, TCHAR* Msg)
{
	wstring Message(&Msg[2], (int)_tcslen(Msg) - 1);
	wstring wtemp = TEXT("Client");
	wtemp += to_wstring(ID);
	wtemp += TEXT(": ");
	wtemp += Message;
	return wtemp;
}

string ServerClass::MakeStrMsg(char* Msg)
{
	string temp = "Server :";
	temp += Msg;
	return temp;
}

string ServerClass::MakeStrMsg(SOCKET ID, char* Msg)
{
	string Message(&Msg[2], strlen(Msg) - 1);
	string temp = "Client";
	temp += to_string(ID);
	temp += ": ";
	temp += Message;
	return temp;
}

void ServerClass::DrawLine(POINT start, POINT end)
{
	MoveToEx(*FrontBuffer, start.x, start.y, NULL);
	LineTo(*FrontBuffer, end.x, end.y);
}

void ServerClass::DrawGrid(int Num)
{
	int Max_Dist = 700;
	int Dist = 40;

	for(int x = 0; x < Num * Dist; x += Dist)
		for (int y = 0; y < Num * Dist; y += Dist)
		{
			DrawLine({ x, y }, { x, Max_Dist });
			DrawLine({ x, y }, { Max_Dist, y });
		}
}
