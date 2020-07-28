// 0728_MultyWindow.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "0728_MultyWindow.h"
#include <cmath>

#define MAX_LOADSTRING 100
#define Deg2Rad(x) (x * 3.141592 / 180)
#define Rad2Deg(x) (x / 3.141592 * 180)

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND ChildHwnd[3];
LRESULT CALLBACK ChildHwndProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildHwndProc2(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildHwndProc3(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

POINT RotatePoint(POINT p, int r, int degree);
POINT CramersRule(POINT P1, POINT P2, POINT P3, POINT P4);


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
    LoadStringW(hInstance, IDC_MY0728_MULTYWINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0728_MULTYWINDOW));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY0728_MULTYWINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY0728_MULTYWINDOW);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);

	wcex.lpfnWndProc = ChildHwndProc;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT("Child 1");
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	RegisterClassExW(&wcex);

	wcex.lpfnWndProc = ChildHwndProc2;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT("Child 2");
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	RegisterClassExW(&wcex);

	wcex.lpfnWndProc = ChildHwndProc3;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT("Child 3");
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	RegisterClassExW(&wcex);


    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

RECT winRect;
int BtnReturn = -1;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		GetClientRect(hWnd, &winRect);

		ChildHwnd[0] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Child 1"), NULL, WS_CHILD | WS_VISIBLE,
			0, 0, winRect.right * 0.66f , winRect.bottom / 2 - 1,
			hWnd, NULL, hInst, NULL);

		ChildHwnd[1] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Child 2"), NULL, WS_CHILD | WS_VISIBLE,
			0, winRect.bottom / 2 + 1, winRect.right * 0.66f, winRect.bottom / 2 - 1,
			hWnd, NULL, hInst, NULL);

		ChildHwnd[2] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Child 3"), NULL, WS_CHILD | WS_VISIBLE ,
			winRect.right * 0.66f, 0, winRect.right, winRect.bottom,
			hWnd, NULL, hInst, NULL);
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
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_SIZE:
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

LRESULT CALLBACK ChildHwndProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static POINT mousePos;

	switch (iMsg)
	{
	case WM_CREATE:
	{
		mousePos = { 0, 0 };

	}
	break;
	case WM_LBUTTONDOWN:
		{
			mousePos.x = LOWORD(lParam);
			mousePos.y = HIWORD(lParam);
			int r = 30;

			HDC hdc = GetDC(hDlg);
			switch (BtnReturn)
			{
			case 0:
				Ellipse(hdc, mousePos.x - r, mousePos.y - r, mousePos.x + r, mousePos.y + r);
				break;
			case 1:
				{
					POINT vertex[10];
					int tempAngle = 72;
					for (int i = 0; i < 10; i += 2)
					{
						vertex[i] = RotatePoint(mousePos, r, tempAngle * i);
					}
					vertex[1] = CramersRule(vertex[0], vertex[4], vertex[2], vertex[8]);
					vertex[3] = CramersRule(vertex[0], vertex[4], vertex[2], vertex[6]);
					vertex[5] = CramersRule(vertex[2], vertex[6], vertex[4], vertex[8]);
					vertex[7] = CramersRule(vertex[0], vertex[6], vertex[4], vertex[8]);
					vertex[9] = CramersRule(vertex[0], vertex[6], vertex[2], vertex[8]);
					Polygon(hdc, vertex, 10);
				}
				break;
			case 2:
				Rectangle(hdc, mousePos.x - r, mousePos.y - r, mousePos.x + r, mousePos.y + r);
				break;
			default:
				break;
			}
			ReleaseDC(hDlg, hdc);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hDlg, iMsg, wParam, lParam);
	}
}
POINT pos; int r; POINT vertex[10];
LRESULT CALLBACK ChildHwndProc2(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:
		{
			pos = { 450, 170 };
			r = 60;

			int tempAngle = 72;
			for (int i = 0; i < 10; i += 2)
			{
				vertex[i] = RotatePoint(pos, r, tempAngle * i);
			}
			vertex[1] = CramersRule(vertex[0], vertex[4], vertex[2], vertex[8]);
			vertex[3] = CramersRule(vertex[0], vertex[4], vertex[2], vertex[6]);
			vertex[5] = CramersRule(vertex[2], vertex[6], vertex[4], vertex[8]);
			vertex[7] = CramersRule(vertex[0], vertex[6], vertex[4], vertex[8]);
			vertex[9] = CramersRule(vertex[0], vertex[6], vertex[2], vertex[8]);
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hDlg, &ps);

			switch (BtnReturn)
			{
			case 0 :
				Ellipse(hdc, pos.x - r, pos.y - r, pos.x + r, pos.y + r);
				break;
			case 1:
				Polygon(hdc, vertex, 10);
				break;
			case 2:
				Rectangle(hdc, pos.x - r, pos.y - r, pos.x + r, pos.y + r);
				break;
			default:
				break;
			}
			EndPaint(hDlg, &ps);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hDlg, iMsg, wParam, lParam);
	}
}

#define IDC_BTN_CIRCLE 100 
#define IDC_BTN_STAR 101
#define IDC_BTN_RECT 102
int BtnWidth = 80; int BtnHeight = 25; RECT DlgRect;
int BtnPosX = 250;
LRESULT CALLBACK ChildHwndProc3(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hButton[3];

	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hDlg, &DlgRect);

		hButton[0] = CreateWindow(TEXT("Button"), TEXT("원"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BtnPosX - (BtnWidth / 2), 200, BtnWidth, BtnHeight,
			hDlg, (HMENU)IDC_BTN_CIRCLE,
			hInst, NULL);

		hButton[1] = CreateWindow(TEXT("Button"), TEXT("별"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BtnPosX - (BtnWidth / 2), 200 + BtnHeight * 2, BtnWidth, BtnHeight,
			hDlg, (HMENU)IDC_BTN_STAR,
			hInst, NULL);

		hButton[2] = CreateWindow(TEXT("Button"), TEXT("사각형"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BtnPosX - (BtnWidth / 2), 200 + BtnHeight * 4, BtnWidth, BtnHeight,
			hDlg, (HMENU)IDC_BTN_RECT,
			hInst, NULL);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BTN_CIRCLE:
			BtnReturn = 0;
			InvalidateRgn(ChildHwnd[1], NULL, TRUE);
			break;
		case IDC_BTN_STAR:
			BtnReturn = 1;
			InvalidateRgn(ChildHwnd[1], NULL, TRUE);
			break;
		case IDC_BTN_RECT:
			BtnReturn = 2;
			InvalidateRgn(ChildHwnd[1], NULL, TRUE);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hDlg, iMsg, wParam, lParam);
	}
}


POINT CramersRule(POINT P1, POINT P2, POINT P3, POINT P4)
{
	POINT CrossPoint = { 0, 0 };

	float a, b, c, d, e, f;

	a = P1.y - P2.y;
	b = -(P1.x - P2.x);
	c = P3.y - P4.y;
	d = -(P3.x - P4.x);
	e = a * P1.x + b * P1.y;
	f = c * P3.x + d * P3.y;

	CrossPoint.x = (e * d - b * f) / (a * d - b * c);
	CrossPoint.y = (a * f - e * c) / (a * d - b * c);

	return CrossPoint;
}

POINT RotatePoint(POINT p, int r, int degree)
{
	POINT temp = { p.x, p.y };

	temp.x = p.x + (r * cos(Deg2Rad(degree)));
	temp.y = p.y - (r * sin(Deg2Rad(degree)));
	return temp;
}