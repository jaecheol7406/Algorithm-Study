/*
function call: main -> Input -> (DFS -> Simulate -> BFS) -> main

1. DFS로 궁수를 배치한다
2. BFS로 거리가 가장 가까워서 쏠 수 있는 적들을 궁수별로 구해둔다
3. 모든 궁수가 동시에 공격하므로 공격 횟수가 아닌 죽은 적 갯수를 센다
4. 공격 이후에는 적들은 한 칸씩 아래로 간다
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Pos {
	int r;
	int c;
	int d = 0; // BFS에서 사용될 cnt
};

vector<Pos> myList; // 궁수 정보
queue<Pos> q;

int N, M, D;
int map[15][15];
int backup[15][15];
int visited[15][15]; // BFS에서 사용
int myR; // 궁수의 행 위치

int tmpAnswer;
int answer;

void Input() {
	cin >> N >> M >> D;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			backup[i][j] = map[i][j];
		}
	}
	myR = N;
}

bool Close() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 1) return false;
		}
	}

	return true;
}
vector<Pos> cands;
int candSize = -1;

void Init() { // 궁수가 바뀔 때마다 Init
	while (!q.empty()) {
		q.pop();
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visited[i][j] = 0;
		}
	}

	candSize = -1;
	cands.clear();
}

bool cmp(Pos a, Pos b) {
	if (a.d == b.d) {
		return a.c < b.c; // 그러한 적이 여럿일 경우에는 가장 왼쪽에 있는 적을 공격한다
	}
	return a.d < b.d;
}

int dir[3][2] = { {-1, 0}, {0, 1}, {0, -1} };
void BFS() {
	int tmpR, tmpC;
	while (!q.empty()) {
		Pos thisPos = q.front();
		q.pop();

		if (thisPos.d + 1 > D) continue;
		if (candSize != -1 && thisPos.d + 1 > candSize) continue; // 거리가 최소가 아닌 애들은 보지 않는다 (>= 가 아니라 > 여야함: 31%에서 틀린 이유)

		for (int i = 0; i < 3; i++) {
			tmpR = thisPos.r + dir[i][0];
			tmpC = thisPos.c + dir[i][1];

			if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) continue;
			if (visited[tmpR][tmpC] == 1) continue;
			if (candSize != -1 && thisPos.d + 1 > candSize) continue;

			if (map[tmpR][tmpC] == 1) { // 적을 찾음
				candSize = thisPos.d + 1;
				cands.push_back(Pos{ tmpR, tmpC, thisPos.d + 1 });
				continue;
			}

			visited[tmpR][tmpC] = 1;
			q.push(Pos{ tmpR, tmpC, thisPos.d + 1 });
		}
	}
}

void Simulate() {
	vector<Pos> dead;

	while (1) {
		// 종료조건: 적이 없다
		if (Close()) {
			break;
		}

		dead.clear();

		// 모든 궁수가 각자 죽이려는 대상을 찾는다
		for (int t = 0; t < myList.size(); t++) {
			Pos me = myList[t];
			Init();
			q.push(me);

			BFS();

			if (cands.size() == 0) continue; // 죽일 수 있는 애가 없으면 pass
			sort(cands.begin(), cands.end(), cmp);
			/*cout << "후보들: ";
			for (int i = 0; i < cands.size(); i++) {
				cout << cands[i].r << "," << cands[i].c << "  ";
			}
			cout << endl;
			cout << "=> 죽일 열: " << cands[0].c << endl;*/
			dead.push_back(Pos{ cands[0].r, cands[0].c, cands[0].d });
		}

		// 모든 궁수는 동시에 공격한다.
		for (int i = 0; i < dead.size(); i++) {
			Pos enemy = dead[i];
			if (map[enemy.r][enemy.c] == 1) { // 같은 적이 여러 궁수에게 공격당할 수 있다.
				map[enemy.r][enemy.c] = 0;
				tmpAnswer++;
			}
		}

		// 적이 한 칸씩 아래로 이동한다
		for (int i = N - 1; i >= 0; i--) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] == 1) {
					if (i == N - 1) map[i][j] = 0;
					else {
						map[i + 1][j] = map[i][j];
						map[i][j] = 0;
					}
				}
			}
		}

		/*for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cout << map[i][j];
			}
			cout << endl;
		}*/

	}
	// cout << tmpAnswer << endl;
	if (tmpAnswer > answer) answer = tmpAnswer;
}

void DFS(int cnt, int pre) {
	if (cnt >= 3) { // 궁수 다 뽑음
		// cout << "궁수:" << myList[0].c << ", " << myList[1].c << ", " << myList[2].c << "===========" << endl;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				map[i][j] = backup[i][j];
			}
		}

		tmpAnswer = 0;
		Simulate();

		return;
	}

	for (int j = pre; j < M; j++) {

		myList.push_back(Pos{ myR, j });

		DFS(cnt + 1, j + 1);

		myList.pop_back();
	}
}

int main() {
	Input();

	DFS(0, 0);

	cout << answer;

	return 0;
}