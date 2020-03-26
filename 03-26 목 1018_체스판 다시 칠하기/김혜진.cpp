/*
1. 타일을 자르는 모든 경우의 수에 대해서
2. 가장 좌측 상단 타일의 색깔이 'B'일 때와 'W'일 때 두 경우에 대해
3. BFS로 칠해야 하는 타일이 몇 개인지 세본다

Function call: Input -> { 반복문: Init() -> BFS }
*/
#include <iostream>
#include <queue>
using namespace std;

struct Tile {
	int r;
	int c;
};

/* Input 받는 데 사용하는 변수 */
int N, M;
char map[55][55];

/* BFS에 사용하는 변수 */
queue<Tile> q;
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int visited[55][55];
int tmpR, tmpC;

/* 전체 시스템에서 집계된 칠해야 하는 수 */
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
	int target = 0; // 이번 BFS에서 칠해야 하는 타일 개수를 누적하는 변수

	q.push(Tile{ r, c });
	char oddColor, evenColor;

	if ((r + c) % 2 == 0) { // 시작점이 짝수면
		evenColor = map[r][c];
		if (evenColor == 'W') oddColor = 'B';
		else oddColor = 'W';
	}
	else { // 시작점이 홀수면
		oddColor = map[r][c];
		if (oddColor == 'W') evenColor = 'B';
		else evenColor = 'W';
	}

	while (!q.empty()) {
		if (minTarget < target) return target; // 어차피 안될 것으로 판명되면 조기 종료

		Tile thisQ = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			
			tmpR = thisQ.r + dir[i][0];
			tmpC = thisQ.c + dir[i][1];
			
			if (tmpR < r || tmpC < c || r + 8  <= tmpR || c + 8 <= tmpC) continue; // 범위 체크가 다른 BFS보다 특수한 문제임
			
			if (visited[tmpR][tmpC] == 1) continue;

			if ((tmpR + tmpC) % 2 == 0 && map[tmpR][tmpC] != evenColor) { // 이번 수가 짝수인데 짝수번 색깔과 일치하지 않으면
				target++;
			}

			if ((tmpR + tmpC) % 2 == 1 && map[tmpR][tmpC] != oddColor) { // 이번 수가 홀수인데 홀수번 색깔과 일치하지 않으면
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
	int tmpTarget; // 매 BFS에서 나온 칠해야 하는 타일 갯수
	
	for (int startR = 0; N - 8 >= startR; startR++) { // 자른다
		for (int startC = 0; M - 8 >= startC; startC++) {

			// 일부러 다른 색으로 만들고 칠해본다
			if (map[startR][startC] == 'W') map[startR][startC] = 'B';
			else map[startR][startC] = 'W';

			Init();
			tmpTarget = BFS(startR, startC) + 1;
			if (minTarget > tmpTarget) minTarget = tmpTarget;


			// 원래 색으로 돌리고 다시 세본다
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