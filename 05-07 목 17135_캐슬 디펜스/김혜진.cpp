/*
function call: main -> Input -> (DFS -> Simulate -> BFS) -> main

1. DFS�� �ü��� ��ġ�Ѵ�
2. BFS�� �Ÿ��� ���� ������� �� �� �ִ� ������ �ü����� ���صд�
3. ��� �ü��� ���ÿ� �����ϹǷ� ���� Ƚ���� �ƴ� ���� �� ������ ����
4. ���� ���Ŀ��� ������ �� ĭ�� �Ʒ��� ����
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Pos {
	int r;
	int c;
	int d = 0; // BFS���� ���� cnt
};

vector<Pos> myList; // �ü� ����
queue<Pos> q;

int N, M, D;
int map[15][15];
int backup[15][15];
int visited[15][15]; // BFS���� ���
int myR; // �ü��� �� ��ġ

int tmpAnswer;
int answer;

void Input() {
	cin >> N >> M >> D;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			backup[i][j] = map[i][j];
		}
	}
	myR = N;
}

bool Close() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 1) return false;
		}
	}

	return true;
}
vector<Pos> cands;
int candSize = -1;

void Init() { // �ü��� �ٲ� ������ Init
	while (!q.empty()) {
		q.pop();
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visited[i][j] = 0;
		}
	}

	candSize = -1;
	cands.clear();
}

bool cmp(Pos a, Pos b) {
	if (a.d == b.d) {
		return a.c < b.c; // �׷��� ���� ������ ��쿡�� ���� ���ʿ� �ִ� ���� �����Ѵ�
	}
	return a.d < b.d;
}

int dir[3][2] = { {-1, 0}, {0, 1}, {0, -1} };
void BFS() {
	int tmpR, tmpC;
	while (!q.empty()) {
		Pos thisPos = q.front();
		q.pop();

		if (thisPos.d + 1 > D) continue;
		if (candSize != -1 && thisPos.d + 1 > candSize) continue; // �Ÿ��� �ּҰ� �ƴ� �ֵ��� ���� �ʴ´� (>= �� �ƴ϶� > ������: 31%���� Ʋ�� ����)

		for (int i = 0; i < 3; i++) {
			tmpR = thisPos.r + dir[i][0];
			tmpC = thisPos.c + dir[i][1];

			if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) continue;
			if (visited[tmpR][tmpC] == 1) continue;
			if (candSize != -1 && thisPos.d + 1 > candSize) continue;

			if (map[tmpR][tmpC] == 1) { // ���� ã��
				candSize = thisPos.d + 1;
				cands.push_back(Pos{ tmpR, tmpC, thisPos.d + 1 });
				continue;
			}

			visited[tmpR][tmpC] = 1;
			q.push(Pos{ tmpR, tmpC, thisPos.d + 1 });
		}
	}
}

void Simulate() {
	vector<Pos> dead;

	while (1) {
		// ��������: ���� ����
		if (Close()) {
			break;
		}

		dead.clear();

		// ��� �ü��� ���� ���̷��� ����� ã�´�
		for (int t = 0; t < myList.size(); t++) {
			Pos me = myList[t];
			Init();
			q.push(me);

			BFS();

			if (cands.size() == 0) continue; // ���� �� �ִ� �ְ� ������ pass
			sort(cands.begin(), cands.end(), cmp);
			/*cout << "�ĺ���: ";
			for (int i = 0; i < cands.size(); i++) {
				cout << cands[i].r << "," << cands[i].c << "  ";
			}
			cout << endl;
			cout << "=> ���� ��: " << cands[0].c << endl;*/
			dead.push_back(Pos{ cands[0].r, cands[0].c, cands[0].d });
		}

		// ��� �ü��� ���ÿ� �����Ѵ�.
		for (int i = 0; i < dead.size(); i++) {
			Pos enemy = dead[i];
			if (map[enemy.r][enemy.c] == 1) { // ���� ���� ���� �ü����� ���ݴ��� �� �ִ�.
				map[enemy.r][enemy.c] = 0;
				tmpAnswer++;
			}
		}

		// ���� �� ĭ�� �Ʒ��� �̵��Ѵ�
		for (int i = N - 1; i >= 0; i--) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] == 1) {
					if (i == N - 1) map[i][j] = 0;
					else {
						map[i + 1][j] = map[i][j];
						map[i][j] = 0;
					}
				}
			}
		}

		/*for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cout << map[i][j];
			}
			cout << endl;
		}*/

	}
	// cout << tmpAnswer << endl;
	if (tmpAnswer > answer) answer = tmpAnswer;
}

void DFS(int cnt, int pre) {
	if (cnt >= 3) { // �ü� �� ����
		// cout << "�ü�:" << myList[0].c << ", " << myList[1].c << ", " << myList[2].c << "===========" << endl;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				map[i][j] = backup[i][j];
			}
		}

		tmpAnswer = 0;
		Simulate();

		return;
	}

	for (int j = pre; j < M; j++) {

		myList.push_back(Pos{ myR, j });

		DFS(cnt + 1, j + 1);

		myList.pop_back();
	}
}

int main() {
	Input();

	DFS(0, 0);

	cout << answer;

	return 0;
}