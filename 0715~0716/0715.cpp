// 0715.cpp : Defines the entry point for the application.
//
#pragma once
#include "stdafx.h"
#include "resource.h"
#include "0715.h"
#include "Cshape.h"
#include "MyStar.h"

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

LRESULT CALLBACK    ChildHwndProc(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_MY0715, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0715));

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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	//wcex.hIcon          = LoadIcon(hInstance, IDI_QUESTION);
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY0715);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON1));

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

#define ELAPSE 25

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT rectView;
	static POINT mousePos;
	static vector<Cshape*> ShapeList;
	static GAMEMODE GameMode;

    switch (message)
    {
	case WM_CREATE:
		{
			GetClientRect(hWnd, &rectView);
			mousePos = { 0, 0 };

			SetTimer(hWnd, 99, ELAPSE, NULL);
			GameMode = NORMAL;
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
			DrawStar(hdc, 400, 400, 150);
			bool col = false;

			for (int i = 0; i < ShapeList.size(); i++)
			{
				ShapeList[i]->Update();
				ShapeList[i]->Show(hdc);
				ShapeList[i]->Collision(rectView, ShapeList, GameMode);
			}
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
			{
				for (Cshape* shape : ShapeList)
				{
					delete shape;
				}
				KillTimer(hWnd, 99);
				PostQuitMessage(0);
			}
			if (wParam == VK_SPACE)
			{
				if(!ShapeList.empty())
					ShapeList.pop_back();
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			mousePos.x = LOWORD(lParam);
			mousePos.y = HIWORD(lParam);

			srand(time(NULL));

			random_device rd;
			mt19937_64 gen(rd());
			uniform_int_distribution<int> randShape(0, 2);
			uniform_int_distribution<int> randDir(-1, 1);

			int shape = randShape(gen);

			int speed = 10;
			int dirX = randDir(gen);
			int dirY = randDir(gen);
			while (dirX + dirX == 0)
			{
				dirX = randDir(gen);
				dirY = randDir(gen);
			}
			
			Cshape* newShape;

			if (shape == CIRCLE)
			{
				newShape = new MyCircle(mousePos.x, mousePos.y, speed, dirX, dirY);

			}
			else if(shape == RECTANGLE)
			{
				float angle = rand() % 30 + 5;
				newShape = new MyRect(mousePos.x, mousePos.y, speed, angle, dirX, dirY);
			}
			else
			{
				float angle = rand() % 30 + 5;
				newShape = new MyStar(mousePos.x, mousePos.y, speed, angle, dirX, dirY);
			}

			ShapeList.push_back(newShape);
		}
		break;
	case WM_TIMER:
		{
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		break;
	case WM_CHAR:
		{
			switch (wParam)
			{
			case '1':
				GameMode = NORMAL;
				break;
			case '2':
				GameMode = DIVIDE;
				break;
			case '3':
				GameMode = MERGE;
				break;
			}
		}
		break;
    case WM_DESTROY:
		{
			for (Cshape* shape : ShapeList)
			{
				delete shape;
			}
			KillTimer(hWnd, 99);
			PostQuitMessage(0);
		}
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

void DrawStar(HDC hdc, int x, int y, int r)
{
	POINT pt[5] = { 0 };

	POINT Center = { x, y };
	int angle = 72;

	for (int i = 0; i < 5; i++)
	{
		pt[i] = RotatePoint(Center, r, angle * i);
	}

	Polygon(hdc, pt, 5);
}

POINT RotatePoint(POINT p, int r, int degree)
{
	POINT temp = { p.x, p.y };

	temp.x = p.x + (r * cos(Deg2Rad(degree)));
	temp.y = p.y - (r * sin(Deg2Rad(degree)));
	return temp;
}
