/*
function call: main -> Input -> main
1. ��� ������ ����ؼ� �� �������� ������� �̵��ϸ� ���ڸ� �����
2. ������� ���ڴ� exist �迭�� �ִ´�
3. �������� exist �迭�� ���� 1�� ������ ������ ���Ѵ�
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