#include "stdafx.h"
#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
	size = 0; msgLen = 0;
	memset(buff, 0, sizeof(buff));
}

NetworkManager::~NetworkManager()
{
	for (int i = 0; i < ClientList.size(); i++)
		closesocket(ClientList[i]);

	closesocket(ServerSocket);
	WSACleanup();
}

void NetworkManager::InitNetworkManager(HWND input)
{
	hWnd = input;
}

bool NetworkManager::OperateServer()
{
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = 20;
	addr.sin_addr.S_un.S_addr = inet_addr(IP_ADDR.c_str());

	if (bind(ServerSocket, (LPSOCKADDR)&addr, sizeof(addr)))
	{
		MessageBox(NULL, TEXT("Binding Failed"), TEXT("Error"), MB_OK);
	}
	else
	{
		cout << "Binding Success!" << endl;
		WSAAsyncSelect(ServerSocket, hWnd, WM_ASYNC, FD_ACCEPT);

		if (listen(ServerSocket, 5) == SOCKET_ERROR)
		{
			MessageBox(NULL, TEXT("Listen Failed"), TEXT("Error"), MB_OK);
		}
		else
		{
			cout << "Listen Success!" << endl;
			return true;
		}
	}
	
	if (connect(ServerSocket, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		MessageBox(NULL, TEXT("Connect Failed"), TEXT("Error"), MB_OK);
		return false;
	}
	else
	{
		cout << "Connect Success!" << endl;
		WSAAsyncSelect(ServerSocket, hWnd, WM_ASYNC, FD_READ);
		return true;
	}

	return true;
}

void NetworkManager::ReadMessage(WPARAM wParam)
{
	msgLen = recv(wParam, buff, 128, 0);
	buff[msgLen] = NULL;
}

bool NetworkManager::Accept()
{
	size = sizeof(c_addr);
	ClientSocket = accept(ServerSocket, (LPSOCKADDR)&c_addr, &size);
	if (ClientSocket == SOCKET_ERROR) return false;
	WSAAsyncSelect(ClientSocket, hWnd, WM_ASYNC, FD_READ);
	ClientList.push_back(ClientSocket);
	return true;
}
