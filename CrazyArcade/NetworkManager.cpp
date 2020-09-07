#include "stdafx.h"
#include "NetworkManager.h"

extern Singleton* singleton;

NetworkManager::NetworkManager()
{
	size = 0; msgLen = 0;
	memset(buff, 0, sizeof(buff));

	memset(&PacketMsg, 0, sizeof(Packet));
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
	msgLen = recv(wParam, (char*)&PacketMsg, sizeof(Packet), 0);
	
	//PrintPacket();

	CURRENT_SCENE->ReceiveData(&PacketMsg);

	memset(&PacketMsg, 0, sizeof(Packet));
}

int NetworkManager::SetPlayerFlag()
{
	for (int i = 0; i < ClientList.size(); i++)
	{
		PacketMsg.head = USERINIT;
		PacketMsg.PlayerFlag = i + 2;
		switch (PacketMsg.PlayerFlag)
		{
		case 2:
			PacketMsg.Pos = { 702, 78 };
			break;
		case 3:
			PacketMsg.Pos = { 78, 598 };
			break;
		case 4:
			PacketMsg.Pos = { 702, 598 };
			break;
		}
		PacketMsg.Power = 1;
		send(ClientList[i], (char*)&PacketMsg, sizeof(Packet), 0);
	}
	return 0;
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

void NetworkManager::SendPlayerPacket(int playerflag, POINT pos)
{
	PacketMsg.head = USER;
	PacketMsg.Pos = pos;
	PacketMsg.PlayerFlag = playerflag;

	SendPacket();
}

void NetworkManager::SendPacket()
{
	if (Ntype == CLIENT)
	{
		send(ServerSocket, (char*)&PacketMsg, sizeof(Packet), 0);
	}
	else if (Ntype == HOST)
	{
		for (SOCKET client : ClientList)
		{
			send(client, (char*)&PacketMsg, sizeof(Packet), 0);
		}
	}
}

void NetworkManager::PrintPacket()
{
	cout << "== Received Packet Info ==" << endl;

	switch (PacketMsg.head)
	{
	case COMMAND:
		cout << "Header : Command" << endl;
		break;
	case BOMB:
		cout << "Header : Bomb" << endl;
		break;
	case USER:
		cout << "Header : User" << endl;
		break;
	case USERINIT:
		cout << "Header : User Init" << endl;
		break;
	default:
		cout << "Header : Unknown" << endl;
		break;
	}
	
	cout << "PlayerFlag : " << PacketMsg.PlayerFlag << endl;
	cout << "Pos.x : " << PacketMsg.Pos.x << endl;
	cout << "Pos.y : " << PacketMsg.Pos.y << endl;
	cout << "Bomb Power : " << PacketMsg.Power << endl;
	if(PacketMsg.head == COMMAND)
		cout << "Command : " << PacketMsg.Cmd << endl;

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
