/*
function call: main -> Input -> (DFS -> Throw -> Grow -> BFS -> Init) -> main

1. �Լ� ����
DFS: �ʱ⿡ ������ �Ѹ� ��(2)�� G+R�� ����
Throw: DFS���� �� ���� ���� �ʷϻ�, ������ �Ѹ��� ��츦 ������ ����
Grow: ������ �۶߸����� BFS �Լ��� ȣ���� �� �� ��쿡 �ǿ� �� ������ ���ϰ�, �ٸ� ��츦 �õ��ϱ� ���� ������ �ʱ�ȭ�Ѵ�
BFS: ������ ������. �� �ʿ� �ѷ��� �������� bfsVisitTime�� �����鼭 �ٴѴ�.

2. ������
- DFS�� 2���� �迭 ���� �̴� ���� �򰥸�.
  ������ �̾ƾ� �ϰ� (��: (1,3)&(3,1) �� (3,1)&(1,3) �� �� �� ������ �� ��)
  ���� ���� ���� �� ������ �� �� (��: (0,0)&(0,0) ������ �� ��)
- ������ �̹� �ѷ��� ������ �ٸ� ������ �Ѹ� �� ����, ���� �ٸ� ���� ������ ���ÿ� �������� ������ ���� �ɴٴ�
  ������ �����ϱ� ����
*/
#include <iostream>
#include <vector>
#include <queue>;
using namespace std;

struct Pos {
	int r;
	int c;
	int cnt=0;
};

int N, M, G, R;
int map[50][50];
int backup[50][50];

int maxAnswer = 0;
int tmpNumber = 0;

vector<Pos> picked; // DFS���� ���

queue<Pos> q; // BFS���� ���
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int bfsVisitTime[50][50];

void Input() {
	cin >> N >> M >> G >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			backup[i][j] = map[i][j];
		}
	}
}

void Init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			map[i][j] = backup[i][j];
			bfsVisitTime[i][j] = 0;
		}
	}
}

void BFS() {
	int tmpR, tmpC;
	while (!q.empty()) {
		Pos thisPos = q.front();
		q.pop();
		if (map[thisPos.r][thisPos.c] != 10 && map[thisPos.r][thisPos.c] != 20) continue; // �̹� ���� �ƴµ� ������ ���� �ִ� pass

		for (int i = 0; i < 4; i++) {
			tmpR = thisPos.r + dir[i][0];
			tmpC = thisPos.c + dir[i][1];

			if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) continue;
			if (map[tmpR][tmpC] == 0 || map[tmpR][tmpC] == -1) continue; // ȣ���� pass
			if (map[thisPos.r][thisPos.c] == map[tmpR][tmpC]) continue; // ���� ������ �̹� �ѷ��� ������

			if (map[tmpR][tmpC] < 10) { // ������ ������ ������ �� ����
				map[tmpR][tmpC] = map[thisPos.r][thisPos.c];
				q.push(Pos{ tmpR, tmpC, thisPos.cnt+1 });
				bfsVisitTime[tmpR][tmpC] = thisPos.cnt + 1;
			}
			else if (map[tmpR][tmpC] != map[thisPos.r][thisPos.c] && bfsVisitTime[tmpR][tmpC] == thisPos.cnt + 1) { // ���� �ɴ�
				tmpNumber++;
				map[tmpR][tmpC] = -1;
			}
		}
	}
}

void Grow() { // ���� �۶߸���
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] != 10 && map[i][j] != 20) continue;
			q.push(Pos{ i,j,0 });
			bfsVisitTime[i][j] = 0;
		}
	}
	tmpNumber = 0;
	BFS();
	if (tmpNumber > maxAnswer) maxAnswer = tmpNumber;
}

int green[5];
void Throw(int cnt, int pre) {
	// �ʷϻ� ���� �Ѹ� �κ� ����
	if (cnt >= G) {
		/*cout << "�ʷϻ�: ";
		for (int i = 0; i < G; i++) {
			cout << green[i] << "��° ��ǥ & ";
		}
		cout << endl;*/

		// �ʷ�, ���� ������ �Ѹ���
		int greenIdx = 0;
		for (int i = 0; i < picked.size(); i++) {
			if (i == green[greenIdx]) {
				map[picked[i].r][picked[i].c] = 10; // green �Ѹ���

				greenIdx++;
			}
			else {
				map[picked[i].r][picked[i].c] = 20; // red  �Ѹ���
			}
		}

		Grow();

		Init();
		
		return;
	}

	for (int i = pre; i < picked.size(); i++) {
		green[cnt] = i;
		Throw(cnt + 1, i + 1);
	}
}


void DFS(int cnt, int preR, int preC) {
	if (cnt >= (G + R)) {
		/*for (int i = 0; i < picked.size(); i++) {
			cout << "(" << picked[i].r << "," << picked[i].c << ") ";
		}
		cout << endl;*/

		Throw(0, 0);

		return;
	}

	// 2���� �迭���� ���� ������ �ߺ� ���� ����
	for (int i = preR; i < N; i++) { // �̹� �� ������ �� �� ���� ���� �ʴ´�
		int startJ;
		if (preR == i) { // �̹��� ���� ���� ��� �̹� �� ���� ���� ������ j�� �� ���� �� �� ����
			startJ = preC;
		}
		else { // �̹� ���� ���� �ຸ�� ũ��
			startJ = 0;
		}

		for (int j = startJ; j < M; j++) {
			if (map[i][j] != 2) continue;

			// �̹� ���� ���� ���� ���� x
			 if (cnt != 0 && picked[cnt - 1].r == i && picked[cnt - 1].c == j) 
				 continue;

			if (map[i][j] == 2) {
				picked.push_back(Pos{ i, j });
				DFS(cnt + 1, i, j);
				picked.pop_back();
			}
		}
	}
}

int main() {

	Input();

	DFS(0, 0, 0);

	cout << maxAnswer;

	return 0;
}