/*
function call: main -> Input -> main
1. 모든 점에서 출발해서 네 방향으로 제약없이 이동하며 숫자를 만든다
2. 만들어진 숫자는 exist 배열에 넣는다
3. 마지막에 exist 배열의 값이 1인 원소의 개수를 구한다
*/
#include <iostream>
#include <math.h>
using namespace std;

int exist[1000000];
int map[5][5];

void Input() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> map[i][j];
		}
	}
}

int picked[6];
int dir[4][2] = { {1, 0}, {-1, 0}, {0, -1}, {0, 1} };
void DFS(int r, int c, int cnt) {
	if (cnt >= 6) {
		int result = 0;
		for (int i = 0; i < 6; i++) {
			result += picked[i] * pow(10, (5 - i));
		}

		// cout << result << endl;
		exist[result] = 1;

		return;
	}

	int tmpR, tmpC;
	for (int i = 0; i < 4; i++) {
		tmpR = r + dir[i][0];
		tmpC = c + dir[i][1];

		if (tmpR < 0 || tmpC < 0 || 5 <= tmpR || 5 <= tmpC) continue;
		picked[cnt] = map[tmpR][tmpC];
		DFS(tmpR, tmpC, cnt + 1);
	}
}

int main() {

	Input();

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			DFS(i, j, 0);
		}
	}

	int answer = 0;
	for (int i = 0; i < 1000000; i++) {
		if (exist[i] == 1) answer++;
	}

	cout << answer;

	return 0;
}