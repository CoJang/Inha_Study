========================================================================
    WIN32 APPLICATION : Astar Project Overview
========================================================================

Tile 구성요소 : g value, f value, h value, Position

h value : 도착지로 부터 직선 거리
g value : 출발지로 부터 직선 거리(합)
f value : g와 h의 합

f 값이 중복되는 경우, g 값이 작은 것을 우선 시 할 것

================== 의사 코드 ====================

시작
open에 시작노드 push
if(open이 비어있는 가) then 길찾기 실패
else
{
	open에서 노드를 pop
	if(현재노드가 Goal인가) then
	{
		노드의 내용을 거꾸로 출력, 종료
	}

	현재 노드의 주변 노드를 탐색하여 새로운 노드 생성(갈 수 없는 곳 제외)
	새로운 노드의 F = g(x) + h(x)를 계산
	if(새로운 노드가 open이나 closed에 있는 가) 
	&& (새로운 노드의 F값이 현재 노드의 F값보다 큰 가) then continue
	else
	{
		새로운 노드가 open에 있으면 갱신
		closed에 있으면 closed에서 빼서 open에 넣고 갱신
		어느쪽에도 없으면 opne에 넣는다
	}
	Node를 closed로 push
}

========================================