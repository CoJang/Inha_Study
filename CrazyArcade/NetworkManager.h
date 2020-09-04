#pragma once

#define WM_ASYNC WM_USER + 2

enum NetWorkType
{
	HOST,
	CLIENT
};

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
	NetworkManager();
	~NetworkManager();
	
	void InitNetworkManager(HWND input);
	bool OperateServer();
	bool Accept();

	void SetMsg(string msg);
	void SetMsg(char* msg);
	void ReadMessage(WPARAM wParam);
	void BroadcastMsg(string msg, bool usemembermsg);
	void SendMsg(SOCKET target, string msg);

	inline void SetNetworkType(NetWorkType type) { Ntype = type; };
	inline void SetIP(string ip) { IP_ADDR = ip; };

	inline int GetClientNum() { return ClientList.size(); };
};

