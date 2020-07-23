// 0722.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "0722.h"

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
    LoadStringW(hInstance, IDC_MY0722, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0722));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY0722));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY0722);
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

#pragma comment(lib, "msimg32.lib")

HBITMAP hBackImage;
BITMAP bitBack;

HBITMAP hTransparentsImage;
BITMAP bitTransparents;

HBITMAP hAnimImage;
BITMAP bitAnim;

const int Sprite_Width = 33;
const int Sprite_Height = 33;
int Anim_Frame_Max = 6;
int Anim_Frame_Min = 0;
int Anim_Frame_Cur = 0;
int Anim_Frame_Flag = 0;

RECT rectView;
void DrawRectText(HDC hdc);
bool IsSizeChanged = false;
POINT Pos = { 0, 0 };
POINT Dir = { 1, 1 };

void UpdateFrame();
void CreateBitmap();
void DeleteBitmap();


HBITMAP hDoubleBufferImage;
void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);

VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK KeyStateProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

TCHAR sKeyState[128];

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		CreateBitmap();
		SetTimer(hWnd, 99, 33, AniProc);
		SetTimer(hWnd, 100, 33, KeyStateProc);
		GetClientRect(hWnd, &rectView);
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
            // TODO: Add any drawing code that uses hdc here...
			//DrawBitmap(hWnd, hdc);
			DrawBitmapDoubleBuffering(hWnd, hdc);
			DrawRectText(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_KEYDOWN:


		break;
	case WM_SIZE:
		IsSizeChanged = true;
		GetClientRect(hWnd, &rectView);
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
    case WM_DESTROY:
		DeleteBitmap();
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

void CreateBitmap()
{
	hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/sigong.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	GetObject(hBackImage, sizeof(BITMAP), &bitBack);

	hTransparentsImage = (HBITMAP)LoadImage(NULL, TEXT("images/수지.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	GetObject(hTransparentsImage, sizeof(BITMAP), &bitTransparents);

	{
		hAnimImage = (HBITMAP)LoadImage(NULL, TEXT("images/character.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		GetObject(hAnimImage, sizeof(BITMAP), &bitAnim);

		Anim_Frame_Max = bitAnim.bmWidth / Sprite_Width - 1;
		Anim_Frame_Min = 0;
		Anim_Frame_Cur = Anim_Frame_Min;
	}
}

void DeleteBitmap()
{
	DeleteObject(hBackImage);
	DeleteObject(hTransparentsImage);
	DeleteObject(hAnimImage);
}

void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
	HDC hMemDC[2];
	HBITMAP oldBitmap[2];
	int bx, by;


	hMemDC[0] = CreateCompatibleDC(hdc);
	if (hDoubleBufferImage == NULL || IsSizeChanged)
	{
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
		IsSizeChanged = false;
	}

	oldBitmap[0] = (HBITMAP)SelectObject(hMemDC[0], hDoubleBufferImage);

	{
		hMemDC[1] = CreateCompatibleDC(hMemDC[0]);
		oldBitmap[1] = (HBITMAP)SelectObject(hMemDC[1], hTransparentsImage);
		bx = bitTransparents.bmWidth;
		by = bitTransparents.bmHeight;

		// 특정 색 제거
		TransparentBlt(hMemDC[0], 0, 0, bx, by, hMemDC[1], 0, 0, bx, by, RGB(255, 0, 255));
		SelectObject(hMemDC[1], oldBitmap[1]);
		DeleteDC(hMemDC[1]);
	}

	{
		hMemDC[1] = CreateCompatibleDC(hMemDC[0]);
		oldBitmap[1] = (HBITMAP)SelectObject(hMemDC[1], hBackImage);
		bx = bitBack.bmWidth;
		by = bitBack.bmHeight;

		BitBlt(hMemDC[0], 0, 0, bx, by, hMemDC[1], 0, 0, SRCCOPY);

		SelectObject(hMemDC[1], oldBitmap[1]);
		DeleteDC(hMemDC[1]);
	}

	{
		hMemDC[1] = CreateCompatibleDC(hMemDC[0]);
		oldBitmap[1] = (HBITMAP)SelectObject(hMemDC[1], hAnimImage);
		bx = bitAnim.bmWidth / 6;
		by = bitAnim.bmHeight / 8;

		int StartX = Anim_Frame_Cur * bx;
		int StartY = Anim_Frame_Flag * by;

		TransparentBlt(hMemDC[0], Pos.x, Pos.y, bx * 2, by * 2, hMemDC[1], StartX, StartY, bx, by, RGB(255, 0, 255));
		SelectObject(hMemDC[1], oldBitmap[1]);
		DeleteDC(hMemDC[1]);
	}

	BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC[0], 0, 0, SRCCOPY);
	SelectObject(hMemDC[0], oldBitmap[0]);
	//DeleteDC(hMemDC);
}

VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	UpdateFrame();
	InvalidateRgn(hWnd, NULL, FALSE);
}

VOID CALLBACK KeyStateProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	static bool moveX = false;
	static bool moveY = false;
	static int Speed = 5;

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		Anim_Frame_Flag = 1;
		Dir.x = -1;
		moveX = true;
		moveY = false;
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		Anim_Frame_Flag = 0;
		Dir.y = 1;
		moveX = false;
		moveY = true;
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		Anim_Frame_Flag = 2;
		Dir.x = 1;
		moveX = true;
		moveY = false;
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		Anim_Frame_Flag = 3;
		Dir.y = -1;
		moveX = false;
		moveY = true;
	}
	else
	{
		wsprintf(sKeyState, TEXT("%s"), TEXT(""));
		Anim_Frame_Cur = 0;
		moveX = false;
		moveY = false;
	}

	if (moveX) Pos.x = Pos.x + (Dir.x * Speed);
	if (moveY) Pos.y = Pos.y + (Dir.y * Speed);

	if (Pos.x > rectView.right || Pos.x < rectView.left) Pos.x = 0;
	if (Pos.y > rectView.bottom || Pos.y < rectView.top) Pos.y = 0;
}


void DrawRectText(HDC hdc)
{
	TCHAR strTest[] = TEXT("텍스트 출력");
	TextOut(hdc, 475, Pos.y - 25, strTest, _tcslen(strTest));
	TextOut(hdc, 100, 100, sKeyState, _tcslen(sKeyState));
}

void UpdateFrame()
{
	Anim_Frame_Cur++;

	if (Anim_Frame_Cur > Anim_Frame_Max)
		Anim_Frame_Cur = Anim_Frame_Min;
}