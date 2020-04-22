/*
Swea 2105: 디저트 카페

문제유형 : 시뮬레이션, 완전탐색

1. DFS를 사용해서 완전탐색, 0행부터 밑을 향하여 마름모를 만들어서 N-3행 까지만 반복하면 됨, 0열과 N-1열 또한 마름모를 만들 수 없음.
2. DFS 탐색 시, 각 좌표에서 진행 가능한 경우는 두 가지이다.
	(1) 진행방향 유지
	(2) 진행방향에서 90도 꺾기(시작 좌표와 3번 다 꺾은 경우는 더이상 꺾지못함)
3. 다음 좌표(nx,ny)가 시작 좌표(start_x,start_y)인지 확인하는 조건문 필요 
	(start_x,start_y는 이미 방문 체크되었기 때문에)
3. DFS 탐색하다 시작 좌표에 도달하면 결과 도출.
*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int N;
int board[20][20];
int dx[4] = { 1,1,-1,-1 };
int dy[4] = { 1,-1,-1,1 };
bool visit[101];
int result,start_x, start_y;
void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
}
void Initialize() {
	memset(board, 0, sizeof(board));
	memset(visit, 0, sizeof(visit));

	result = -1;
}
void DFS(int x, int y, int dir, int cnt) {
	if (x == start_x && y == start_y && cnt > 1) {
		result = max(result, cnt);
		return;
	}
	for (int i = 0; i < 2; i++) {
		int nx, ny, nd;
		if (i == 0) {
			nd = dir;
		}
		else {
			if ((x == start_x && y == start_y) || dir == 3)
				continue;
			nd = dir + 1;
		}
		nx = x + dx[nd];
		ny = y + dy[nd];
		if (nx == start_x && ny == start_y) {
			DFS(nx, ny, nd, cnt);
			continue;
		}
		if (nx < 0 || nx >= N || ny < 0 || ny >= N)
			continue;
		if (visit[board[nx][ny]])
			continue;
		visit[board[nx][ny]] = true;
		DFS(nx, ny, nd, cnt + 1);
		visit[board[nx][ny]] = false;
	}
}
void Solution() {
	for (int i = 0; i < N - 2; i++) {
		for (int j = 1; j < N - 1; j++) {
			visit[board[i][j]] = true;
			start_x = i;
			start_y = j;
			DFS(i, j, 0, 1);
			visit[board[i][j]] = false;
		}
	}
}
void Solve() {
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Initialize();
		Input();
		Solution();
		cout << "#" << i << " " << result << endl;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}