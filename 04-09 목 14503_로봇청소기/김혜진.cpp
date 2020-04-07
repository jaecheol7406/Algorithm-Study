/*
function call: main -> Input -> (Search <-> main) -> main

문제 조건대로 구현
로봇의 방향 전환은 공식이 아니라 배열을 만들어 정해줌
int dir[i][j] <- 로봇의 방향이 i 일 때 이동할 방향
int turn[i][j] <- 로봇의 방향이 현재 i일 때 차례로 탐색할 방향
int oppDir[i] = { 2, 3, 0, 1 }; <- 로봇의 방향이 i일 때 후진할 방향
*/
#include <iostream>
using namespace std;

struct Pos {
	int r;
	int c;
	int d;
};
Pos robot;

int N, M;
int map[60][60];

void Input() {
	scanf("%d %d\n", &N, &M);

	int a, b, c;
	scanf("%d %d %d\n", &a, &b, &c);
	robot = Pos{ a, b, c };

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
}

int answer = 0;
int dir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} }; // 북, 동, 남, 서 순서
int turn[4][4] = { { 3, 2, 1, 0}, {0, 3, 2, 1}, {1, 0, 3, 2}, {2, 1, 0, 3} }; // 로봇이 탐색할 순서
int oppDir[4] = { 2, 3, 0, 1 };
int tmpDir, tmpR, tmpC;

int Search() {
	for (int i = 0; i < 4; i++) { // 네 방향 탐색
		tmpDir = turn[robot.d][i]; // 탐색할 방향
		tmpR = robot.r + dir[tmpDir][0];
		tmpC = robot.c + dir[tmpDir][1];

		if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) continue;
		if (map[tmpR][tmpC] == 0) { // 갈 수 있는 곳을 찾음
			robot.d = tmpDir;
			robot.r = tmpR;
			robot.c = tmpC;
			return 0;
		}
	}

	// 네 방향 다 못 가면 뒤로 갈 수 있는지 탐색
	tmpDir = oppDir[robot.d];
	tmpR = robot.r + dir[tmpDir][0];
	tmpC = robot.c + dir[tmpDir][1];

	if (map[tmpR][tmpC] == 1) {
		return -1;
	}
	else {
		robot.r = tmpR;
		robot.c = tmpC;
		return 0;
	}
}

int main() {

	Input();
	
	int tmp;
	while (1) {
		if (map[robot.r][robot.c] == 0) { // 현재 있는 곳이 빈 칸이면 청소
			map[robot.r][robot.c] = 2; 
			answer++;
		}

		tmp = Search();
		if (tmp == -1) {
			break;
		}
		
	}

	cout << answer << endl;

	return 0;
}