/*
function call: main -> Draw -> main -> Count

1. 드래곤 커브 방향의 규칙성 파악 (i세대에서는 i+1 세대까지 움직인 방향의 역순에서 +1한 방향으로 움직인다)
2. 각 세대를 그릴 때
   - 이전 세대에서 마지막으로 끝난 점을 시작점으로 삼는다
   - 지금까지의 움직인 방향을 기록한 벡터(mem)를 역순으로 돌며 +1 한 방향으로 움직인다
   - 움직일 때마다 mem 벡터에 방향을 넣고, 마지막으로 끝난 점을 갱신한다
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
	for (int gen = 1; gen <= g; gen++) { // i세대 그리기
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

		// 시작점 및 0세대 그리기
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