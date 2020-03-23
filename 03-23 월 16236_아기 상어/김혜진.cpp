/*
함수 호출 순서: Input() -> BFS()

1. BFS로 "먹을 수 있고", "가장 가까우면서", "가장 위&왼쪽에 있는 물고기"를 골라낸다.
2. 그 물고기가 있는 곳까지 가서, 먹고, 크기를 키울 수 있으면 키운다.
3. 2에서 업데이트된 조건을 반영해 "먹을 수 있는 물고기가 없을 때까지" 1을 계속한다.

주의점 1: 특정 위치와의 거리를 단순 abs로 계산하면 안 된다.(나보다 큰 상어는 지나갈 수 없기 때문에)
주의점 2: n개 거리가 떨어진 BFS를 돌 때, 무조건 가장 먼저 도달한 곳으로 가면 안 된다.(같은 거리의 BFS일 때 큐에서 더 뒤에 위치한 애가 '더 위, 더 왼쪽' 일 수 있다
*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Pos {
	int r;
	int c;
};

/* 기본 Input */
int N;
Pos shark; // 상어의 위치
int eaten = 0; // 상어가 먹은 물고기 개수
int sharkSize = 2; // 상어 크기
int fish[25][25]; // 물고기의 위치 및 물고기 크기



/* BFS 관련 변수 */
queue<Pos> q; // BFS에서 먹을 수 있는 물고기를 발견한 가장 작은 cnt
int dir[4][2] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} }; // 이 순서는 아무것도 보장하지 않음

int visited[25][25]; // BFS의 visited
int distArr[25][25]; // BFS에서 몇 걸음 간 것인지 cnt 기록
int stdDist = 0; // BFS에서 stdDist 걸음만큼 간 위치들 중, 먹을 수 있는 물고기 목록 (이 중 가장 위, 가장 왼쪽인 물고기를 판별해야 함)
vector<Pos> cands;



// cands를 정렬하는 데 사용하는 함수
bool cpr(Pos a, Pos b) {
	if (a.r == b.r) return a.c < b.c;
	return a.r < b.r;
}

int seconds; // 총 걸린 시간 (물고기까지의 거리의 총합산)

void Input() {
	scanf("%d\n", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &fish[i][j]);
			if (fish[i][j] == 9) {
				fish[i][j] = 0;
				shark = Pos{ i, j };
			}
		}
	}
}


Pos BFS() {
	// Init
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited[i][j] = 0;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			distArr[i][j] = 0;
		}
	}
	while (!q.empty()) {
		q.pop();
	}
	stdDist = 0;

	q.push(shark);
	int thisR, thisC;
	int tmpR, tmpC;

	while (!q.empty()) {

		thisR = q.front().r; thisC = q.front().c;

		if (fish[thisR][thisC] > 0 && fish[thisR][thisC] < sharkSize) { // 먹을 수 있는 가장 가까운 물고기
			return Pos{ thisR, thisC };
		}
		q.pop();

		if (stdDist != 0 && distArr[thisR][thisC] >= stdDist) continue;

		for (int i = 0; i < 4; i++) {
			tmpR = thisR + dir[i][0];
			tmpC = thisC + dir[i][1];

			if (tmpR < 0 || tmpC < 0 || N <= tmpR || N <= tmpC) continue;
			if (visited[tmpR][tmpC] != 0) continue;

			if (fish[tmpR][tmpC] > sharkSize) continue;
			
			if (fish[tmpR][tmpC] > 0 && fish[tmpR][tmpC] < sharkSize) { // 먹을 수 있는 물고기
				distArr[tmpR][tmpC] = distArr[thisR][thisC] + 1;
				stdDist = distArr[tmpR][tmpC];
				cands.push_back(Pos{ tmpR, tmpC });
				// return Pos{ tmpR, tmpC }; 주의점 2 와 관련된 틀리게 하는 원인
			}
			else {
				visited[tmpR][tmpC] = 1;
				q.push(Pos{ tmpR, tmpC });
				distArr[tmpR][tmpC] = distArr[thisR][thisC] + 1;
			}
			
		}
	}

	if (cands.size() > 0) {
		sort(cands.begin(), cands.end(), cpr);

		
		return Pos{ cands[0].r, cands[0].c };
	}
	else {
		return Pos{ -1, -1 };
	}
}


int main() {

	Input();

	Pos nextPos = Pos{ 0, 0 };
	
	while (1) { // 먹을 수 있는 물고기를 찾는다.(BFS)

		nextPos = BFS();
		if (nextPos.r == -1 && nextPos.c == -1) {
			break;
		}

		seconds += distArr[nextPos.r][nextPos.c];
		cands.clear();

		fish[nextPos.r][nextPos.c] = 0;
		shark.r = nextPos.r;
		shark.c = nextPos.c;
		eaten++;
		if (eaten == sharkSize) {
			eaten = 0;
			sharkSize++;
		}
		
	}
	
	cout << seconds;

	return 0;
}