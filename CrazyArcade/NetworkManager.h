#pragma once

#define WM_ASYNC WM_USER + 2

enum NetWorkType
{
	HOST,
	CLIENT
};

struct BombPacket
{
	int PlayerFlag;
	POINT Pos;
	int Power;
};

enum Header
{
	COMMAND,
	BOMB,
};

typedef struct Packet
{
	Header head;

	int PlayerFlag;
	POINT Pos;
	int Power;
	char* Cmd;
}Packet;

class NetworkManager
{
private:
	NetWorkType Ntype;

	HWND hWnd;
	WSADATA wsadata;
	SOCKET ServerSocket, ClientSocket;
	SOCKADDR_IN addr = { 0 }, c_addr;
	string IP_ADDR;
	int size, msgLen;
	char buff[128];
	string Message;

	vector<SOCKET> ClientList;
public:
	Packet tempPacket;

	NetworkManager();
	~NetworkManager();
	
	void InitNetworkManager(HWND input);
	bool OperateServer();
	bool Accept();

	void ReadMessage(WPARAM wParam);
	void SendMsg(SOCKET target, string msg);

	inline void SetNetworkType(NetWorkType type) { Ntype = type; };
	inline void SetIP(string ip) { IP_ADDR = ip; };

	inline int GetClientNum() { return ClientList.size(); };

	void SendPacket();
	void SendPacket(Packet packet);

	void PrintPacket();
};

