/*
1. Ÿ���� �ڸ��� ��� ����� ���� ���ؼ�
2. ���� ���� ��� Ÿ���� ������ 'B'�� ���� 'W'�� �� �� ��쿡 ����
3. BFS�� ĥ�ؾ� �ϴ� Ÿ���� �� ������ ������

Function call: Input -> { �ݺ���: Init() -> BFS }
*/
#include <iostream>
#include <queue>
using namespace std;

struct Tile {
	int r;
	int c;
};

/* Input �޴� �� ����ϴ� ���� */
int N, M;
char map[55][55];

/* BFS�� ����ϴ� ���� */
queue<Tile> q;
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int visited[55][55];
int tmpR, tmpC;

/* ��ü �ý��ۿ��� ����� ĥ�ؾ� �ϴ� �� */
int minTarget = 2500;


void Input() {
	scanf("%d %d\n", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%s", &map[i]);
	}
}


void Init() {
	while (!q.empty()) {
		q.pop();
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visited[i][j] = 0;
		}
	}
}


int BFS(int r, int c) {
	int target = 0; // �̹� BFS���� ĥ�ؾ� �ϴ� Ÿ�� ������ �����ϴ� ����

	q.push(Tile{ r, c });
	char oddColor, evenColor;

	if ((r + c) % 2 == 0) { // �������� ¦����
		evenColor = map[r][c];
		if (evenColor == 'W') oddColor = 'B';
		else oddColor = 'W';
	}
	else { // �������� Ȧ����
		oddColor = map[r][c];
		if (oddColor == 'W') evenColor = 'B';
		else evenColor = 'W';
	}

	while (!q.empty()) {
		if (minTarget < target) return target; // ������ �ȵ� ������ �Ǹ�Ǹ� ���� ����

		Tile thisQ = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			
			tmpR = thisQ.r + dir[i][0];
			tmpC = thisQ.c + dir[i][1];
			
			if (tmpR < r || tmpC < c || r + 8  <= tmpR || c + 8 <= tmpC) continue; // ���� üũ�� �ٸ� BFS���� Ư���� ������
			
			if (visited[tmpR][tmpC] == 1) continue;

			if ((tmpR + tmpC) % 2 == 0 && map[tmpR][tmpC] != evenColor) { // �̹� ���� ¦���ε� ¦���� ����� ��ġ���� ������
				target++;
			}

			if ((tmpR + tmpC) % 2 == 1 && map[tmpR][tmpC] != oddColor) { // �̹� ���� Ȧ���ε� Ȧ���� ����� ��ġ���� ������
				target++;
			}

			visited[tmpR][tmpC] = 1;
			q.push(Tile{ tmpR, tmpC });

		}
	}

	return target;
}

int main() {

	Input();
	int tmpTarget; // �� BFS���� ���� ĥ�ؾ� �ϴ� Ÿ�� ����
	
	for (int startR = 0; N - 8 >= startR; startR++) { // �ڸ���
		for (int startC = 0; M - 8 >= startC; startC++) {

			// �Ϻη� �ٸ� ������ ����� ĥ�غ���
			if (map[startR][startC] == 'W') map[startR][startC] = 'B';
			else map[startR][startC] = 'W';

			Init();
			tmpTarget = BFS(startR, startC) + 1;
			if (minTarget > tmpTarget) minTarget = tmpTarget;


			// ���� ������ ������ �ٽ� ������
			if (map[startR][startC] == 'W') map[startR][startC] = 'B';
			else map[startR][startC] = 'W';

			Init();
			tmpTarget = BFS(startR, startC);
			if (minTarget > tmpTarget) minTarget = tmpTarget;
		}
	}

	if (minTarget == 2500) cout << 0;
	else cout << minTarget;

	return 0;
}