/*
�ش信 �ʿ��� function call: main -> Input -> (DFS <--�ݺ�--> BFS) -> main

1. K���� ���̷��� ��, �ʱ⿡ Ȱ��ȭ��ų M�� ���̷����� ����(DFS)���� �����Ѵ�
2. ���� ��쿡�� BFS�� Ȱ���� ��� ��ĭ�� Ȱ��ȭ��Ű�� �ּ� �ð��� ���Ѵ�
3. �� ��쿡�� ���� �ּҽð� �� ���� ���� ���� ���� ����Ѵ�
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
int map[55][55];

struct Pos {
	int r;
	int c;
	int cnt;
};

// Ȱ��ȭ��ų ���̷����� ������ ��(DFS) ���� ����
vector<Pos> virus;
int picked[15];

// �� ��쿡 ��� �� ĭ�� Ȱ�����̷���ȭ ��Ű�� ��(BFS) ���� ����
queue<Pos> q;
int tmpMap[55][55];
int visited[55][55];
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

// �ݺ����� ���鼭 ���� ������ �� ���̴� ����
int vacantSize = 0;
int tmpR, tmpC;
int tmpTime;
int answer = 5000;

void Input() {
	scanf("%d %d\n", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &map[i][j]);
			if (map[i][j] == 2) {
				virus.push_back(Pos{ i, j, 0 });
			}
			else if (map[i][j] == 0) {
				vacantSize++;
			}
		}
	}
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", tmpMap[i][j]);
		}
		cout << endl;
	}
	/*for (int i = 0; i < virus.size(); i++) {
		cout << virus[i].r << "," << virus[i].c << endl;
	}*/
}


int BFS(int cnt) {
	/*for (int i = 0; i < M; i++) { // ���� ���̷��� ����
		cout << picked[i];
	}
	cout << endl;*/

	int activatedNum = 0; // Ȱ��ȭ�� �� ĭ�� ���� �ʱ�ȭ

	// ���� Ȱ��ȭ�� ���̷��� ���¸� tmpMap�� ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			tmpMap[i][j] = map[i][j];
		}
	}
	// Print();

	// visited �ʱ�ȭ
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited[i][j] = 0;
		}
	}

	while (!q.empty()) {
		Pos thisVirus = q.front();
		// cout << "thisVirus(" << thisVirus.cnt << "): " << thisVirus.r << "," << thisVirus.c << endl;
		q.pop();
		visited[thisVirus.r][thisVirus.c] = 1;

		for (int i = 0; i < 4; i++) {
			tmpR = thisVirus.r + dir[i][0];
			tmpC = thisVirus.c + dir[i][1];

			if (tmpR < 0 || N <= tmpR || tmpC < 0 || N <= tmpC) continue;
			if (visited[tmpR][tmpC] == 1 || tmpMap[tmpR][tmpC] == 1) continue;

			if (tmpMap[tmpR][tmpC] == 0) { // ������� Ȱ�����̷���ȭ ��Ű�� ���
				activatedNum++;
				// cout << tmpR << "," << tmpC << ":"<< tmpMap[tmpR][tmpC] << ", ���̷��� Ȱ��ȭ => " << activatedNum << " �� ��ĭ ��: " << vacantSize << endl;

				if (activatedNum == vacantSize) { // ��� ���̷����� Ȱ��ȭ�� ���
					return thisVirus.cnt + 1;
				}
			}

			tmpMap[tmpR][tmpC] = 9; // �� ĭ �Ǵ� ��Ȱ�����̷����� Ȱ�����̷���ȭ �ϱ�
			q.push(Pos{ tmpR, tmpC, thisVirus.cnt + 1 });
			visited[tmpR][tmpC] = 1;
			// cout << "push " << tmpR << "," << tmpC << "(" << thisVirus.cnt+1 << ")" << endl;
		}
	}

	return 5000; // ã�� ����
}


void DFS(int cnt, int pre) {
	if (cnt >= M) {
		/*for (int i = 0; i < M; i++) { // ���� ���̷��� ����
			cout << picked[i];
		}
		cout << endl;*/

		while (!q.empty()) { // q ����
			q.pop();
		}

		for (int i = 0; i < M; i++) {
			tmpR = virus[picked[i]].r;
			tmpC = virus[picked[i]].c;
			map[tmpR][tmpC] = 9; // Ȱ��ȭ
			q.push(Pos{ tmpR, tmpC, 0 }); // q�� �ʱ���� Ȱ��ȭ�� ���̷��� �ֱ�
		}

		// Print();

		// ������ �� �� �� �ɸ����� ���
		tmpTime = BFS(0);

		while (!q.empty()) { // q ����
			q.pop();
		}

		// cout << tmpTime << "�� " << answer << "��" << endl;
		if (tmpTime < answer) answer = tmpTime;

		// �ٽ� ���̷����� ��� ��Ȱ��ȭ
		for (int i = 0; i < M; i++) {
			tmpR = virus[picked[i]].r;
			tmpC = virus[picked[i]].c;
			map[tmpR][tmpC] = 2;
		}
		return;
	}

	for (int i = pre + 1; i < virus.size(); i++) {
		picked[cnt] = i;
		DFS(cnt + 1, i);	
	}

}

int main() {

	Input();

	if (vacantSize == 0) {
		cout << 0;
		return 0;
	}

	// virus ��������ŭ �߿��� m���� �̴� ����
	DFS(0, -1);

	if (answer == 5000) cout << -1;
	else cout << answer;

	return 0;
}