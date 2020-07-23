// 0709.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "0709.h"


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
    LoadStringW(hInstance, IDC_MY0709, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0709));

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
    //wcex.hIcon          = LoadIcon(hInstance, IDI_QUESTION);
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_IBEAM);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY0709);
    wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm		= LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON1));

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

   HWND hWnd = CreateWindowW(szWindowClass, _T("코장의 첫 윈도우"), WS_OVERLAPPEDWINDOW,
      200, 200, 600, 800, nullptr, nullptr, hInstance, nullptr);

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
static TCHAR str[100];
static int Count = 0;
static RECT rc;
void DrawGrid(HDC, float, float, float, float, float);
void DrawCircle(HDC, int, int, int, int);
void DrawCircle(HDC, int, int, int);

void DrawSunflower(HDC, int, int, int, int);

static POINT circlePos;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		rc.left = 0;
		rc.top = 0;
		rc.bottom = 20;
		rc.right = 600;

		circlePos.x = 250;
		circlePos.y = 250;

		//CreateCaret(hWnd, NULL, 15, 15);
		//ShowCaret(hWnd);
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
	case WM_CHAR:
		{
			if (wParam == VK_BACK && Count > 0 )
			{
				Count--;
				if (Count == 0 && rc.top > 0 && rc.bottom)
				{
					rc.top -= 20;
					rc.bottom -= 20;
				}
			}
			else
			{
				str[Count++] = wParam;
			}
			if (wParam == VK_RETURN)
			{
				Count = 0;
				rc.top += 20;
				rc.bottom += 20;
			}
			str[Count] = NULL;

			if (wParam == VK_UP && circlePos.y > 0)
			{
				circlePos.y -= 50;
			}
			if (wParam == VK_LEFT && circlePos.x > 0)
			{
				circlePos.x -= 50;
			}
			if (wParam == VK_DOWN)
			{
				circlePos.y += 50;
			}
			if (wParam == VK_RIGHT)
			{
				circlePos.x += 50;
			}
			
			if (wParam == VK_ESCAPE)
				PostQuitMessage(0);

			// hWnd 윈도우 영역을 다시 그려라. [WM_PAINT 이벤트 다시 발생시킴]
			InvalidateRgn(hWnd, NULL, TRUE);

			//RECT rc;
			//rc.left = 0;
			//rc.top = 0;
			//rc.bottom = 15;
			//rc.right = 70;
			//InvalidateRect(hWnd, &rc, TRUE);
		}
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

			//TextOut(hdc, 0, Ypos, str, _tcslen(str));
			//DrawText(hdc, str, _tcslen(str), &rc, NULL);
			//SIZE size;
			//GetTextExtentPoint(hdc, str, _tcslen(str), &size);
			//SetCaretPos(size.cx, rc.top);

			//DrawGrid(hdc, 100, 100, 500, 500, 50);

			//DrawCircle(hdc, circlePos.x, circlePos.y, 50);
			DrawSunflower(hdc, 200, 200, 50, 6);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		//HideCaret(hWnd);
		//DestroyCaret();
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

void DrawGrid(HDC hdc, float StartX, float StartY, float LastX, float LastY, float Distance)
{
	for (int x = StartX; x <= LastX; x += Distance)
	{
		for (int y = StartY; y <= LastY; y += Distance)
		{
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, x, LastY);

			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, LastX, y);
		}
	}
}

void DrawCircle(HDC hdc, int CenterX, int CenterY, int rX, int rY)
{
	Ellipse(hdc, CenterX - rX, CenterY - rY, CenterX + rX, CenterY + rY);
}

void DrawCircle(HDC hdc, int CenterX, int CenterY, int r)
{
	Ellipse(hdc, CenterX - r, CenterY - r, CenterX + r, CenterY + r);
}

double degree_to_radian(const double degree)
{
	return degree / 180 * 3.141592;
}

void DrawSunflower(HDC hdc, int CenterX, int CenterY, int r, int circleNum)
{
	if (circleNum < 3) return;
	DrawCircle(hdc, CenterX, CenterY, r);
	int halftheta = 360 / (circleNum * 2);
	// sin@ = r2 / (r1 + r2)
	// sin@(r1 + r2) = r2
	// r1sin@ + r2sin@ = r2
	// r1sin@ = r2 - r2sin@
	// r1 = r2(1 - sin@)
	// r1 / (1 - sin@) = r2
	int smallR = r * sin(degree_to_radian(halftheta)) / (1 - sin(degree_to_radian(halftheta)));
	int angle = 0;
	
	for (int i = 0; i < 360 / (halftheta * 2); i++)
	{
		int smallX = (smallR + r) * cos(degree_to_radian(angle)) + CenterX;
		int smallY = (smallR + r) * sin(degree_to_radian(angle)) + CenterY;
		DrawCircle(hdc, smallX, smallY, smallR);
		angle += (halftheta * 2);
	}

}