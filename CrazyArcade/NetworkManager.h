#pragma once

#define WM_ASYNC WM_USER + 2

enum NetWorkType
{
	HOST,
	CLIENT
};

enum Header
{
	COMMAND,
	USER,
	USERINIT,
	BOMB,
};

typedef struct Packet
{
	Header head;

	int PlayerFlag;
	POINT Pos;
	int Power;
	string Cmd;
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
	Packet PacketMsg;

	NetworkManager();
	~NetworkManager();
	
	void InitNetworkManager(HWND input);
	bool OperateServer();
	bool Accept();

	void ReadMessage(WPARAM wParam);
	int SetPlayerFlag();

	inline void SetIP(string ip) { IP_ADDR = ip; };
	inline int GetClientNum() { return ClientList.size(); };
	inline NetWorkType GetNetworkType() { return Ntype; };
	inline void SetNetworkType(NetWorkType type) { Ntype = type; };

	void SendPacket();
	void SendPacket(Packet packet);
	void SendPlayerPacket(int playerflag, POINT pos);

	void PrintPacket();
};

