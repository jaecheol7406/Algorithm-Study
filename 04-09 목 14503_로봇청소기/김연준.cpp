/*
BOJ 14503: 로봇 청소기
문제 유형 : 시뮬레이션

1. 로봇의 현재 위치가 청소 안한 곳이라면 청소한다(좌표의 값을 2로 바꿈)
2. 4방향을 탐색해서 청소 안한 곳을 찾는다.
	(1) 청소 안한 곳이 있으면 좌표를 바꿈.
3. 4방향 다 청소되어있으면 로봇을 후진 시킨 좌표가 벽인지 보고 벽이면 끝낸다.

*/
#include <iostream>

using namespace std;
int board[51][51];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int N, M;
int robot_x, robot_y, dir;
void Input() {
	cin >> N >> M;
	cin >> robot_x >> robot_y >> dir;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
}
void Solution() {
	int cnt = 0;
	while (true) {
		if (board[robot_x][robot_y] == 0) {
			board[robot_x][robot_y] = 2;
			cnt++;
		}
		bool flag = false;
		for (int i = 0; i < 4; i++) {
			dir = (dir + 3) % 4;
			int nx = robot_x + dx[dir];
			int ny = robot_y + dy[dir];
			if (board[nx][ny]==0) {
				robot_x = nx;
				robot_y = ny;
				flag = true;
				break;
			}
		}
		if (!flag) {
			robot_x = robot_x + dx[(dir + 2) % 4];
			robot_y = robot_y + dy[(dir + 2) % 4];
			if (board[robot_x][robot_y] == 1) {
				break;
			}
		}
	}
	cout << cnt << endl;
}
void Solve() {
	Input();
	Solution();
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}