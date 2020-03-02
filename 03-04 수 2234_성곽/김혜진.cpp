/*
# �⺻������ BFS�� ��ȸ�ؼ� ���� ���� �� ���� ū ���� ũ�⸦ ���Ѵ�.
# �湮 ������ ������ �Ǵ��Ѵ�.
  1.Ư�� ��ġ(i,j)�� ���� 2������ �ٲ� ũ�� 4¥�� �迭(jinsu)�� ��´�.
    13  ->  1 1 0 1

  2. dir �迭�� ������ ���� �����Ѵ�.
    dir[0]  <==  2^3 �ǹ�, ���ʿ� ���� ����.
	dir[1]  <==  2^2 �ǹ�, ���ʿ� ���� ����.
	dir[2]  <==  2^1 �ǹ�, ���ʿ� ���� ����.
	dir[3]  <==  2^0 �ǹ�, ���ʿ� ���� ����.

  3. 2���� �迭(jinsu)�� dir�迭�� ���� �� �� �ִ� ��ǥ�� q�� �ִ´�
    if(dir[0] == 1) �������� ����=> continue
	if(dir[1] == 1) �������� ����=> continue
	if(dir[2] == 1) �������� ����=> continue
	if(dir[3] == 1) �������� ����=> continue


# ���� �ϳ��� �㹰 ������ ��� ��ǥ�� ��� ���� �㹮 �� ���� ������ �ݺ��Ѵ�.
# ���� �㹮��.
  1. Ư�� ��ġ(i,j)�� ���� 2������ �ٲ� ũ�� 4¥�� �迭(jinsu)�� ��´�.
  2. jinsu �迭�� ���鼭 ���� 1�� ���, �ش� ����ŭ�� map[i][j]���� ���� Ž���� �Ѵ�.
    map[i][j] -= pow(2, (3 - c));
	��: map[i][j] = 13�̶��,
	  map[i][j] -= 8 �� �� Ž�� ����, Ž�� ������ map[i][j] += 8
	  map[i][j] -= 4 �� �� Ž�� ����, Ž�� ������ map[i][j] += 4
	  map[i][j] -= 1 �� �� Ž�� ����, Ž�� ������ map[i][j] += 1
	�̿� ���� ������ ��� (i,j) ������ ���� �����Ѵ�.
*/
#include <iostream>
#include <queue>
#include <vector>
#include <math.h>
using namespace std;

// BFS�� �ʿ��� �⺻ ����
struct Pos {
	int r;
	int c;
};
int m, n;
int map[110][110];
int visited[110][110];
queue<Pos> q;

// ���� ��ġ�� ����, ����, ����, ���� ��.
int dir[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
int jinsu[4];

void Input() {
	scanf("%d %d\n", &n, &m);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
}

void Print() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", map[i][j]);
		}
		cout << endl;
	}
}

// 10���� org�� 2������ �ٲ� jinsu �迭�� �ִ´�
void Convert(int org) {
	for (int i = 3; i>=0; i--) {
		int rems = org % 2;
		jinsu[i] = rems;
		org /= 2;
	}
	/*for (int i = 0; i < 4; i++) {
		cout << jinsu[i] << " ";
	}
	cout << endl;*/
}

int MAX = 0;
void BFS() {
	int maxCnt = 0;
	while (!q.empty()) {
		Pos thisPos = q.front();
		q.pop();
		maxCnt++;
		// cout << thisPos.r << "," << thisPos.c << "�湮" << endl;

		int tmpr, tmpc;
		Convert(map[thisPos.r][thisPos.c]);
		for (int i = 0; i < 4; i++) {
			if (jinsu[i] == 1) continue;
			tmpr = thisPos.r + dir[i][0];
			tmpc = thisPos.c + dir[i][1];

			if (tmpr < 0 || tmpc < 0 || m <= tmpr || n <= tmpc) continue;
			if (visited[tmpr][tmpc] != 0) continue;

			q.push(Pos{ tmpr, tmpc });
			visited[tmpr][tmpc] = 1;
		}
	}
	if (MAX < maxCnt) MAX = maxCnt;
}


int cnt = 0;
void Search() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j] == 1) continue;
			q.push(Pos{ i, j });
			visited[i][j] = 1;
			// cout << i << "," << j << "���� cnt++" << endl;
			cnt++;
			BFS();
		}
	}
}

void Destroy() {

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			Convert(map[i][j]);

			for (int c = 0; c < 4; c++) {
				if (jinsu[c] == 0) continue;
				map[i][j] -= pow(2, (3 - c));
				//cout << i << "," << j << "�� " << c << "�� ���� �㹰����: -" << pow(2, (3-c)) << "=" << map[i][j] << endl;
				
				// visited ����
				for (int i = 0; i < m; i++) {
					for (int j = 0; j < n; j++) {
						visited[i][j] = 0;
					}
				}

				Search();
				// cout << "�� ����: " << cnt << "�ִ� ũ��: " << MAX << endl;
				map[i][j] += pow(2, (3 - c));
			}
		}
	}
}

int main() {

	Input();
	// Print();

	Search();

	cout << cnt << endl;
	cout << MAX << endl;

	Destroy();
	cout << MAX << endl;

	return 0;
}