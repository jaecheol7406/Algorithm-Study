/*
function call: main -> Input -> (Init -> BFS) -> main

1. ����� ��ġ���� ��� ���� Ž���� BFS�� ���� �� �ִ� ����� �ĺ��� ���Ѵ�
   <�ð�����>
   ���� ª�� �Ÿ��� �ֵ��� ��� ���ؾ� �ϰ�, �� �̻��� ���� �ʿ� ����
   (��: BFS �ϸ鼭 ���� 3�� �ְ� �������� ���� 3�� ���� ��� ���ϰ� 4 �Ѿ�� �ͺ��ʹ� x)
2. ����� �ĺ����� ��� �� ������������ �����Ѵ�. �׷� 0��° �ĺ��� ���ǿ� �����ϴ� ������
3. �Դ´�. �Ÿ�(=�ɸ� �ð�)�� ���ϰ� map�� ��������� �����Ѵ�
4. ����� �ĺ��� 0�� �ɶ����� �ݺ��Ѵ�
*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct Fish {
	int r;
	int c;
	int d = 0; // BFS���� �̵��Ÿ�
};

int N;
int map[20][20];
Fish shark;
int sharkSize = 2;
int sharkEaten = 0;
queue<Fish> q;

int minSize;

vector<Fish> cands;

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				shark.r = i;
				shark.c = j;
			}
		}
	}
	
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

bool cmp(Fish a, Fish b) {
	if (a.d == b.d && a.r == b.r) {
		return a.c < b.c;
	}
	if (a.d == b.d) {
		return a.r < b.r;
	}
	return a.d < b.d;
}

int answer = 0;
int visited[20][20];
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
void BFS() {
	int tmpR, tmpC;

	while (!q.empty()) {
		Fish thisPos = q.front();
		q.pop();

		

		for (int i = 0; i < 4; i++) {
			tmpR = thisPos.r + dir[i][0];
			tmpC = thisPos.c + dir[i][1];

			if (tmpR < 0 || tmpC < 0 || N <= tmpR || N <= tmpC) continue;
			if (map[tmpR][tmpC] > sharkSize) continue;
			if (visited[tmpR][tmpC] == 1) continue;

			// ���� �� �ִ� ���� ����� ����⸦ ã��
			if (map[tmpR][tmpC] != 0 && map[tmpR][tmpC] < sharkSize) {
				cands.push_back(Fish{ tmpR, tmpC, thisPos.d + 1 });
				if (minSize > thisPos.d + 1) minSize = thisPos.d + 1;
			}

			// �ð� ���� (4ms -> 0ms)
			if (thisPos.d + 1 > minSize) continue; // �̹� �ĺ��� ���°� ������ �׺��� ū �ĺ��� ã�� �ʴ´�

			visited[tmpR][tmpC] = 1;
			q.push(Fish{ tmpR, tmpC, thisPos.d + 1 });
		}
	}
}

void Init() {
	while (!q.empty()) {
		q.pop();
	}

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			visited[i][j] = 0;
		}
	}

	cands.clear();

	q.push(shark);
	visited[shark.r][shark.c] = 1;

	minSize = 9999; // �ִ� 400
}

int main() {

	Input();

	while (1) {
		// Print();
		Init();

		// ���� �Ÿ� ������ ���� �� �ִ� �� ã��
		BFS();

		if (cands.size() == 0) break;		

		// ���� ��� ã��
		sort(cands.begin(), cands.end(), cmp);
		Fish target = cands[0];

		// �Ա�
		answer += target.d ;
		// cout << "+=" << target.d << endl;
		map[shark.r][shark.c] = 0;
		shark.r = target.r;
		shark.c = target.c;
		map[shark.r][shark.c] = 9;

		// ��� ���� ����
		sharkEaten++;
		if (sharkEaten == sharkSize) {
			sharkSize++;
			sharkEaten = 0;
		}
	}

	cout << answer;

	return 0;
}