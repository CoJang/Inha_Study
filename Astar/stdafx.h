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

#include <vector>
#include <string>
#include <iostream>

using namespace std;
// TODO: reference additional headers your program requires here
#define WIN_WIDTH 800
#define WIN_HEIGHT 800

#define TILE_SIZE 40

inline bool operator==(POINT &p1, POINT &p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}