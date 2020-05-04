/*
function call: main -> Input -> (Init -> BFS) -> main

1. 상어의 위치에서 모든 점을 탐색해 BFS로 먹을 수 있는 물고기 후보를 구한다
   <시간절약>
   가장 짧은 거리인 애들은 모두 구해야 하고, 그 이상은 구할 필요 없다
   (예: BFS 하면서 길이 3인 애가 나왔으면 길이 3인 점은 모두 구하고 4 넘어가는 것부터는 x)
2. 물고기 후보들을 행과 열 오름차순으로 정렬한다. 그럼 0번째 후보가 조건에 부합하는 물고기다
3. 먹는다. 거리(=걸린 시간)을 더하고 map과 상어정보를 갱신한다
4. 물고기 후보가 0이 될때까지 반복한다
*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct Fish {
	int r;
	int c;
	int d = 0; // BFS에서 이동거리
};

int N;
int map[20][20];
Fish shark;
int sharkSize = 2;
int sharkEaten = 0;
queue<Fish> q;

int minSize;

vector<Fish> cands;

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				shark.r = i;
				shark.c = j;
			}
		}
	}
	
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

bool cmp(Fish a, Fish b) {
	if (a.d == b.d && a.r == b.r) {
		return a.c < b.c;
	}
	if (a.d == b.d) {
		return a.r < b.r;
	}
	return a.d < b.d;
}

int answer = 0;
int visited[20][20];
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
void BFS() {
	int tmpR, tmpC;

	while (!q.empty()) {
		Fish thisPos = q.front();
		q.pop();

		

		for (int i = 0; i < 4; i++) {
			tmpR = thisPos.r + dir[i][0];
			tmpC = thisPos.c + dir[i][1];

			if (tmpR < 0 || tmpC < 0 || N <= tmpR || N <= tmpC) continue;
			if (map[tmpR][tmpC] > sharkSize) continue;
			if (visited[tmpR][tmpC] == 1) continue;

			// 먹을 수 있는 가장 가까운 물고기를 찾음
			if (map[tmpR][tmpC] != 0 && map[tmpR][tmpC] < sharkSize) {
				cands.push_back(Fish{ tmpR, tmpC, thisPos.d + 1 });
				if (minSize > thisPos.d + 1) minSize = thisPos.d + 1;
			}

			// 시간 절약 (4ms -> 0ms)
			if (thisPos.d + 1 > minSize) continue; // 이미 후보가 나온게 있으면 그보다 큰 후보는 찾지 않는다

			visited[tmpR][tmpC] = 1;
			q.push(Fish{ tmpR, tmpC, thisPos.d + 1 });
		}
	}
}

void Init() {
	while (!q.empty()) {
		q.pop();
	}

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			visited[i][j] = 0;
		}
	}

	cands.clear();

	q.push(shark);
	visited[shark.r][shark.c] = 1;

	minSize = 9999; // 최대 400
}

int main() {

	Input();

	while (1) {
		// Print();
		Init();

		// 가장 거리 가깝고 먹을 수 있는 애 찾기
		BFS();

		if (cands.size() == 0) break;		

		// 먹을 상어 찾기
		sort(cands.begin(), cands.end(), cmp);
		Fish target = cands[0];

		// 먹기
		answer += target.d ;
		// cout << "+=" << target.d << endl;
		map[shark.r][shark.c] = 0;
		shark.r = target.r;
		shark.c = target.c;
		map[shark.r][shark.c] = 9;

		// 상어 정보 갱신
		sharkEaten++;
		if (sharkEaten == sharkSize) {
			sharkSize++;
			sharkEaten = 0;
		}
	}

	cout << answer;

	return 0;
}