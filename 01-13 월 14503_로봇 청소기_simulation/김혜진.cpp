#include <iostream>
#include <queue>
using namespace std;

struct Pos {
	int r;
	int c;
	int d;
};

int R, C;
int map[60][60];
int visited[60][60];
int dir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} }; // 북, 동, 남, 서 순
int dirmap[4][4] = { {3, 2, 1, 0}, {0, 3, 2, 1}, {1, 0, 3, 2}, {2, 1, 0, 3} };
queue<Pos> q;

void Input() {
	scanf("%d %d\n", &R, &C);
	int r, c, d;
	scanf("%d %d %d\n", &r, &c, &d);
	q.push(Pos{r, c, d});

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
}

void Print() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}

int main() {
	Input();
	
	int answer = 0;
	while (!q.empty()) {
		Pos thisPos = q.front();
		q.pop();

		if (visited[thisPos.r][thisPos.c] == 0) {
			visited[thisPos.r][thisPos.c] = 1; // 청소
			answer++;
		}
		

		int rtmp, ctmp;
		for (int i = 0; i < 4; i++) {
			// int newDir = (thisPos.d - i + 4) % 4;
			int newDir = dirmap[thisPos.d][i];
			rtmp = thisPos.r + dir[newDir][0];
			ctmp = thisPos.c + dir[newDir][1];

			if (rtmp < 0 || R <= rtmp || ctmp < 0 || C <= ctmp) continue;
			if (map[rtmp][ctmp] == 0 && visited[rtmp][ctmp] == 0) { // 청소할 수 있고 갈 수 있다
				q.push(Pos{rtmp, ctmp, newDir});
				break; // for문을 나간다
			}
		}
		if (q.empty()) { // 후진한다
			int newDir = (thisPos.d + 2) % 4;
			int rtmp = thisPos.r + dir[newDir][0];
			int ctmp = thisPos.c + dir[newDir][1];

			if (rtmp < 0 || R <= rtmp || ctmp < 0 || C <= ctmp) continue;

			if (map[rtmp][ctmp] == 0) {
				q.push(Pos{rtmp, ctmp, thisPos.d});
			}
		}
	}
	cout << answer;

	return 0;
}