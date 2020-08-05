========================================================================
    WIN32 APPLICATION : GalsPanic Project Overview
========================================================================

string str = "콘솔창에 쓰고 싶은 문자열";
DWORD dwWrite;
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
WriteFile(hOut, str.c_str(), str.size(), &dwWrite, NULL);

문제점
[0]. 점이 내부에 있는지 판단
		-> 하려면 다각형의 점 또는 변의 정보가 필요

[1]. Flood Fill 기반 색칠 시 
	 이미 칠해진 곳을 넘지 않고 칠하는 알고리즘 필요
	 -> 현재 알고리즘으로는 무한 루프 수준의 연산필요