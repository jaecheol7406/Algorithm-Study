/*
BOJ 17144번: 미세먼지 안녕!
문제 유형 : 시뮬레이션

1. Speard(미세먼지 확산)
	(1) 인접한 방향에 확산이 일어나면 임시 배열에 그 값을 누적시킨다.
	(2) 인접한 방향 확인이 끝나면 임시 배열에 남은 미세먼지 양을 누적시킨다.
	(3) 확산이 끝나면 원래의 board에 copy한다.
2. actAir(공기청정기 작동)
	(1) 위쪽 바람은, 공기 청정기 좌표 중 x값이 작은 좌표를 기준으로 반시계 확산한다.
		아래쪽 바람은, 공기 청정기 좌표 중 x값이 큰 좌표를 기준으로 시계방향 확산한다.

		확산 중, 모서리에 접근하면 방향을 바꿔준다.

		
*/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int R, C, T;
int board[51][51];
int t_board[51][51];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
int air_top = -1;
int air_bottom;
void Input() {
	cin >> R >> C >> T;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> board[i][j];
			if (board[i][j] == -1) {
				if (air_top == -1)
					air_top = i;
				else
					air_bottom = i;
			}
		}
	}
}
void Spread() {
	memset(t_board, 0, sizeof(t_board));
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (board[i][j] == 0)
				continue;
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (nx < 0 || nx >= R || ny < 0 || ny >= C)
					continue;
				if (nx == air_top && ny == 0)
					continue;
				if (nx == air_bottom && ny == 0)
					continue;
				t_board[nx][ny] += board[i][j] / 5;
				cnt++;
			}
			t_board[i][j] += (board[i][j] - (board[i][j] / 5) * cnt);
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			board[i][j] = t_board[i][j];
		}
	}
}
void actAir() {
	//위쪽 바람
	int dir = 2;
	int nx = air_top - 1;
	int ny = 0;
	while (!(nx==air_top && ny==1)) {
		board[nx][ny] = board[nx + dx[dir]][ny + dy[dir]];
		nx = nx + dx[dir];
		ny = ny + dy[dir];
		if (nx == 0 && ny == 0 || nx == 0 && ny == C - 1 || nx == air_top && ny == C - 1)
			dir = (dir + 3) % 4;

	}
	board[nx][ny] = 0;
	//아래쪽 바람
	dir = 0;
	nx = air_bottom + 1;
	ny = 0;
	while (!(nx == air_bottom && ny == 1)) {
		board[nx][ny] = board[nx + dx[dir]][ny + dy[dir]];
		nx = nx + dx[dir];
		ny = ny + dy[dir];
		if (nx == R-1 && ny == 0 || nx == R-1 && ny == C - 1 || nx == air_bottom && ny == C - 1)
			dir = (dir + 1) % 4;

	}
	board[nx][ny] = 0;
	
}
void Solution() {
	while (T--) {
		Spread();
		actAir();
	}
	int sum = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (board[i][j] == -1)
				continue;
			sum += board[i][j];
		}
	}
	cout << sum << endl;
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