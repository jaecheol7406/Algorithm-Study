/*
BOJ 15683번: 감시

1. 각 CCTV가 감시 가능한 방향들을 dir에 저장.
	(1번 카메라는 북,동,남,서)
	(2번 카메라는 (서,동),(남,북)
	....)
2. DFS로 CCTV가 순찰해야하는 방향을 cmd벡터에 저장.
3. 각 CCTV의 방향을 정하면 순찰한다. 순찰 시, 순찰한 칸은 -1로 지정
4. 모든 CCTV의 순찰이 끝나면, 0인 칸을 확인하여 사각지대 수를 도출.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct cctv {
	int x;
	int y;
};
int N, M;
int board[10][10];
int t_board[10][10];
int result = 987654321;
vector<cctv> cctv_list;
//vector<vector<cctv>> cctv_list(6);
vector<vector<vector<int>>> dir{ {{0},{1},{2},{3}},
	{{0,2},{1,3}},
	{{0,1},{1,2},{2,3},{3,0}},
	{{0,1,3},{0,1,2},{1,2,3},{0,2,3}},
	{{0,1,2,3}} };
vector<int> cmd;
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
			if (1<=board[i][j] && board[i][j]<=5) {
				cctv_list.push_back({ i,j});
			}
		}
	}

}
void watch(int idx, int n) {
	int x = cctv_list[idx].x;
	int y = cctv_list[idx].y;
	int num = board[x][y];
	for (int i = 0; i < dir[num - 1][n].size(); i++) {
		int nx = x;
		int ny = y;
		int nd = dir[num - 1][n][i];
		while (true) {
			nx += dx[nd];
			ny += dy[nd];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M)
				break;
			if (t_board[nx][ny] == 6)
				break;
			if (t_board[nx][ny] == 0) {
				t_board[nx][ny] = -1;
			}
		}
	}

}
void copy_map() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			t_board[i][j] = board[i][j];
	}
}
int getAns() {
	int answer = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (t_board[i][j] == 0)
				answer++;
		}
	}
	return answer;
}
void DFS(int cnt) {
	if (cnt == cctv_list.size()) {
		copy_map();
		for (int i = 0; i < cmd.size(); i++) {
			watch(i, cmd[i]);
		}
		result = min(result, getAns());
		return;
	}
	int x = cctv_list[cnt].x;
	int y = cctv_list[cnt].y;
	int idx = board[x][y];
	for (int i = 0; i < dir[idx-1].size(); i++) {
		cmd.push_back(i);
		DFS(cnt + 1);
		cmd.pop_back();
	}

}
void Solution() {
	DFS(0);
	cout << result << endl;
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