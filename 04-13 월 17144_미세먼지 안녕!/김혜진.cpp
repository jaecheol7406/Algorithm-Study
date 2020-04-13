/*
function call: main -> Input -> ( Spread <-> Clarify ) -> main

주의사항
1. 미세먼지 확산이 '모든 칸에서 동시'에 일어나므로,
   1) 먼저 각 칸에서 몇 개 칸으로 확산되는지 계산한 후,
   2) 자신의 남은 미세먼지 양을 업데이트 한 후
   3) 다른 칸에서 이동해 온 미세먼지를 더해 map배열을 한 번에 업데이트한다. (queue와 added 배열 사용)
만약 1 -> 3 - > 2 번 순서로 계산하거나 미세먼지 확산에 칸별로 순서를 줄 경우, 틀릴 것이다.

2. 남은 미세먼지의 양을 더할 때, 공기청정기(-1)는 제외한다.
*/
#include <iostream>
#include <queue>
using namespace std;

struct Pos {
	int r;
	int c;
};
queue<Pos> q;

int R, C;
int map[60][60];
int added[60][60];
int T;
int Top = -1;
int Bottom;

void Input() {
	scanf("%d %d %d\n", &R, &C, &T);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			scanf("%d ", &map[i][j]);
			if (map[i][j] == -1) {
				if (Top == -1) {
					Top = i;
				}
				else {
					Bottom = i;
				}
			}
		}
	}
}

void Print() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int dir[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
void Spread() {
	int tmpR, tmpC;
	int cnt = 0;
	int r, c;
	// 자기 줄이기
	while (!q.empty()) {
		cnt = 0;
		r = q.front().r;
		c = q.front().c;
		q.pop();

		for (int i = 0; i < 4; i++) {
			tmpR = r + dir[i][0];
			tmpC = c + dir[i][1];

			if (map[tmpR][tmpC] == -1) continue;
			if (tmpR < 0 || tmpC < 0 || R <= tmpR || C <= tmpC) continue;
			cnt++;

			added[tmpR][tmpC] += map[r][c] / 5;
		}
		map[r][c] -= (map[r][c] / 5) * cnt;
	}

	// 다른 애에서 받아오기
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			map[i][j] += added[i][j];
		}
	}
}

void Clarify() {
	// 공기청정기 위쪽
	map[Top-1][0] = 0;
	for (int i = Top - 2; i >= 0; i--) {
		map[i+1][0] = map[i][0];
	}

	for (int j = 0; j < C - 1; j++) {
		map[0][j] = map[0][j + 1];
	}

	for (int i = 0; i < Top; i++) {
		map[i][C - 1] = map[i + 1][C - 1];
	}

	for (int j = C - 1; j >= 2; j--) {
		map[Top][j] = map[Top][j - 1];
	}
	map[Top][1] = 0;

	// 공기청정기 아래쪽
	map[Bottom + 1][0] = 0;
	for (int i = Bottom + 1; i < R - 1; i++) {
		map[i][0] = map[i + 1][0];
	}

	for (int j = 0; j < C - 1; j++) {
		map[R - 1][j] = map[R - 1][j + 1];
	}

	for (int i = R - 1; i >= Bottom; i--) {
		map[i][C - 1] = map[i - 1][C - 1];
	}

	for (int j = C - 1; j >= 2; j--) {
		map[Bottom][j] = map[Bottom][j - 1];
	}
	map[Bottom][1] = 0;
}

int main() {

	Input();
	// Print();

	while (T != 0) {

		// 0. 초기화
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				added[i][j] = 0;
			}
		}

		// 1. 미세먼지 확산
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if(map[i][j] != 0 && map[i][j] != -1)
					q.push(Pos{ i, j });
			}
		}
		Spread();
		// Print();

		// 2. 공기청정기 작동
		Clarify();
		// Print();

		T--;
	}

	// Print();

	int answer = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (map[i][j] == -1) continue;
			answer += map[i][j];
		}
	}
	cout << answer;

	return 0;
}