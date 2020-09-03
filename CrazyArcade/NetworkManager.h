#pragma once

#define WM_ASYNC WM_USER + 2

class NetworkManager
{
private:
	HWND hWnd;
	WSADATA wsadata;
	SOCKET ServerSocket, ClientSocket;
	SOCKADDR_IN addr = { 0 }, c_addr;
	string IP_ADDR;
	int size, msgLen;
	char buff[128];

	vector<SOCKET> ClientList;
public:
	NetworkManager();
	~NetworkManager();
	
	void InitNetworkManager(HWND input);
	bool Accept();

	bool OperateServer();
	void ReadMessage(WPARAM wParam);

	inline void SetIP(string ip) { IP_ADDR = ip; };

	inline int GetClientNum() { return ClientList.size(); };
};

