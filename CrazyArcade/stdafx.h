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


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <istream>
#include <ostream>

using namespace std;

// TODO: reference additional headers your program requires here
#include "Singleton.h"
#include "MyMath.h"

#pragma comment(lib, "msimg32.lib")
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#define FILTER RGB(255, 0, 255)

#define WIN_WIDTH 1056
#define WIN_HEIGHT 839
#define MAP_WIDTH 15
#define MAP_HEIGHT 13

#define ElapseTime 17

#define MAP singleton->GetCollisionManager()->GetMap()
#define BLOCKS singleton->GetCollisionManager()->GetMap()->GetBlocks()
#define PLAYER singleton->GetCollisionManager()->GetPlayer()
#define BLOCK_VECTOR singleton->GetCollisionManager()->GetBlocks()
#define OBSTACLE_VECTOR singleton->GetCollisionManager()->GetObstacles()
#define ITEM_VECTOR singleton->GetCollisionManager()->GetItems()
