#include <iostream>
#include <cstring>

#define MAX 20
#define endl '\n'

using namespace std;

int board[MAX][MAX];
bool visit[101];
int start_x, start_y, N, result;
int dx[4] = { 1,1, -1,-1 };
int dy[4] = { -1,1,1,-1 };
void Initialize() {
	memset(board, 0, sizeof(board));
	memset(visit, 0, sizeof(visit));
	result = -1;
}
void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
}
bool IsRange(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}
bool IsStart(int x, int y) {
	return x == start_x && y == start_y;
}
void Dfs(int x,int y, int cnt, int dir) {
	if (IsStart(x,y) &&dir==3 ) { //시작점에 돌아온 경우
		if (cnt > result)
			result = cnt;
		return;
	}
	for (int i = 1; i <= 2; i++) {
		int nx, ny, nd;
		if (i == 1) { //진행 방향 그대로
			nx = x + dx[dir];
			ny = y + dy[dir];
			nd = dir;
		}
		else { //반시계 회전
			if ((x == start_x && y == start_y) || dir==3)
				continue;
			nd = dir + 1;
			nx = x + dx[nd];
			ny = y + dy[nd];
			
		}
		if (!IsRange(nx, ny))
			continue;

		if (IsStart(nx, ny))
			Dfs(nx, ny, cnt + 1, nd);

		if (!visit[board[nx][ny]]) {
			visit[board[nx][ny]] = true;
			Dfs(nx, ny, cnt + 1, nd);
			visit[board[nx][ny]] = false;
		}
	}
}
void Solution() {
	for (int i = 0; i < N-1; i++) {
		for (int j = 1; j < N-1; j++) {
			start_x = i;
			start_y = j;
			visit[board[i][j]] = true;
			Dfs(i, j, 0, 0 ); // 왼쪽 아래부터 탐색
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