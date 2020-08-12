#include "stdafx.h"

#include <stdlib.h>
#include <string>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")
#define Buf_Size 1024

void Error(char* msg);
void Log(char* msg);

// °­»ç´Ô 192.168.0.44
char strServerIP[] = "165.246.192.68";
char strClientIP[] = "127.0.0.1";
char strPort[] = "12345";

void ClientCode();

int main()
{
	ClientCode();
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

void ClientCode()
{
	WSADATA wsaData;
	SOCKET serverSocket;
	char msg[Buf_Size];
	int strLength;

	SOCKADDR_IN serverAddr, clientAddr;

	Log("Start...");

	// Version Select : 2, 2
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		Error("WSAStartup error");

	// TCP/IP (AF_INET = PF_INET)
	// SOCK_STREAM = TCP/IP, SOCK_DGRAM = UDP
	serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET)
		Error("Socket() Error");

	Log("Socket OK");

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = inet_addr(strServerIP);
	serverAddr.sin_port = htons(atoi(strPort));

	if (connect(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		Error("Connect() Error");
	else
		Log("Connected!");

	while (1)
	{
		fputs("Input Message(Q to quit) : ", stdout);
		fgets(msg, Buf_Size, stdin);
		if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
			break;

		send(serverSocket, msg, strlen(msg), 0);
		strLength = recv(serverSocket, msg, Buf_Size - 1, 0);
		msg[strLength] = 0;
		printf("Message From Server %s", msg);
	}

	closesocket(serverSocket);
	WSACleanup();
}

