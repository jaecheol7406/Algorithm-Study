/*
주의점 1: 특정 위치와의 거리를 단순 abs로 계산하면 안 된다.(나보다 큰 상어는 지나갈 수 없기 때문에)
주의점 2: n개 거리가 떨어진 BFS를 돌 때, 무조건 가장 먼저 도달한 곳으로 가면 안 된다.(같은 거리의 BFS일 때 큐에서 더 뒤에 위치한 애가 '더 위, 더 왼쪽' 일 수 있다
*/
#include <iostream>
#include <queue>

using namespace std;

struct Pos {
	int r;
	int c;
};


int N;
Pos shark; // 상어의 위치
int eaten = 0; // 상어가 먹은 물고기 개수
int sharkSize = 2; // 상어 크기
int dist = 0;

int fish[25][25]; // 물고기의 위치 및 물고기 크기
int visited[25][25];
int distArr[25][25];

int seconds;

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

void Print() {
	cout << shark.r << "," << shark.c << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", fish[i][j]);
		}
		cout << endl;
	}
}
queue<Pos> q;

int dir[4][2] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} };
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
	dist = 0;

	q.push(shark);
	// visited[shark.r][shark.c] = 1;
	// cout << "현재 상어 위치: " << shark.r << "," << shark.c << endl;
	int thisR, thisC;
	int tmpR, tmpC;

	while (!q.empty()) {

		thisR = q.front().r; thisC = q.front().c;
		// cout << "이번 큐: " << thisR << "," << thisC << endl;
		if (fish[thisR][thisC] > 0 && fish[thisR][thisC] < sharkSize) { // 먹을 수 있는 가장 가까운 물고기
			return Pos{ thisR, thisC };
		}
		q.pop();

		for (int i = 0; i < 4; i++) {
			tmpR = thisR + dir[i][0];
			tmpC = thisC + dir[i][1];

			if (tmpR < 0 || tmpC < 0 || N <= tmpR || N <= tmpC) continue;
			if (visited[tmpR][tmpC] != 0) continue;
			// cout << tmpR << "," << tmpC << "(사이즈" << fish[tmpR][tmpC] << ") <? " << sharkSize << endl;
			if (fish[tmpR][tmpC] > sharkSize) continue;
			
			if (fish[tmpR][tmpC] > 0 && fish[tmpR][tmpC] < sharkSize) { // 먹을 수 있는 가장 가까운 물고기
				distArr[tmpR][tmpC] = distArr[thisR][thisC] + 1;
				return Pos{ tmpR, tmpC };
			}
			visited[tmpR][tmpC] = 1;
			q.push(Pos{ tmpR, tmpC });
			distArr[tmpR][tmpC] = distArr[thisR][thisC] + 1;
			// cout << "distArr[tmpR][tmpC]= " << distArr[thisR][thisC] + 1 << endl;
			
		}
	}
	return Pos{ -1, -1 };
}

int main() {

	Input();

	Pos nextPos = Pos{ 0, 0 };
	// 먹을 수 있는 물고기를 찾는다.(BFS)
	while (1) {
		

		nextPos = BFS();
		if (nextPos.r == -1 && nextPos.c == -1) {
			break;
		}

		// cout << "****먹는다: " << nextPos.r << "," << nextPos.c << " 이동거리: " << distArr[nextPos.r][nextPos.c] << endl;
		seconds += distArr[nextPos.r][nextPos.c];

		fish[nextPos.r][nextPos.c] = 0;
		shark.r = nextPos.r;
		shark.c = nextPos.c;
		eaten++;
		if (eaten == sharkSize) {
			eaten = 0;
			sharkSize++;
		}
		
		// cout << "크기: " << sharkSize << " 먹은 개수: " << eaten << endl;
	}
	
	cout << seconds;

	return 0;
}