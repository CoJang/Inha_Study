#include "stdafx.h"
#include "NetworkManager.h"

extern Singleton* singleton;

NetworkManager::NetworkManager()
{
	size = 0; msgLen = 0;
	memset(buff, 0, sizeof(buff));

	memset(&tempPacket, 0, sizeof(Packet));
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
		cout << "Binding Failed!" << endl;
		cout << "Trying Connect..." << endl;
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
			Ntype = HOST;
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
		MessageBox(NULL, TEXT("Connect Success"), TEXT("Success"), MB_OK);
		Ntype = CLIENT;
		WSAAsyncSelect(ServerSocket, hWnd, WM_ASYNC, FD_READ);
		return true;
	}

	return true;
}

void NetworkManager::ReadMessage(WPARAM wParam)
{
	msgLen = recv(wParam, (char*)&tempPacket, sizeof(Packet), 0);
	
	PrintPacket();

	if (tempPacket.head == COMMAND)
	{
		if (strcmp(tempPacket.Cmd.c_str(), "NextScene") == 0)
		{
			singleton->GetSceneManager()->NextScene();
		}
	}
	else if (tempPacket.head == BOMB)
	{
		CURRENT_SCENE->ReceiveData(&tempPacket);
	}

	memset(&tempPacket, 0, sizeof(Packet));
}

void NetworkManager::SendPacket(Packet packet)
{
	if (Ntype == CLIENT)
	{
		send(ServerSocket, (char*)&packet, sizeof(Packet), 0);
	}
	else if(Ntype == HOST)
	{
		for (SOCKET client : ClientList)
		{
			send(client, (char*)&packet, sizeof(Packet), 0);
		}
	}
}

void NetworkManager::SendPacket()
{
	if (Ntype == CLIENT)
	{
		send(ServerSocket, (char*)&tempPacket, sizeof(Packet), 0);
	}
	else if (Ntype == HOST)
	{
		for (SOCKET client : ClientList)
		{
			send(client, (char*)&tempPacket, sizeof(Packet), 0);
		}
	}
}

void NetworkManager::PrintPacket()
{
	cout << "== Received Packet Info ==" << endl;

	switch (tempPacket.head)
	{
	case COMMAND:
		cout << "Header : Command" << endl;
		break;
	case BOMB:
		cout << "Header : Bomb" << endl;
		break;
	default:
		cout << "Header : Unknown" << endl;
		break;
	}
	
	cout << "PlayerFlag : " << tempPacket.PlayerFlag << endl;
	cout << "Pos.x : " << tempPacket.Pos.x << endl;
	cout << "Pos.y : " << tempPacket.Pos.y << endl;
	cout << "Bomb Power : " << tempPacket.Power << endl;
	if(tempPacket.head == COMMAND)
		cout << "Command : " << tempPacket.Cmd << endl;

	cout << "== Received Packet Info End ==" << endl;
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
