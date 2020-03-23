/*
�Լ� ȣ�� ����: Input() -> BFS()

1. BFS�� "���� �� �ְ�", "���� �����鼭", "���� ��&���ʿ� �ִ� �����"�� ��󳽴�.
2. �� ����Ⱑ �ִ� ������ ����, �԰�, ũ�⸦ Ű�� �� ������ Ű���.
3. 2���� ������Ʈ�� ������ �ݿ��� "���� �� �ִ� ����Ⱑ ���� ������" 1�� ����Ѵ�.

������ 1: Ư�� ��ġ���� �Ÿ��� �ܼ� abs�� ����ϸ� �� �ȴ�.(������ ū ���� ������ �� ���� ������)
������ 2: n�� �Ÿ��� ������ BFS�� �� ��, ������ ���� ���� ������ ������ ���� �� �ȴ�.(���� �Ÿ��� BFS�� �� ť���� �� �ڿ� ��ġ�� �ְ� '�� ��, �� ����' �� �� �ִ�
*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Pos {
	int r;
	int c;
};

/* �⺻ Input */
int N;
Pos shark; // ����� ��ġ
int eaten = 0; // �� ���� ����� ����
int sharkSize = 2; // ��� ũ��
int fish[25][25]; // ������� ��ġ �� ����� ũ��



/* BFS ���� ���� */
queue<Pos> q; // BFS���� ���� �� �ִ� ����⸦ �߰��� ���� ���� cnt
int dir[4][2] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} }; // �� ������ �ƹ��͵� �������� ����

int visited[25][25]; // BFS�� visited
int distArr[25][25]; // BFS���� �� ���� �� ������ cnt ���
int stdDist = 0; // BFS���� stdDist ������ŭ �� ��ġ�� ��, ���� �� �ִ� ����� ��� (�� �� ���� ��, ���� ������ ����⸦ �Ǻ��ؾ� ��)
vector<Pos> cands;



// cands�� �����ϴ� �� ����ϴ� �Լ�
bool cpr(Pos a, Pos b) {
	if (a.r == b.r) return a.c < b.c;
	return a.r < b.r;
}

int seconds; // �� �ɸ� �ð� (���������� �Ÿ��� ���ջ�)

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
	stdDist = 0;

	q.push(shark);
	int thisR, thisC;
	int tmpR, tmpC;

	while (!q.empty()) {

		thisR = q.front().r; thisC = q.front().c;

		if (fish[thisR][thisC] > 0 && fish[thisR][thisC] < sharkSize) { // ���� �� �ִ� ���� ����� �����
			return Pos{ thisR, thisC };
		}
		q.pop();

		if (stdDist != 0 && distArr[thisR][thisC] >= stdDist) continue;

		for (int i = 0; i < 4; i++) {
			tmpR = thisR + dir[i][0];
			tmpC = thisC + dir[i][1];

			if (tmpR < 0 || tmpC < 0 || N <= tmpR || N <= tmpC) continue;
			if (visited[tmpR][tmpC] != 0) continue;

			if (fish[tmpR][tmpC] > sharkSize) continue;
			
			if (fish[tmpR][tmpC] > 0 && fish[tmpR][tmpC] < sharkSize) { // ���� �� �ִ� �����
				distArr[tmpR][tmpC] = distArr[thisR][thisC] + 1;
				stdDist = distArr[tmpR][tmpC];
				cands.push_back(Pos{ tmpR, tmpC });
				// return Pos{ tmpR, tmpC }; ������ 2 �� ���õ� Ʋ���� �ϴ� ����
			}
			else {
				visited[tmpR][tmpC] = 1;
				q.push(Pos{ tmpR, tmpC });
				distArr[tmpR][tmpC] = distArr[thisR][thisC] + 1;
			}
			
		}
	}

	if (cands.size() > 0) {
		sort(cands.begin(), cands.end(), cpr);

		
		return Pos{ cands[0].r, cands[0].c };
	}
	else {
		return Pos{ -1, -1 };
	}
}


int main() {

	Input();

	Pos nextPos = Pos{ 0, 0 };
	
	while (1) { // ���� �� �ִ� ����⸦ ã�´�.(BFS)

		nextPos = BFS();
		if (nextPos.r == -1 && nextPos.c == -1) {
			break;
		}

		seconds += distArr[nextPos.r][nextPos.c];
		cands.clear();

		fish[nextPos.r][nextPos.c] = 0;
		shark.r = nextPos.r;
		shark.c = nextPos.c;
		eaten++;
		if (eaten == sharkSize) {
			eaten = 0;
			sharkSize++;
		}
		
	}
	
	cout << seconds;

	return 0;
}