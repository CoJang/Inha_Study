#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

#define NODE_NUM 8
#define INF 9999

/*
	1. 모든 꼭짓점을 미방문 상태로 표시한다. 미방문 집합이라는 모든 미방문 꼭짓점의 집합을 만든다.

	2.  모든 꼭짓점에 시험적 거리 값을 부여한다: 초기점을 0으로, 
		다른 모든 꼭짓점을 무한대로 설정한다. 초기점을 현재 위치로 설정한다.

	3.  현재 꼭짓점에서 미방문 인접 꼭짓점을 찾아 그 시험적 거리를 현재 꼭짓점에서 계산한다. 
		새로 계산한 시험적 거리를 현재 부여된 값과 비교해서 더 작은 값을 넣는다. 
		예를 들어, 현재 꼭짓점 A의 거리가 6이라고 표시되었고, 
		인접 꼭짓점 B로 연결되는 변의 길이가 2라고 한다면,
		A를 통한 B까지의 거리는 6 + 2 = 8이 된다. 
		이전의 B까지의 거리가 8보다 컸다면 8로 바꾸고,
		그렇지 않다면 그대로 놔둔다.

	4.  만약 현재 꼭짓점에 인접한 모든 미방문 꼭짓점까지의 거리를 계산했다면,
		현재 꼭짓점을 방문한 것으로 표시하고 미방문 집합에서 제거한다.
		방문한 꼭짓점은 이후에는 다시 방문하지 않는다.

	5. 두 꼭짓점 사이의 경로를 찾는 경우: 도착점이 방문한 상태로 표시되면 멈추고 알고리즘을 종료한다.
	6.  완전 순회 경로를 찾는 경우: 미방문 집합에 있는 꼭짓점들의 시험적 거리 중 최솟값이 무한대이면
		이는 출발점과 미방문 집합 사이에 연결이 없는 경우이므로 멈추고 알고리즘을 종료한다.
	7. 아니면 시험적 거리가 가장 작은 다음 미방문 꼭짓점을 새로운 "현재 위치"로 선택하고 3단계로 되돌아간다.

	출처 : wiki백과
*/

int Map[NODE_NUM][NODE_NUM] =
{
	{ 0, 2, INF, INF, INF, 3, INF, INF },
	{ 2, 0, 4, 1, INF, INF, INF, INF },
	{ INF, 4, 0, INF, 3, INF, INF, INF },
	{ INF, 1, INF, 0, 3, INF, 2, INF },
	{ INF, INF, 3, 3, 0, INF, INF, 4 },
	{ 3, INF, INF, INF, INF, 0, 6, INF },
	{ INF, INF, INF, 2, INF, 6, 0, 4 },
	{ INF, INF, INF, INF, 4, INF, 4, 0 }
};

int Dist[NODE_NUM];
bool Visited[NODE_NUM];
int ShortestNode[NODE_NUM];

// return Shortest Node's Index
int GetShortestNode()
{
	int MinDist, MinIndex;
	MinDist = INF;
	MinIndex = -1;

	for (int i = 0; i < NODE_NUM; i++)
	{
		// if Visited Node Skip
		if (Visited[i] == true) continue;
		// Find Shortest Node [Base On Current Node]
		if (Dist[i] < MinDist)
		{
			MinDist = Dist[i];
			MinIndex = i;
		}
	}

	return MinIndex;
}

void UpdateDistance(int Next)
{
	for (int i = 0; i < NODE_NUM; i++)
	{
		// if Visited Node Skip
		if (Visited[i] == true || Map[Next][i] == INF) continue;

		if (Dist[i] > Dist[Next] + Map[Next][i])
		{
			ShortestNode[i] = Next;
			Dist[i] = Dist[Next] + Map[Next][i];
		}
	}
}

int main()
{
	int Start = 1;
	int Goal = 5;

	cout << "시작 지점을 입력하시오.";
	cin >> Start;
	cout << "목표 지점을 입력하시오.";
	cin >> Goal;

	Start--; Goal--;

	for (int i = 0; i < NODE_NUM; i++)
	{
		// Initialize Distance Based on Start Node
		Dist[i] = Map[Start][i];
	}
	// 시작 지점을 기준으로 거리를 업데이트 했기 때문에
	// 방문 완료로 표시.
	Visited[Start] = true;

	printf("Visit Index : ");
	for (int i = 0; i < NODE_NUM - 1; i++)
	{
		int Next = GetShortestNode();

		printf("%d ", Next + 1);
		UpdateDistance(Next);
		Visited[Next] = true;
	}

	if (Dist[Goal] == INF)
	{
		cout << "Blocked!" << endl;
		return 0;
	}

	printf("\nDistance From Start : ");
	for (int i = 0; i < NODE_NUM; i++)
		printf("%d ", Dist[i]);

	printf("\nShortest Way : ");
	printf("%d ", Goal + 1);
	for (int i = Goal; i < NODE_NUM;)
	{
		printf("%d ", ShortestNode[i] + 1);
		i = ShortestNode[i];
		if (i <= 0) break;
	}

    return 0;
}

