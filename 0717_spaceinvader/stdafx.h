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

// TODO: reference additional headers your program requires here
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <istream>
#include <ostream>

using namespace std;

#include "SceneManager.h"

#define WIN_WIDTH 450
#define WIN_HEIGHT 800

#define ElapseTime 33