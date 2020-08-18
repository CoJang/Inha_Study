#include "stdafx.h"
#include "ServerClass.h"

ServerClass::ServerClass()
{
	Cnt = 0; size = 0; msgLen = 0;
	memset(msg, 0, sizeof(msg));
	memset(buff, 0, sizeof(buff));
	memset(wbuff, 0, sizeof(wbuff));

	IsWhiteTurn = false;
	GridPos = { 25, 25 };
	InitTile({ 25, 25 }, 19);
}


ServerClass::~ServerClass()
{
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
	addr.sin_addr.S_un.S_addr = inet_addr("61.101.25.157");

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

	if (listen(s, 5) == SOCKET_ERROR)
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
	MoveToEx(*FrontBuffer, 0, 845, NULL);
	LineTo(*FrontBuffer, 845, 845);
	TextOut(*FrontBuffer, 0, 860, wbuff, (int)_tcslen(wbuff));

	for (int i = 0; i < ChatLog.size(); i++)
	{
		TextOut(*FrontBuffer, 0, WIN_HEIGHT + (i * 20) - 205, ChatLog[i].c_str(), ChatLog[i].size());
	}

	DrawGrid({25, 25}, 19);

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

void ServerClass::Accept(HWND hWnd)
{
	size = sizeof(c_addr);
	cs = accept(s, (LPSOCKADDR)&c_addr, &size);
	if (cs == SOCKET_ERROR) return;
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
	int ColorFlag = -1;

	if (ChatLog.size() >= MAX_CHAT)
		ChatLog.erase(ChatLog.begin());

	string temp = MakeStrMsg(wParam, buff);

	// 8 = System, 9 = Chat
	if (msg[1] == '9')
	{
		// Broadcast Chatting Message
		for (int i = 0; i < ClientList.size(); i++)
			send(ClientList[i], temp.c_str(), temp.size(), 0);

		wstring wtemp = MakeWStrMsg(wParam, msg);
		ChatLog.push_back(wtemp.c_str());
	}
	else if (msg[1] == '8')
	{
		// Check Player's Turn
		if (ClientList.size() > 1)
		{
			if (wParam == ClientList[0] && IsWhiteTurn)
				return;
			else if (wParam == ClientList[1] && !IsWhiteTurn)
				return;
			else if (wParam == ClientList[0] && !IsWhiteTurn)
				ColorFlag = 0;
			else if (wParam == ClientList[1] && IsWhiteTurn)
				ColorFlag = 1;
		}
		else
			return;

		string x, y;
		int i = 2;
		while (msg[i] != ',')
		{
			x += msg[i++];
		}
		
		i++;
		while (msg[i] != '\0')
		{
			y += msg[i++];
		}

		POINT Pos = CircleClickCheck({ atoi(x.c_str()), atoi(y.c_str()) }, ColorFlag);

		if (Pos.x == -1 || Pos.y == -1) return;

		if (ClientList.size() > 1)
		{
			if (ColorFlag == 1)
			{
				WhiteStoneContainer.push_back(Pos);
				IsWhiteTurn = false;
			}
			else if (ColorFlag == 0)
			{
				BlackStoneContainer.push_back(Pos);
				IsWhiteTurn = true;
			}
		}

		string SystemMsg = StonePosFix(Pos, ColorFlag);

		// Broadcast System Message
		for (int i = 0; i < ClientList.size(); i++)
			send(ClientList[i], SystemMsg.c_str(), SystemMsg.size(), 0);

		if (CheckVictory(Pos, ColorFlag))
		{
			wstring WinMsg;
			if (ColorFlag == 0)
			{
				WinMsg = TEXT("System: Black Win!");
				SystemMsg = "Server: -9Black Win!";
			}
			else
			{
				WinMsg = TEXT("System: White Win!");
				SystemMsg = "Server: -9White Win!";
			}

			ChatLog.push_back(WinMsg.c_str());

			////////////////////////// 임시 방편 /////////////////////
			Sleep(1000);
			/////////////////////////////////////////////////////////
			
			for (int i = 0; i < ClientList.size(); i++)
				send(ClientList[i], SystemMsg.c_str(), SystemMsg.size(), 0);
		}
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

		// Broadcast Chatting Message
		for (int i = 0; i < ClientList.size(); i++)
			send(ClientList[i], temp.c_str(), temp.size(), 0);

		Cnt = 0;
		memset(msg, 0, sizeof(msg));
		memset(buff, 0, sizeof(buff));
		memset(wbuff, 0, sizeof(wbuff));
	}
}

// ColorFlag -1 = Unused, 0 = White, 1 = Black
POINT ServerClass::CircleClickCheck(POINT MousePos, int ColorFlag)
{
	for (int x = 0; x < 19; x++)
		for (int y = 0; y < 19; y++)
		{
			float distance = sqrt(pow(Tiles[x][y].Pos.x - MousePos.x, 2)
								+ pow(Tiles[x][y].Pos.y - MousePos.y, 2));

			if (distance <= 20)
			{
				if (Tiles[x][y].IsUsing == -1)
				{
					Tiles[x][y].IsUsing = ColorFlag;
					return POINT{ Tiles[x][y].Pos.x, Tiles[x][y].Pos.y };
				}
				else
					return POINT{ -1, -1 };
			}
		}

	return POINT{ -1, -1 };
}

bool ServerClass::CheckVictory(POINT StonePos, int CheckColor)
{
	int Cnt = 0;
	POINT index = { (StonePos.x - 25) / 40, (StonePos.y - 25) / 40 };

	int x(0), y(0);
	{
		// Check X axis
		for (x = 0; x < 19; x++)
		{
			if (Tiles[x][index.y].IsUsing == CheckColor)
				Cnt++;
			else
				Cnt = 0;

			if (Cnt > 4) return true;
		}

		// Check Y axis
		Cnt = 0;
		for (y = 0; y < 19; y++)
		{
			if (Tiles[index.x][y].IsUsing == CheckColor)
				Cnt++;
			else
				Cnt = 0;

			if (Cnt > 4) return true;
		}

		// Find Start index [ -X, +Y ]
		x = index.x, y = index.y;
		while (1)
		{
			if (x == 0 || x == 18 || y == 0 || y == 18)
				break;
			x--; y++;
		}

		// Check -X +Y axis
		Cnt = 0;
		while (1)
		{
			if (Tiles[x++][y--].IsUsing == CheckColor)
				Cnt++;
			else
				Cnt = 0;

			if (Cnt > 4) return true;

			if (x < 0 || x > 18 || y < 0 || y > 18)
				break;
		}

		// Find Start index [ +X, +Y ]
		x = index.x, y = index.y;
		while (1)
		{
			if (x == 0 || x == 18 || y == 0 || y == 18)
				break;
			x++; y++;
		}

		// Check +X +Y axis
		Cnt = 0;
		while (1)
		{
			if (Tiles[x--][y--].IsUsing == CheckColor)
				Cnt++;
			else
				Cnt = 0;

			if (Cnt > 4) return true;

			if (x < 0 || x > 18 || y < 0 || y > 18)
				break;
		}
	}

	return false;
}

wstring ServerClass::MakeWStrMsg(TCHAR* Msg)
{
	wstring wtemp = TEXT("Server: ");
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
	string temp = "Server: -9";
	temp += Msg;
	return temp;
}

string ServerClass::MakeStrMsg(SOCKET ID, char* Msg)
{
	string temp = "Client";
	temp += to_string(ID);
	temp += ": ";
	temp += Msg;
	return temp;
}

// flag 0 = Black Stone, flag 1 = White Stone
string ServerClass::StonePosFix(POINT pos, int flag)
{	// temp = "-8Posx, Posy, flag"
	string temp = to_string(-8);

	temp += to_string(pos.x);
	temp += ", ";
	temp += to_string(pos.y);
	temp += ", ";
	temp += to_string(flag);

	return temp;
}

void ServerClass::DrawLine(POINT start, POINT end)
{
	MoveToEx(*FrontBuffer, start.x, start.y, NULL);
	LineTo(*FrontBuffer, end.x, end.y);
}

void ServerClass::DrawGrid(POINT pos, int Num)
{
	int Max_Dist = 700;
	int Dist = 40;

	for (int x = pos.x; x < Num * Dist + pos.x; x += Dist)
	{
		for (int y = pos.y; y < Num * Dist + pos.y; y += Dist)
		{
			DrawLine({ x, y }, { x, Max_Dist });
			DrawLine({ x, y }, { Max_Dist, y });
		}
	}

	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(*FrontBuffer, hBrush);

	for (int x = 3; x < 19; x += 6)
	{
		for (int y = 3; y < 19; y += 6)
		{
			DrawCircle(Tiles[x][y].Pos, 5);
		}
	}

	SelectObject(*FrontBuffer, oldBrush);
	DeleteObject(oldBrush);
	DeleteObject(hBrush);
}

void ServerClass::DrawCircle(POINT pos, int R)
{
	Ellipse(*FrontBuffer, pos.x - R, pos.y - R, pos.x + R, pos.y + R);
}

void ServerClass::InitTile(POINT pos, int Num)
{
	int Max_Dist = 700;
	int Dist = 40;

	int i(0), j(0);

	for (int x = pos.x; x < Num * Dist + pos.x; x += Dist)
	{
		for (int y = pos.y; y < Num * Dist + pos.y; y += Dist)
		{
			Tiles[i][j % 19].Pos = { x, y };
			Tiles[i][j++ % 19].IsUsing = -1;
		}
		i++;
	}

}
