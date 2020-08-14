#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

#define NODE_NUM 8
#define INF 9999

/*
	1. ��� �������� �̹湮 ���·� ǥ���Ѵ�. �̹湮 �����̶�� ��� �̹湮 �������� ������ �����.

	2.  ��� �������� ������ �Ÿ� ���� �ο��Ѵ�: �ʱ����� 0����, 
		�ٸ� ��� �������� ���Ѵ�� �����Ѵ�. �ʱ����� ���� ��ġ�� �����Ѵ�.

	3.  ���� ���������� �̹湮 ���� �������� ã�� �� ������ �Ÿ��� ���� ���������� ����Ѵ�. 
		���� ����� ������ �Ÿ��� ���� �ο��� ���� ���ؼ� �� ���� ���� �ִ´�. 
		���� ���, ���� ������ A�� �Ÿ��� 6�̶�� ǥ�õǾ���, 
		���� ������ B�� ����Ǵ� ���� ���̰� 2��� �Ѵٸ�,
		A�� ���� B������ �Ÿ��� 6 + 2 = 8�� �ȴ�. 
		������ B������ �Ÿ��� 8���� �Ǵٸ� 8�� �ٲٰ�,
		�׷��� �ʴٸ� �״�� ���д�.

	4.  ���� ���� �������� ������ ��� �̹湮 ������������ �Ÿ��� ����ߴٸ�,
		���� �������� �湮�� ������ ǥ���ϰ� �̹湮 ���տ��� �����Ѵ�.
		�湮�� �������� ���Ŀ��� �ٽ� �湮���� �ʴ´�.

	5. �� ������ ������ ��θ� ã�� ���: �������� �湮�� ���·� ǥ�õǸ� ���߰� �˰����� �����Ѵ�.
	6.  ���� ��ȸ ��θ� ã�� ���: �̹湮 ���տ� �ִ� ���������� ������ �Ÿ� �� �ּڰ��� ���Ѵ��̸�
		�̴� ������� �̹湮 ���� ���̿� ������ ���� ����̹Ƿ� ���߰� �˰����� �����Ѵ�.
	7. �ƴϸ� ������ �Ÿ��� ���� ���� ���� �̹湮 �������� ���ο� "���� ��ġ"�� �����ϰ� 3�ܰ�� �ǵ��ư���.

	��ó : wiki���
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

	cout << "���� ������ �Է��Ͻÿ�.";
	cin >> Start;
	cout << "��ǥ ������ �Է��Ͻÿ�.";
	cin >> Goal;

	Start--; Goal--;

	for (int i = 0; i < NODE_NUM; i++)
	{
		// Initialize Distance Based on Start Node
		Dist[i] = Map[Start][i];
	}
	// ���� ������ �������� �Ÿ��� ������Ʈ �߱� ������
	// �湮 �Ϸ�� ǥ��.
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

