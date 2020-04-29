/*
SWEA 1953번: 탈주범 검거
문제 유형 : 시뮬레이션(BFS)

1. 각 지하 터널이 이동할 수 있는 방향 정보를 vector<vector<int>> dir에 입력.
2. BFS로 탐색
3. 해당 좌표와 이동 할 좌표가 연결되어있는지 확인(IsPossible())
	-> 현재 이동하고 있는 방향과 다음 터널에서의 방향이 반대여야 연결되어 있으므로
		방향을 180도 회전하고, 다음 터널이 회전한 방향을 포함하고 있는지 확인한다.


*/
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
int N, M, start_x, start_y, L;
int board[51][51];
bool visit[51][51];
int answer;
int dx[4] = { 1,0,-1,0 }; // 하,우,상,좌
int dy[4] = { 0,1,0,-1 };
vector<vector<int>> dir{ {}, {0,1,2,3},{0,2},{1,3},{1,2},{0,1},{0,3},{2,3} };
void Input() {
	cin >> N >> M >> start_x >> start_y >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
}
void Initialize() {
	memset(visit,0, sizeof(visit));
	answer = 1;
}
bool IsPossible(int d, int x,int y) {
	d = (d + 2) % 4; //반대 방향으로 바꿈
	int type = board[x][y];
	for (int i = 0; i < dir[type].size(); i++) {
		if (dir[type][i] == d)
			return true;
	}
	return false;
}
void BFS() {
	queue<pair<pair<int, int>,int>> que;
	que.push({ { start_x,start_y },0 });
	visit[start_x][start_y] = true;

	while (!que.empty()) {
		int x = que.front().first.first;
		int y = que.front().first.second;
		int time = que.front().second;
		int type = board[x][y];
		que.pop();
		if (time >= L-1)
			break;
		for (int i = 0; i < dir[type].size(); i++) {
			int nd = dir[type][i];
			int nx = x + dx[nd];
			int ny = y + dy[nd];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M)
				continue;
			if (visit[nx][ny])
				continue;
			if (!IsPossible(nd, nx, ny))
				continue;
			visit[nx][ny] = true;
			que.push({ {nx,ny},time + 1 });
			answer++;
		}
		
	}
}
void Solution() {
	BFS();
}
void Solve() {
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Initialize();
		Input();
		Solution();
		cout << "#" << i << " " << answer << endl;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}