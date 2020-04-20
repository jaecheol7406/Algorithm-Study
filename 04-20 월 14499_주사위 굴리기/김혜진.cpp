/*
function call: main -> Input -> main

주의점
- 굴러가면 위아래 면 2개만 바뀌는 것이 아니라, 총 4개의 면이 바뀌게 된다
(굴러가는 모습을 상상해보기)

*/
#include <iostream>
using namespace std;

int N, M, x, y, K;
int map[30][30];
int cmd[1010];

int cube[7]; // 전개도대로 1:윗면 2:뒷면 3:오른쪽 4:왼쪽 5:앞면 6:바닥면
int dir[5][2] = { {0, 0},  {0, 1}, {0, -1}, {-1, 0}, {1, 0} }; // 주사위가 굴러갈 위치 계산

void Input() {
	scanf("%d %d %d %d %d\n", &N, &M, &x, &y, &K);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d ", &map[i][j]);
		}
	}

	for (int i = 0; i < K; i++) {
		scanf("%d ", &cmd[i]);
	}
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {

	Input();

	for (int k = 0; k < K; k++) {
		int tmpX = x + dir[cmd[k]][0];
		int tmpY = y + dir[cmd[k]][1];

		if (tmpX < 0 || tmpY < 0 || N <= tmpX || M <= tmpY) continue;

		x = tmpX;
		y = tmpY;
		int top = cube[1];

		if (cmd[k] == 1) { // 동쪽 (앞, 뒷면인 2,5 빼고 바뀐다)
			cube[1] = cube[4];
			cube[4] = cube[6];
			cube[6] = cube[3];
			cube[3] = top;
		}
		else if (cmd[k] == 2) { // 서쪽 (앞, 뒷면인 2,5 빼고 바뀐다)
			cube[1] = cube[3];
			cube[3] = cube[6];
			cube[6] = cube[4];
			cube[4] = top;
		}
		else if (cmd[k] == 3) { // 북쪽 (왼, 오른쪽인 3, 4빼고 바뀐다)
			cube[1] = cube[5];
			cube[5] = cube[6];
			cube[6] = cube[2];
			cube[2] = top;
		}
		else if (cmd[k] == 4) { // 남쪽 (왼, 오른쪽인 3, 4빼고 바뀐다)
			cube[1] = cube[2];
			cube[2] = cube[6];
			cube[6] = cube[5];
			cube[5] = top;
		}

		cout << cube[1] << endl;

		// 아랫면과 지도를 비교
		if (map[x][y] == 0) {
			map[x][y] = cube[6];
		}
		else {
			cube[6] = map[x][y];
			map[x][y] = 0;
		}
	}

	return 0;
}