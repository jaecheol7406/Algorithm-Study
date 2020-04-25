/*
function call: main -> Draw -> main -> Count

1. �巡�� Ŀ�� ������ ��Ģ�� �ľ� (i���뿡���� i+1 ������� ������ ������ �������� +1�� �������� �����δ�)
2. �� ���븦 �׸� ��
   - ���� ���뿡�� ���������� ���� ���� ���������� ��´�
   - ���ݱ����� ������ ������ ����� ����(mem)�� �������� ���� +1 �� �������� �����δ�
   - ������ ������ mem ���Ϳ� ������ �ְ�, ���������� ���� ���� �����Ѵ�
*/
#include <iostream>
#include <vector>
using namespace std;

int x, y, d, g;
int map[110][110];
int N;

vector<int> mem;
int lastX, lastY;
int thisDir;

int dir[4][2] = { {0, 1}, {-1, 0}, {0, -1}, {1, 0} };
void Draw() {
	for (int gen = 1; gen <= g; gen++) { // i���� �׸���
		for (int idx = mem.size() - 1; idx >= 0; idx--) {
			thisDir = (mem[idx] + 1) % 4;
			lastX += dir[thisDir][0];
			lastY += dir[thisDir][1];
			map[lastX][lastY] = 1;
			mem.push_back(thisDir);
		}
	}
}

int Count() {
	int squareNum = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (map[i][j] == 0) continue;
			if (map[i + 1][j] == 0) continue;
			if (map[i][j + 1] == 0)continue;
			if (map[i + 1][j + 1] == 0) continue;
			squareNum++;
		}
	}
	return squareNum;
}

int main() {

	scanf("%d\n", &N);
	for (int i = 0; i < N; i++) {
		mem.clear();
		scanf("%d %d %d %d\n", &y, &x, &d, &g);

		// ������ �� 0���� �׸���
		map[x][y] = 1;
		lastX = x + dir[d][0];
		lastY = y + dir[d][1];
		map[lastX][lastY] = 1;
		mem.push_back(d);

		Draw();
	}

	cout << Count();

	return 0;
}