#include "stdafx.h"

#include <stdlib.h>
#include <string>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")
#define Buf_Size 1024

void Error(char* msg);
void Log(char* msg);

char strServerIP[] = "165.246.192.68";
char strClientIP[] = "127.0.0.1";
char strPort[] = "12345";

void ServerCode();

int main()
{
	ServerCode();
    return 0;
}

void Error(char * msg)
{
	Log(msg);
	exit(1);
}

void Log(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
}

void ServerCode()
{
	WSADATA wsaData;
	SOCKET serverSocket; 
	SOCKET clientSocket;
	char msg[Buf_Size];
	int strLength;

	SOCKADDR_IN serverAddr;
	SOCKADDR_IN clientAddr;
	int clientAddrSize;

	// Version Select : 2, 2
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		Error("WSAStartup error");

	// TCP/IP (AF_INET = PF_INET)
	// SOCK_STREAM = TCP/IP, SOCK_DGRAM = UDP
	serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET)
		Error("Socket() Error");

	memset(&serverAddr, 0, sizeof(serverAddr));
	// Using IPv4
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(atoi(strPort));

	if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		Error("Bind() Error");

	Log("Bind() OK");

	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
		Error("Listen() Error");

	Log("Listen() OK");


	clientAddrSize = sizeof(clientAddr);
	memset(msg, 0, sizeof(msg));

	int ClientNum = 1;
	for (int i = 0; i < SOMAXCONN; i++)
	{
		clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrSize);
		Log("Accept().....");
		if (clientSocket == SOCKET_ERROR)
			Error("Accept() Error");
		else
		{
			printf("Connected Client %d \n", ClientNum);
			ClientNum++;
		}

		while ((strLength = recv(clientSocket, msg, Buf_Size, 0)) != 0)
		{
			printf("%d Client : %s", i + 1, msg);
			send(clientSocket, msg, strLength, 0);
			memset(msg, 0, sizeof(msg));
		}

		closesocket(clientSocket);
		ClientNum--;
	}

	closesocket(serverSocket);
	WSACleanup();
	Log("Finish");
}
