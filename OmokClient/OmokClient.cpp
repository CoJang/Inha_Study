// OmokClient.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "OmokClient.h"
#include "ClientClass.h"

#define MAX_LOADSTRING 100

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
    LoadStringW(hInstance, IDC_OMOKCLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OMOKCLIENT));

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

    return (int) msg.wParam;
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OMOKCLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OMOKCLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, WIN_WIDTH, WIN_HEIGHT, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	static HDC BackBuffer[2];
	static RECT winRect;
	static HBITMAP BackBitmap, oldBitmap;
	static ClientClass* Client;
	static POINT MousePos;

    switch (message)
    {
	case WM_CREATE:
		GetWindowRect(hWnd, &winRect);

		BackBuffer[0] = CreateCompatibleDC(hdc);
		BackBuffer[1] = CreateCompatibleDC(BackBuffer[0]);

		BackBitmap = CreateCompatibleBitmap(hdc, winRect.right, winRect.bottom); //도화지 준비!
		oldBitmap = (HBITMAP)SelectObject(BackBuffer[0], BackBitmap);

		Client = new ClientClass;
		Client->InitClient(hWnd, &BackBuffer[0], &BackBuffer[1]);
		SetTimer(hWnd, 99, 60, NULL);
		MousePos = { 0, 0 };
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
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
			hdc = BeginPaint(hWnd, &ps);
			BackBitmap = CreateCompatibleBitmap(hdc, winRect.right, winRect.bottom);
			oldBitmap = (HBITMAP)SelectObject(BackBuffer[0], BackBitmap);
			PatBlt(BackBuffer[0], 0, 0, winRect.right, winRect.bottom, WHITENESS);

			Client->Render();

			BitBlt(hdc, 0, 0, winRect.right, winRect.bottom, BackBuffer[0], 0, 0, SRCCOPY);
			SelectObject(BackBuffer[0], oldBitmap);

			EndPaint(hWnd, &ps);
        }
        break;
	case WM_ASYNC:
		switch (lParam)
		{
		case FD_READ:
			Client->ReadMessage(wParam);
			InvalidateRgn(hWnd, NULL, FALSE);
			break;
		default:
			break;
		}
		break;
	case WM_CHAR:
		Client->CheckKeyDown(wParam);
		InvalidateRgn(hWnd, NULL, FALSE);
		break;
	case WM_LBUTTONDOWN:
		MousePos.x = LOWORD(lParam);
		MousePos.y = HIWORD(lParam);
		Client->MouseDown(MousePos);
		break;
	case WM_TIMER:
		InvalidateRgn(hWnd, NULL, FALSE);
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
		delete Client;
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
