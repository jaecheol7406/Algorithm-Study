/*
전개도 방향 바뀌는 것을 고려하지 않은 코드
function call: main -> Input -> main

이동방향별로 윗면을 계속 기록
*/
#include <iostream>
using namespace std;

int N, M, x, y, K;
int tmpX, tmpY;
int map[30][30];
int cmd[1010];

int topNum = 1; // 주사위의 윗면
int topToBtm[7] = { 0, 6, 5, 4, 3, 2, 1 }; // 윗면이 i 일 때 바닥
// 특정 방향으로 구른 뒤 윗면
int topAfterRoll[7][5] = { {0, 0, 0, 0, 0},  {0, 4, 3, 5, 2}, {0, 4, 3, 1, 6}, {0, 1, 6, 5, 2}, {0, 6, 1, 5, 2}, {0, 4, 3, 6, 1}, {0, 4, 3, 2, 5} };
int dir[5][2] = { {0, 0},  {0, 1}, {0, -1}, {-1, 0}, {1, 0} }; // 주사위가 굴러갈 위치 계산
int cube[7]; // 주사위 각 번호에 써져 있는 숫자

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

	for (int time = 0; time < K; time++) {
		cout << "time: " << time << "==============" << endl;
		tmpX = x + dir[cmd[time]][0];
		tmpY = y + dir[cmd[time]][1];

		if (tmpX < 0 || tmpY < 0 || N <= tmpX || M <= tmpY) continue;

		x = tmpX;
		y = tmpY;
		cout << "현재 주사위 위치: " << x << ", " << y << endl;

		topNum = topAfterRoll[topNum][cmd[time]]; // 윗면 갱신
		cout << "현재 윗면: " << topNum << endl;
		if (map[x][y] == 0) { // 주사위 -> 지도로 복사
			map[x][y] = cube[topToBtm[topNum]];
			cout << "map[" << x << "][" << y << "] = " << "cube[" << topToBtm[topNum] << "]" << endl;
		}
		else { // 지도 -> 주사위로 복사
			cube[topToBtm[topNum]] = map[x][y];
			map[x][y] = 0;
			cout << "cube[" << topToBtm[topNum] << "] = " << "map[" << x << "][" << y << "]" << endl;
		}

		cout << cube[topNum] << endl;
		Print();

	}

	return 0;
}