// 0721_Menu.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "0721_Menu.h"
#include "MyStar.h"
#include <commdlg.h>
#include <iostream>
#include <ostream>
#include <fstream>

using namespace std;

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
    LoadStringW(hInstance, IDC_MY0721_MENU, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0721_MENU));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY0721_MENU));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY0721_MENU);
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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

wstring ReadData(const TCHAR* srcFileName);
void DrawShape(HDC hdc, POINT pos, int flag);
static MyStar star;

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
	static POINT mousePos;
	static int RecentShapeFlag;
	OPENFILENAME ofn;
	OPENFILENAME sfn;
	TCHAR str[100], lpstrFile[100] = TEXT("");
	TCHAR filter[] = TEXT("Every File(*.*)\0*.*\0Text File(*.txt)\0*.txt;*.doc\0");
	static wstring wstr;
	static RECT winrect;

	CHOOSECOLOR COLOR;
	static COLORREF temp[16], color;
	HBRUSH hBrush, oldBrush;


    switch (message)
    {
	case WM_CREATE:
		star.SetPos({ 0, 0 });
		RecentShapeFlag = -1;
		GetWindowRect(hWnd, &winrect);
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
			case ID_CAPTION_CIRCLE:
				RecentShapeFlag = 0;
                break;
			case ID_CAPTION_RECTANGLE:
				RecentShapeFlag = 1;
				break;
			case ID_CAPTION_STAR:
				RecentShapeFlag = 2;
				break;
			case ID_CAPTION_FILEOPEN:
				memset(&ofn, 0, sizeof(OPENFILENAME));
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = hWnd;
				ofn.lpstrFilter = filter;
				ofn.lpstrFile = lpstrFile;
				ofn.nMaxFile = 100;
				ofn.lpstrInitialDir = TEXT(".");
				if (GetOpenFileName(&ofn) != 0)
				{
					_stprintf_s(str, TEXT("%s 파일을 열겠습니까?"), ofn.lpstrFile);
					MessageBox(hWnd, L"File Open", L"열기 선택", MB_YESNOCANCEL);
					wstr = ReadData(lpstrFile);
					InvalidateRgn(hWnd, NULL, TRUE);
				}
				break;
			case ID_CAPTION_FILESAVE:
				memset(&sfn, 0, sizeof(OPENFILENAME));
				sfn.lStructSize = sizeof(OPENFILENAME);
				sfn.hwndOwner = hWnd;
				sfn.lpstrFilter = filter;
				sfn.lpstrFile = lpstrFile;
				sfn.nMaxFile = 256;
				sfn.lpstrInitialDir = TEXT(".");
				if (GetSaveFileName(&sfn) != 0)
				{
					_stprintf_s(str, TEXT("%s 파일을 저장하시겠습니까?"), sfn.lpstrFile);
					MessageBox(hWnd, L"File Save", L"저장 선택", MB_YESNOCANCEL);
					//wstr = ReadData(lpstrFile);
					//InvalidateRgn(hWnd, NULL, TRUE);
				}
				break;
			case ID_CAPTION_COLORDLG:
				for (int i = 0; i < 16; i++)
					temp[i] = RGB(rand() % 256, rand() % 256, rand() % 256);
				memset(&COLOR, 0, sizeof(CHOOSECOLOR));
				COLOR.lStructSize = sizeof(CHOOSECOLOR);
				COLOR.hwndOwner = hWnd;
				COLOR.lpCustColors = temp;
				COLOR.Flags = CC_FULLOPEN;
				if (ChooseColor(&COLOR) != 0)
				{
					color = COLOR.rgbResult;
					InvalidateRect(hWnd, NULL, TRUE);
				}
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

			hBrush = CreateSolidBrush(color);
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			DrawShape(hdc, mousePos, RecentShapeFlag);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);

			if (!wstr.empty())
			{
				//TextOut(hdc, 0, 0, wstr.c_str(), wstr.size());
				DrawText(hdc, wstr.c_str(), wstr.size(), &winrect, DT_LEFT);
			}

            EndPaint(hWnd, &ps);
        }
        break;
	case WM_LBUTTONDOWN:
		{
			mousePos.x = LOWORD(lParam);
			mousePos.y = HIWORD(lParam);

			InvalidateRgn(hWnd, NULL, TRUE);
		}
		break;
	case WM_CHAR:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void DrawShape(HDC hdc, POINT pos, int flag)
{
	int r = 20;
	switch (flag)
	{
	case 0:
		Ellipse(hdc, pos.x - r, pos.y - r, pos.x + r, pos.y + r);
		break;
	case 1:
		Rectangle(hdc, pos.x - r, pos.y - r, pos.x + r, pos.y + r);
		break;
	case 2:
		star.SetPos(pos);
		star.Show(hdc);
		break;
	default:
		break;
	}
}

wstring ReadData(const TCHAR* srcFileName)
{
	wstring str;
	ifstream SrcFile;
	char buff = 0;

	SrcFile.open(srcFileName, ios_base::binary | ios_base::in);

	if (!SrcFile.good())
	{
		printf("ERROR! SrcFile OpenFailed!\n"); return 0;
	}

	SrcFile.seekg(0, SrcFile.end);
	int FileSize = SrcFile.tellg();
	SrcFile.seekg(0, SrcFile.beg);

	
	while (SrcFile.get(buff))
	{
		str += buff;
	}

	//printf("Read Success!\n");
	SrcFile.close();

	return str;
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
