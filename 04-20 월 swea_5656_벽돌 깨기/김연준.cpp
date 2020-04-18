/*
SWEA 5656.[모의 SW 역량테스트] 벽돌 깨기
문제 유형 : 시뮬레이션, 완전탐색
function call() : main -> Solve - > Initialize - >input->solution->DFS->play->gravity->getResult.
1. 중복순열로 구슬로 맞출 벽돌을 정한다.(DFS())
2. 벽돌을 깬다(play())
	(1) BFS를 사용해서 구슬이 벽돌에 명중하면 그 벽돌의 범위에 있는 벽돌을 queue에 추가.
	(2) queue에 추가할 때, visit으로 방문 체크를 하여 중복 방문을 방지.
	(3) 해당 벽돌의 범위를 모두 검사했으면, 벽돌이 제거되었으므로 0으로 바꿔준다.(gravity()를 위해)
3. 벽돌을 밑으로 떨어뜨림(gravity())
4. 결과 계산

*/
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
int T, N, M; //[H][W];
int board[16][16];
int t_board[16][16];
int visit[16];
bool vis[16][16];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
int result = 987654321;
void Input() {
	cin >> T >> M >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
}
void copy_board() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			t_board[i][j] = board[i][j];
		}
	}
}
void BFS(int x, int y) {
	queue<pair<int, int>> que;
	memset(vis, 0, sizeof(vis));
	que.push({ x,y });
	vis[x][y] = true;

	while (!que.empty()) {
		auto cur = que.front();
		que.pop();
		for (int i = 1; i <= t_board[cur.first][cur.second] - 1; i++) {
			for (int j = 0; j < 4; j++) {
				int nx = cur.first + dx[j] * i;
				int ny = cur.second + dy[j] * i;
				if (nx < 0 || nx >= N || ny < 0 || ny >= M)
					continue;
				if (vis[nx][ny])
					continue;
				if (t_board[nx][ny] == 0)
					continue;
				vis[nx][ny] = true;
				que.push({ nx,ny });
			}
		}
		t_board[cur.first][cur.second] = 0;

	}
}
void gravity() {
	for (int i = 0; i < M; i++) {
		for (int j = N - 2; j >= 0; j--) {
			for (int k = j + 1; k < N; k++) {
				if (t_board[k][i] == 0) {
					t_board[k][i] = t_board[k - 1][i];
					t_board[k - 1][i] = 0;
				}
			}
		}
	}
}
void print() {
	cout << "------------------------" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << t_board[i][j] << " ";
		}
		cout << endl;
	}
	cout << "------------------------" << endl;
}
void play(int idx) {
	//벽돌꺠기
	bool flag = false;
	for (int i = 0; i < N; i++) {
		if (t_board[i][idx] != 0) {
			BFS(i, idx);
			flag = true;
			break;
		}
	}
	//중력
	if (flag) {
		gravity();
	}
}
void getResult() {
	int answer = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (t_board[i][j] != 0)
				answer++;
		}
	}
	result = min(answer, result);
}
void DFS(int cnt) {
	if (cnt == T) {
		copy_board();
		for (int i = 0; i < T; i++) {
			play(visit[i]);
		}
		//print();
		getResult();
		return;
	}
	for (int i = 0; i < M; i++) {
		visit[cnt] = i;
		DFS(cnt + 1);
	}
}
void Solution() {
	DFS(0);
}
void Initialize() {
	result = 987654321;
	memset(visit, 0, sizeof(visit));
}
void Solve() {
	int t_case;
	cin >> t_case;
	for (int i = 1; i <= t_case; i++) {
		Initialize();
		Input();
		Solution();
		cout << "#" << i << " "<<result<< endl;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}