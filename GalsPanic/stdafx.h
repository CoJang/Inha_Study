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

#define WIN_WIDTH 450
#define WIN_HEIGHT 800

#define ElapseTime 33

#define TILESIZE 10

#define FILL RGB(0, 0, 0)
#define TEMPFILL RGB(0, 255, 255)
#define NOTFILL RGB(255, 255, 255)