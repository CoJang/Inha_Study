// SocketServerWINAPI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SocketServerWINAPI.h"
#include <vector>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

#define MAX_LOADSTRING 100
#define WM_ASYNC WM_USER + 2

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SOCKETSERVERWINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SOCKETSERVERWINAPI));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SOCKETSERVERWINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SOCKETSERVERWINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 300, 800, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static WSADATA wsadata;
	static SOCKET s, cs;
	static TCHAR msg[512], wbuff[128];
	static SOCKADDR_IN addr = { 0 }, c_addr;
	static int Cnt, size, msgLen;
	static int PosY = 0;
	static char buff[128];
	static vector<wstring> ChatLog;
	static vector<SOCKET> ClientList;

    switch (message)
    {
	case WM_CREATE:
		{
			WSAStartup(MAKEWORD(2, 2), &wsadata);
			s = socket(AF_INET, SOCK_STREAM, 0);
			addr.sin_family = AF_INET;
			addr.sin_port = 20;
			addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

			if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)))
			{
				MessageBox(NULL, TEXT("Binding Failed"), TEXT("Error"), MB_OK);
				return 0;
			}
			else
			{
				MessageBox(NULL, TEXT("Binding Success"), TEXT("Success"), MB_OK);
			}

			WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_ACCEPT);

			if (listen(s, 5) == SOCKET_ERROR)
			{
				MessageBox(NULL, TEXT("Listen Failed"), TEXT("Error"), MB_OK);
				return 0;
			}
			else
			{
				MessageBox(NULL, TEXT("Listen Success"), TEXT("Success"), MB_OK);
			}
		}
		break;
	case WM_ASYNC:
		switch (lParam)
		{
		case FD_ACCEPT:
			size = sizeof(c_addr);
			cs = accept(s, (LPSOCKADDR)&c_addr, &size);
			WSAAsyncSelect(cs, hWnd, WM_ASYNC, FD_READ);
			ClientList.push_back(cs);
			break;
		case FD_READ:
			msgLen = recv(wParam, buff, 128, 0);
			buff[msgLen] = NULL;
			
#ifdef _UNICODE
			msgLen = MultiByteToWideChar(CP_ACP, 0, buff, strlen(buff), NULL, NULL);
			MultiByteToWideChar(CP_ACP, 0, buff, strlen(buff), msg, msgLen);
			msg[msgLen] = NULL;

			for(int i = 0; i < ClientList.size(); i++)
				send(ClientList[i], buff, strlen(buff), 0);
#else
			strcpy_s(msg, buff);
			send(cs, msg, strlen(msg), 0);
#endif
			ChatLog.push_back(msg);
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		default:
			break;
		}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

			MoveToEx(hdc, 0, 700, NULL);
			LineTo(hdc, 700, 700);
			TextOut(hdc, 0, 715, wbuff, (int)_tcslen(wbuff));

			for (int i = 0; i < ChatLog.size(); i++)
			{
				TextOut(hdc, 0, i * 20, ChatLog[i].c_str(), ChatLog[i].size());
			}

            EndPaint(hWnd, &ps);
        }
        break;
	case WM_CHAR:
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
		else if (wParam == VK_RETURN)
		{
			if (s == INVALID_SOCKET)
			{
				return 0;
			}
			string temp = "Server : ";
			temp += buff;
			wstring wtemp = TEXT("Server : ");
			wtemp += wbuff;
			ChatLog.push_back(wtemp);
			for (int i = 0; i < ClientList.size(); i++)
				send(ClientList[i], temp.c_str(), temp.size(), 0);
			Cnt = 0;
			memset(buff, 0, sizeof(buff));
			memset(wbuff, 0, sizeof(wbuff));
		}
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
    case WM_DESTROY:
		closesocket(s);
		WSACleanup();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
