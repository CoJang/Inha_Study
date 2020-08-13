// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

using namespace std;

#include <vector>
#include <string>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "msimg32.lib")

// TODO: reference additional headers your program requires here
#define WIN_WIDTH 800
#define WIN_HEIGHT 950