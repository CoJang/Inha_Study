// GalsPanic.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Main.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
enum SceneType;

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
    LoadStringW(hInstance, IDC_GALSPANIC, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GALSPANIC));

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

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GALSPANIC);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

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

extern Singleton singleton;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static POINT mousePos;
	static HDC hdc;
	static HDC BackBuffer[2];
	static HBITMAP BackBitmap, oldBitmap;
	static RECT winRect;

    switch (message)
    {
	case WM_CREATE:
		{
			//AllocConsole();
			SetTimer(hWnd, 99, ElapseTime, NULL);
			GetWindowRect(hWnd, &winRect);

			BackBuffer[0] = CreateCompatibleDC(hdc);
			BackBuffer[1] = CreateCompatibleDC(BackBuffer[0]);

			BackBitmap = CreateCompatibleBitmap(hdc, winRect.right, winRect.bottom); //도화지 준비!
			oldBitmap = (HBITMAP)SelectObject(BackBuffer[0], BackBitmap);			 //도화지 세팅

			singleton.InitSingleton(&BackBuffer[0], &BackBuffer[1]);
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
            hdc = BeginPaint(hWnd, &ps);
			BackBitmap = CreateCompatibleBitmap(hdc, winRect.right, winRect.bottom); 
			oldBitmap = (HBITMAP)SelectObject(BackBuffer[0], BackBitmap); 
			PatBlt(BackBuffer[0], 0, 0, winRect.right, winRect.bottom, WHITENESS);

			singleton.GetSceneManager()->GetInstance()->Update();
			singleton.GetSceneManager()->GetInstance()->Render();
			singleton.GetSceneManager()->GetInstance()->CheckKeyDown(wParam);

			BitBlt(hdc, 0, 0, winRect.right, winRect.bottom, BackBuffer[0], 0, 0, SRCCOPY);
			SelectObject(BackBuffer[0], oldBitmap);

            EndPaint(hWnd, &ps);
        }
        break;
	case WM_KEYDOWN:
		{
			switch (singleton.GetSceneManager()->GetInstance()->GetType())
			{
				case TITLE:
				{
					static wstring input;
					if (wParam != VK_RETURN && wParam != VK_BACK)
					{
						input += wParam;
						singleton.GetSceneManager()->GetInstance()->SetID(input);
					}
					else if (wParam == VK_BACK && input.size() > 0)
					{
						input.erase(input.begin() + input.size() - 1);
						singleton.GetSceneManager()->GetInstance()->SetID(input);
					}
					else
					{
						singleton.GetSceneManager()->GetInstance()->SetID(input);
						input = TEXT("");
					}
				}
				break;
			case GAME:
				break;
			case GAMEOVER:
				break;
		} // end of switch(singleton.GetSceneManager()->GetInstance()->GetType())
	} // end of WM_KEYDOWN:
	break;
	case WM_LBUTTONUP:
		{
			mousePos.x = LOWORD(lParam);
			mousePos.y = HIWORD(lParam);

			singleton.GetSceneManager()->GetInstance()->CheckClick(mousePos, 0);
		}
		break;
	case WM_MOUSEMOVE:
		{
			mousePos.x = LOWORD(lParam);
			mousePos.y = HIWORD(lParam);

			singleton.GetSceneManager()->GetInstance()->CheckClick(mousePos, 2);
		}
		break;
	case WM_TIMER:
		{
			InvalidateRgn(hWnd, NULL, FALSE);
		}
		break;
	case WM_SIZE:
		GetWindowRect(hWnd, &winRect);
		break;
    case WM_DESTROY:
		//FreeConsole();
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
