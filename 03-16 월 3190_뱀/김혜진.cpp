/*
map �迭: �� �� 0, ��� 1, ���� ������ �� 2
snake ť: front�� ����, back�� �Ӹ�. �Ӹ��� �ø� �ܿ� ť�� ���� �ڿ� push

�̿� ���� ���� �����ϸ�, ���� ���ǿ� �ɸ� ������ ��� �̵��Ѵ�.
*/
#include <iostream>
#include <queue>

using namespace std;

int N, K, L;
int map[105][105]; // ����� 1, ���� 2, �� ���� 0

int turnExist[10005]; // index: ������ȯ�ؾ� �ϴ� �ð�, value: 1�̸� ���ƾ� ��, 0�̸� �ƴ�
char turn[10005]; // index: ������ȯ�ؾ� �ϴ� �ð�, value: ����

struct Snake {
	int r;
	int c;
};
queue<Snake> snake; // ���� ��ġ�� ��� ť. ���� ���� ����, ���� �ڰ� �Ӹ�

void Input() {
	scanf("%d\n%d\n", &N, &K);

	int r, c;
	for (int i = 0; i < K; i++) {
		scanf("%d %d\n", &r, &c);
		map[r - 1][c - 1] = 1;
	}

	scanf("%d\n", &L);

	int t;
	char p;
	for (int i = 0; i < L; i++) {
		scanf("%d %c\n", &t, &p);
		turnExist[t] = 1;
		turn[t] = p;
	}
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", map[i][j]);
		}
		cout << endl;
	}

	/*for (int i = 0; i < 10005; i++) {
		if(turnExist[i] == 1) printf("%c ", turn[i]);
	}*/
}

int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
int nowDir = 0; // ���� ���� �ٶ󺸰� �ִ� ����

int answer = 0;
int main() {
	Input();

	// ���� ���� ��ġ
	snake.push(Snake{ 0, 0 });
	map[0][0] = 2;
	int newR, newC;
	Snake tail;
	//Print();

	while (1) {
		answer++;

		// �̵�
		newR = snake.back().r + dir[nowDir][0];
		newC = snake.back().c + dir[nowDir][1];

		// ���� ���� �˻�
		if (newR < 0 || newC < 0 || N <= newR || N <= newC) break; // ������ �����
		if (map[newR][newC] == 2) break; // �ڽ��� ���� �ε�����

		// �����̸� �÷� �Ӹ� ��ġ�� �ٲ۴� (�Ӹ���ġ = ť�� �ǳ�)
		snake.push(Snake{ newR, newC });

		// ����� �ִ��� �˻�
		if (map[newR][newC] != 1) { // ����� ������ ������ ���δ�
			tail = Snake{ snake.front().r, snake.front().c };
			map[tail.r][tail.c] = 0;
			snake.pop();
		}
		map[newR][newC] = 2; // �Ӹ� ��ġ�� ǥ���ϴ� ���ÿ� ���� ����� ���ְ� �ȴ�

		// ���� ��ȯ
		if (turnExist[answer] == 1) {
			if (turn[answer] == 'D') { // ���������� 90�� ȸ��
				nowDir = (nowDir + 1) % 4;
			}
			else {
				nowDir = (nowDir + 3) % 4;
			}
		}

		//cout << answer << "�� ��=============" << endl;
		//Print();
	}
	cout << answer;

	return 0;
}