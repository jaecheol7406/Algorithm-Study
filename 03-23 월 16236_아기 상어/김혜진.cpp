/*
������ 1: Ư�� ��ġ���� �Ÿ��� �ܼ� abs�� ����ϸ� �� �ȴ�.(������ ū ���� ������ �� ���� ������)
������ 2: n�� �Ÿ��� ������ BFS�� �� ��, ������ ���� ���� ������ ������ ���� �� �ȴ�.(���� �Ÿ��� BFS�� �� ť���� �� �ڿ� ��ġ�� �ְ� '�� ��, �� ����' �� �� �ִ�
*/
#include <iostream>
#include <queue>

using namespace std;

struct Pos {
	int r;
	int c;
};


int N;
Pos shark; // ����� ��ġ
int eaten = 0; // �� ���� ����� ����
int sharkSize = 2; // ��� ũ��
int dist = 0;

int fish[25][25]; // ������� ��ġ �� ����� ũ��
int visited[25][25];
int distArr[25][25];

int seconds;

void Input() {
	scanf("%d\n", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &fish[i][j]);
			if (fish[i][j] == 9) {
				fish[i][j] = 0;
				shark = Pos{ i, j };
			}
		}
	}
}

void Print() {
	cout << shark.r << "," << shark.c << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", fish[i][j]);
		}
		cout << endl;
	}
}
queue<Pos> q;

int dir[4][2] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} };
Pos BFS() {
	// Init
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited[i][j] = 0;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			distArr[i][j] = 0;
		}
	}
	while (!q.empty()) {
		q.pop();
	}
	dist = 0;

	q.push(shark);
	// visited[shark.r][shark.c] = 1;
	// cout << "���� ��� ��ġ: " << shark.r << "," << shark.c << endl;
	int thisR, thisC;
	int tmpR, tmpC;

	while (!q.empty()) {

		thisR = q.front().r; thisC = q.front().c;
		// cout << "�̹� ť: " << thisR << "," << thisC << endl;
		if (fish[thisR][thisC] > 0 && fish[thisR][thisC] < sharkSize) { // ���� �� �ִ� ���� ����� �����
			return Pos{ thisR, thisC };
		}
		q.pop();

		for (int i = 0; i < 4; i++) {
			tmpR = thisR + dir[i][0];
			tmpC = thisC + dir[i][1];

			if (tmpR < 0 || tmpC < 0 || N <= tmpR || N <= tmpC) continue;
			if (visited[tmpR][tmpC] != 0) continue;
			// cout << tmpR << "," << tmpC << "(������" << fish[tmpR][tmpC] << ") <? " << sharkSize << endl;
			if (fish[tmpR][tmpC] > sharkSize) continue;
			
			if (fish[tmpR][tmpC] > 0 && fish[tmpR][tmpC] < sharkSize) { // ���� �� �ִ� ���� ����� �����
				distArr[tmpR][tmpC] = distArr[thisR][thisC] + 1;
				return Pos{ tmpR, tmpC };
			}
			visited[tmpR][tmpC] = 1;
			q.push(Pos{ tmpR, tmpC });
			distArr[tmpR][tmpC] = distArr[thisR][thisC] + 1;
			// cout << "distArr[tmpR][tmpC]= " << distArr[thisR][thisC] + 1 << endl;
			
		}
	}
	return Pos{ -1, -1 };
}

int main() {

	Input();

	Pos nextPos = Pos{ 0, 0 };
	// ���� �� �ִ� ����⸦ ã�´�.(BFS)
	while (1) {
		

		nextPos = BFS();
		if (nextPos.r == -1 && nextPos.c == -1) {
			break;
		}

		// cout << "****�Դ´�: " << nextPos.r << "," << nextPos.c << " �̵��Ÿ�: " << distArr[nextPos.r][nextPos.c] << endl;
		seconds += distArr[nextPos.r][nextPos.c];

		fish[nextPos.r][nextPos.c] = 0;
		shark.r = nextPos.r;
		shark.c = nextPos.c;
		eaten++;
		if (eaten == sharkSize) {
			eaten = 0;
			sharkSize++;
		}
		
		// cout << "ũ��: " << sharkSize << " ���� ����: " << eaten << endl;
	}
	
	cout << seconds;

	return 0;
}