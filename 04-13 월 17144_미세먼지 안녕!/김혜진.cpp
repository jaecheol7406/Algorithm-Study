/*
function call: main -> Input -> ( Spread <-> Clarify ) -> main

���ǻ���
1. �̼����� Ȯ���� '��� ĭ���� ����'�� �Ͼ�Ƿ�,
   1) ���� �� ĭ���� �� �� ĭ���� Ȯ��Ǵ��� ����� ��,
   2) �ڽ��� ���� �̼����� ���� ������Ʈ �� ��
   3) �ٸ� ĭ���� �̵��� �� �̼������� ���� map�迭�� �� ���� ������Ʈ�Ѵ�. (queue�� added �迭 ���)
���� 1 -> 3 - > 2 �� ������ ����ϰų� �̼����� Ȯ�꿡 ĭ���� ������ �� ���, Ʋ�� ���̴�.

2. ���� �̼������� ���� ���� ��, ����û����(-1)�� �����Ѵ�.
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
	// �ڱ� ���̱�
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

	// �ٸ� �ֿ��� �޾ƿ���
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			map[i][j] += added[i][j];
		}
	}
}

void Clarify() {
	// ����û���� ����
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

	// ����û���� �Ʒ���
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

		// 0. �ʱ�ȭ
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				added[i][j] = 0;
			}
		}

		// 1. �̼����� Ȯ��
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if(map[i][j] != 0 && map[i][j] != -1)
					q.push(Pos{ i, j });
			}
		}
		Spread();
		// Print();

		// 2. ����û���� �۵�
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