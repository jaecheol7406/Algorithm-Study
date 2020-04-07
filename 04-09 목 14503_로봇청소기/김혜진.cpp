/*
function call: main -> Input -> (Search <-> main) -> main

���� ���Ǵ�� ����
�κ��� ���� ��ȯ�� ������ �ƴ϶� �迭�� ����� ������
int dir[i][j] <- �κ��� ������ i �� �� �̵��� ����
int turn[i][j] <- �κ��� ������ ���� i�� �� ���ʷ� Ž���� ����
int oppDir[i] = { 2, 3, 0, 1 }; <- �κ��� ������ i�� �� ������ ����
*/
#include <iostream>
using namespace std;

struct Pos {
	int r;
	int c;
	int d;
};
Pos robot;

int N, M;
int map[60][60];

void Input() {
	scanf("%d %d\n", &N, &M);

	int a, b, c;
	scanf("%d %d %d\n", &a, &b, &c);
	robot = Pos{ a, b, c };

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
}

int answer = 0;
int dir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} }; // ��, ��, ��, �� ����
int turn[4][4] = { { 3, 2, 1, 0}, {0, 3, 2, 1}, {1, 0, 3, 2}, {2, 1, 0, 3} }; // �κ��� Ž���� ����
int oppDir[4] = { 2, 3, 0, 1 };
int tmpDir, tmpR, tmpC;

int Search() {
	for (int i = 0; i < 4; i++) { // �� ���� Ž��
		tmpDir = turn[robot.d][i]; // Ž���� ����
		tmpR = robot.r + dir[tmpDir][0];
		tmpC = robot.c + dir[tmpDir][1];

		if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) continue;
		if (map[tmpR][tmpC] == 0) { // �� �� �ִ� ���� ã��
			robot.d = tmpDir;
			robot.r = tmpR;
			robot.c = tmpC;
			return 0;
		}
	}

	// �� ���� �� �� ���� �ڷ� �� �� �ִ��� Ž��
	tmpDir = oppDir[robot.d];
	tmpR = robot.r + dir[tmpDir][0];
	tmpC = robot.c + dir[tmpDir][1];

	if (map[tmpR][tmpC] == 1) {
		return -1;
	}
	else {
		robot.r = tmpR;
		robot.c = tmpC;
		return 0;
	}
}

int main() {

	Input();
	
	int tmp;
	while (1) {
		if (map[robot.r][robot.c] == 0) { // ���� �ִ� ���� �� ĭ�̸� û��
			map[robot.r][robot.c] = 2; 
			answer++;
		}

		tmp = Search();
		if (tmp == -1) {
			break;
		}
		
	}

	cout << answer << endl;

	return 0;
}