#include "stdafx.h"

#include <process.h>
#include <Windows.h>

int Value = 0;
int ValuePlusOne = 0;

int Cnt = 0; // Value > Value + 1
bool IsChecked = false;

// Need Check Proj. Properties
// C/C++ -> Code Generation -> Runtime Library
// Runtime Library -> Multy Thread

CRITICAL_SECTION cs;

DWORD WINAPI ThreadFunc1(LPVOID lpParam)
{
	while (1)
	{
		// Do Not Switch To Other
		EnterCriticalSection(&cs);
		Value = rand() % 1000;
		ValuePlusOne = Value + 1;
		LeaveCriticalSection(&cs);
	}
	return 0;
}

DWORD WINAPI ThreadFunc2(LPVOID lpParam)
{
	while (1)
	{
		EnterCriticalSection(&cs);
		if (Value > ValuePlusOne)
		{
			printf("%d\n", Cnt++);
		}
		LeaveCriticalSection(&cs);
	}
	return 0;
}

unsigned __stdcall ThreadFunc10(LPVOID lpParam)
{
	while (1)
	{
		// Do Not Switch To Other
		EnterCriticalSection(&cs);
		Value = rand() % 1000;
		ValuePlusOne = Value + 1;
		LeaveCriticalSection(&cs);
	}
	return 0;
}

unsigned __stdcall ThreadFunc11(LPVOID lpParam)
{
	while (1)
	{
		EnterCriticalSection(&cs);
		if (Value > ValuePlusOne)
		{
			printf("%d\n", Cnt++);
		}
		LeaveCriticalSection(&cs);
	}
	return 0;
}

int main()
{
	InitializeCriticalSection(&cs);

	DWORD dwThreadID1, dwThreadID2;
	HANDLE hThread[2];

	unsigned long ulStackSize = 0;
	dwThreadID1 = 0; dwThreadID2 = 0;
	hThread[0] = NULL; hThread[1] = NULL;

	// CREATE_SUSPENDED : Make & Wait
	//hThread[0] = CreateThread(NULL, ulStackSize, ThreadFunc1, NULL, CREATE_SUSPENDED, &dwThreadID1);
	//hThread[1] = CreateThread(NULL, ulStackSize, ThreadFunc2, NULL, CREATE_SUSPENDED, &dwThreadID2);

	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, 
				 (unsigned(__stdcall*)(void*)) ThreadFunc10,
				 NULL, 0, (unsigned*)&dwThreadID1);

	hThread[1] = (HANDLE)_beginthreadex(NULL, 0,
				 (unsigned(__stdcall*)(void*)) ThreadFunc11,
				 NULL, 0, (unsigned*)&dwThreadID2);

	if (hThread[0] == 0 || hThread[1] == 0)
	{
		exit(1);
	}

	ResumeThread(hThread[0]);
	ResumeThread(hThread[1]);

	// Do Not Terminate Program, Until Thread's Works End
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	DeleteCriticalSection(&cs);

    return 0;
}

