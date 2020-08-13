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
	GridImage->InitImageObject(TEXT("images/Omok_Ground.bmp"), { 0, 0 });
}


ClientClass::~ClientClass()
{
	delete GridImage;
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
	MoveToEx(*FrontBuffer, 0, 680, NULL);
	LineTo(*FrontBuffer, 680, 680);
	TextOut(*FrontBuffer, 0, 695, wbuff, (int)_tcslen(wbuff));

	for (int i = 0; i < ChatLog.size(); i++)
	{
		TextOut(*FrontBuffer, 0, i * 20, ChatLog[i].c_str(), ChatLog[i].size());
	}

	GridImage->Render(*FrontBuffer, *BackBuffer);
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

		send(s, buff, strlen(buff) + 1, 0);

		Cnt = 0;
		memset(msg, 0, sizeof(msg));
		memset(buff, 0, sizeof(buff));
		memset(wbuff, 0, sizeof(wbuff));
	}
}

void ClientClass::MouseDown(POINT MousePos)
{
	string temp = "MousePosition (";
	temp += to_string(MousePos.x);
	temp += ", ";
	temp += to_string(MousePos.y);
	temp += ")";

	send(s, temp.c_str(), temp.size(), 0);
}

