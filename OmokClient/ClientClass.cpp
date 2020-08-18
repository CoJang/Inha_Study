#include "stdafx.h"
#include "ClientClass.h"


ClientClass::ClientClass()
{
	addr = { 0 };
	memset(msg, 0 , sizeof(msg));
	memset(buff, 0, sizeof(buff));
	memset(wbuff, 0, sizeof(wbuff));
	Cnt = 0; size = 0; msgLen = 0;
	IsMyTurn = false;
}

ClientClass::~ClientClass()
{
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
	addr.sin_addr.S_un.S_addr = inet_addr("61.101.25.157");

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

	DrawGrid({ 25, 25 }, 19);

	for (int i = 0; i < WhiteStoneContainer.size(); i++)
		DrawCircle(WhiteStoneContainer[i], 20);

	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(*FrontBuffer, hBrush);

	for (int i = 0; i < BlackStoneContainer.size(); i++)
		DrawCircle(BlackStoneContainer[i], 20);

	SelectObject(*FrontBuffer, oldBrush);
	DeleteObject(oldBrush);
	DeleteObject(hBrush);
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

	 ParseMessage(msg);
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
	temp += to_string(MousePos.x);
	temp += ", ";
	temp += to_string(MousePos.y);

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

	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(*FrontBuffer, hBrush);

	for (int x = 145; x <= 625; x += 240)
	{
		for (int y = 145; y <= 625; y += 240)
		{
			DrawCircle({ x, y }, 5);
		}
	}

	SelectObject(*FrontBuffer, oldBrush);
	DeleteObject(oldBrush);
	DeleteObject(hBrush);
}

// 8 = System, 9 = Chat
wstring ClientClass::ParseMessage(TCHAR* Msg)
{
	int i = 0;
	while (Msg[i] != '-')
	{
		i++;
	}
	i += 1;

	wstring wtemp;

	if (Msg[i] == '8') // Extract Point
	{
		string x, y;
		int j = 2; int flag = -1;
		while (msg[j] != ',')
		{
			x += msg[j++];
		}

		j++;
		while (msg[j] != ',')
		{
			y += msg[j++];
		}

		while (msg[j] != '\0')
		{
			flag = msg[j++];
		}
		POINT Pos = { atoi(x.c_str()), atoi(y.c_str()) };

		if (flag == 49)
			WhiteStoneContainer.push_back(Pos);
		else if (flag == 48)
			BlackStoneContainer.push_back(Pos);
	}
	else if (Msg[i] == '9') // Remove Flag
	{
		if (ChatLog.size() >= MAX_CHAT)
			ChatLog.erase(ChatLog.begin());

		wstring front(&Msg[0], i - 1);
		wstring back(&Msg[i + 1], (int)_tcslen(Msg) - 1);

		wtemp = front + back;

		ChatLog.push_back(wtemp.c_str());
	}

	return wtemp;
}

void ClientClass::DrawCircle(POINT pos, int R)
{
	Ellipse(*FrontBuffer, pos.x - R, pos.y - R, pos.x + R, pos.y + R);
}

